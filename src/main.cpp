#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>

#include "headers/controller.h"
#include "headers/projectmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Controller controller;

    qRegisterMetaType<ProjectModel*>();

    qmlRegisterType<Controller>("APIController", 1, 0, "Controller");

    auto size = app.primaryScreen()->size();

    ProjectModel model;


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("windowWidth", size.width());
    engine.rootContext()->setContextProperty("windowHeight", size.height());
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
