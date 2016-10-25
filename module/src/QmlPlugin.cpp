#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include "QmlPlugin.h"
#include "CCBaseTypeDefine.h"
#include "CCLogin.h"

QmlPlugin::QmlPlugin(AppId appId, QObject *parent)
    : QObject(parent)
    , m_appId(appId)
{
}
QmlPlugin::~QmlPlugin()
{
}

void QmlPlugin::registerTypes()
{

    // register qml context.
    /*
    QQmlContext *ctx = APP::IF(m_appId) ? APP::IF(m_appId)->appQmlContext() : NULL;
    if (ctx) {
        ctx->setContextProperty("APP_LogTag", APP_LogTag);
        ctx->setContextProperty("MIST", APP::MIST(m_appId));
        ctx->setContextProperty("APP", APP::IF(m_appId));
        ctx->setContextProperty("appId", m_appId);
    }
*/
    // framework build in view type, register this view type or
    // the sub-types of NQView defined by developers.
   // qmlRegisterType<Home>("Home", 1, 0, "Home");
    qmlRegisterType<CCLogin>("CCLogin", 1, 0, "CCLogin");

}
