#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlPlugin.h"
#include "CCBaseTypeDefine.h"
#include <QQuickView>
#include <QQmlContext>
#include "Home.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const AppId first = 0;
    QmlPlugin * qp = new QmlPlugin(first, &engine);
    qp->registerTypes();
    //QQuickView viwer;
    //viwer.setSource(QUrl(QStringLiteral("qrc:///Home.qml")));
    //QQuickItem *rootItem = viwer.rootObject();
    //viwer.rootContext()->setContextProperty("cpplogicMaker",new Home(first));
    engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));
    //viwer.show();
    return app.exec();
    /*
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));

    return app.exec();
    */
}
