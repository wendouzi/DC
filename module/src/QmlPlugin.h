#ifndef QMLPLUGIN_H
#define QMLPLUGIN_H

#endif // QMLPLUGIN_H
#include <QObject>
#include "CCBaseTypeDefine.h"
class QmlPlugin : public QObject
{
    Q_OBJECT
public:
    /// constructor.
    explicit QmlPlugin(AppId appId, QObject * parent);

    /// destructor.
    ~QmlPlugin();

    /// register some infomation at QML moc system.
    void registerTypes();

private:
    /// private member.
    AppId m_appId;
};
