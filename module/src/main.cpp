
#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include "QmlPlugin.h"
#include "CCBaseTypeDefine.h"
#include <QQuickView>
#include <QQmlContext>
#include "Home.h"
#include "CCLogin.h"
#include "imgpreview.h"
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "Disease control start" << std::endl;
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<CCLogin>("CCLogin", 1, 0, "CCLogin");
    qmlRegisterType<PreViewPainter>("CCPreviewPainter",1,0,"CCPainter");
    qmlRegisterType<PreView>("CCPreview",1,0,"CCPreview");
    //engine.load(QUrl(QStringLiteral("qrc:/Home.qml")));
    QQmlComponent com(&engine, QUrl(QStringLiteral("qrc:/Home.qml")));
    QObject * object = com.create();
    //PreViewPainter * p = object->findChild<PreViewPainter *>("CCPainter");
    CCLogin * l = object->findChild<CCLogin *>("CCLoginUI");
  //  MessageDialog *l->findChild<MessageDialog *>("messageDialog");
    PreView * pr = object->findChild<PreView *>("CCPreviewer");

    if(pr != NULL && l != NULL ) {
        //QObject::connect(l,SIGNAL(sig_selectdFile(QString)),p,SLOT(onSelectedFile(QString)));
        QObject::connect(l,SIGNAL(sig_selectdFile(QString)),pr,SLOT(onSelectedFile(QString)));
    }
    else
    {
       qDebug("PreViewPainter is NULL or CCLogin is NULL");
    }
        return app.exec();
}
