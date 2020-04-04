#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QAbstractSocket>
#include <QHttpMultiPart>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "headers/controller.h"
#include "headers/project.h"
#include "headers/projectmodel.h"

const QString QUWI_URL = "https://api.quwi.com/v2";

Controller::Controller(QObject *obj)
    : QObject(obj)
{
    m_manager = new QNetworkAccessManager(this);
    m_model = new ProjectModel(this);
}

void Controller::login(QString userName, QString password)
{
    if (userName.isEmpty() || password.isEmpty())
    {
        return;
    }

    QByteArray jsonString = QString("{\"email\":\"%1\",\"password\":\"%2\"}").arg(userName).arg(password).toLocal8Bit();

    QByteArray postDataSize = QByteArray::number(jsonString.size());

    QUrl serviceURL(QUWI_URL + "/auth/login");
    QNetworkRequest request(serviceURL);

    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Content-Length", postDataSize);

    auto reply = m_manager->post(request, jsonString);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();
        m_token = jsonObject["token"].toString();
        m_logged = true;
        emit loggedChanged();
        reply->deleteLater();
    });
}

void Controller::logout()
{
    QUrl serviceURL(QUWI_URL + "/auth/logout");
    QNetworkRequest request(serviceURL);

    auto reply = m_manager->post(request, QByteArray());

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        if (reply->error() == QNetworkReply::NetworkError::NoError)
        {
            m_logged = false;
            emit loggedChanged();
        }
        m_token.clear();
        reply->deleteLater();
    });
}

void Controller::getProjects()
{
    if (m_token.isEmpty())
    {
        qDebug() << "Token is empty";
        return;
    }

    QNetworkRequest request(QUrl(QUWI_URL + "/projects-manage"));

    QString headerData = "Bearer " + m_token;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    auto reply = m_manager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        m_model->clearModel();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();
        auto projects = jsonObject["projects"].toArray();
        for (int i = 0; i < projects.size(); ++i)
        {
            QJsonObject npcObject = projects[i].toObject();
            Project *newProject = new Project;
            newProject->setId(npcObject["id"].toInt());
            newProject->setName(npcObject["name"].toString());
            newProject->setLogoUrl(npcObject["logo_url"].toString());
            newProject->setPosition(npcObject["position"].toInt());
            newProject->setActive(npcObject["is_active"].toInt());
            newProject->setOwnerWatcher(npcObject["is_owner_watcher"].toInt());
            newProject->setSpendTimeWeek(npcObject["spend_time_week"].toInt());
            newProject->setSpendTimeMonth(npcObject["spend_time_month"].toInt());
            newProject->setSpendTimeAll(npcObject["spend_time_all"].toInt());
            m_model->add(newProject);
        }
        emit modelUpdated();
        reply->deleteLater();
    });
}

void Controller::updateValue(int projectId, QString name, bool active, bool watcher)
{
    if (m_token.isEmpty())
    {
        qDebug() << "Token is empty";
        return;
    }

    m_model->updateValue(projectId, name, active, watcher);


    QHttpPart textPart1;
    textPart1.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    textPart1.setBody(name.toLocal8Bit());

    QHttpPart textPart2;
    textPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"is_active\""));
    textPart2.setBody(QString("%1").arg(active).toLocal8Bit());

    QHttpPart textPart3;
    textPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"is_owner_watcher\""));
    textPart3.setBody(QString("%1").arg(watcher).toLocal8Bit());

    QNetworkRequest request(QUrl(QUWI_URL + "/projects-manage/update?id=" + QString::number(projectId)));

    QString headerData = "Bearer " + m_token;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->append(textPart1);
    multiPart->append(textPart2);
    multiPart->append(textPart3);

    auto reply = m_manager->post(request, multiPart);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        emit modelUpdated();
        reply->deleteLater();
    });

}

ProjectModel* Controller::model()
{
    return m_model;
}

bool Controller::logged() const
{
    return m_logged && !m_token.isEmpty();
}

void Controller::setLogged(bool logged)
{
    m_logged = logged;
    emit loggedChanged();
}
