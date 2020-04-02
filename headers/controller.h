#pragma once

#include <QObject>
#include "project.h"
#include "projectmodel.h"
#include "projectroleenum.h"

class QNetworkAccessManager;
class QNetworkReply;

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ProjectModel* projectModel READ model)
    Q_PROPERTY(bool logged READ logged WRITE setLogged)

public:
    Controller(QObject *parent = nullptr);

    Q_INVOKABLE void login(QString userName, QString password);
    Q_INVOKABLE void logout();
    Q_INVOKABLE void getProjects();
    Q_INVOKABLE void add();
    Q_INVOKABLE void updateValue(int projectId, QString name, bool active, bool watcher);

    Q_INVOKABLE ProjectModel* model();

    bool logged() const;

signals:
    void loggedChanged();
    void modelUpdated();

private slots:
    void setLogged(bool logged);
    void replyFinished(QNetworkReply *reply);

private:
    ProjectModel *m_model;

    QNetworkAccessManager *m_manager;

    QString m_token;
    bool m_logged;
};
