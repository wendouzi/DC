
#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include "QmlPlugin.h"
#include "CCBaseTypeDefine.h"
#include <QQuickView>
#include <QQmlContext>
#include "Home.h"
#include "CCLogin.h"
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "Disease control start" << std::endl;
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<CCLogin>("CCLogin", 1, 0, "CCLogin");
    engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));
    return app.exec();
}
