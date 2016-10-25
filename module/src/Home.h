#ifndef HOME_H
#define HOME_H
#include <QObject>
#include <QWindow>
#include <QQuickItem>
#include <QtQml/qqmlcomponent.h>
#include "CCBaseTypeDefine.h"

class Home : public QWindow
{
    Q_OBJECT
public:
    Home(AppId id);
private:
    AppId m_Appid;
};



#endif // HOME_H

