#ifndef HOMEPAGE_H
#define HOMEPAGE_H


#include <QObject>
class HomePage : public QObject
{
    Q_OBJECT
public:
    HomePage(QObject * parent);
    ~HomePage();
};

#endif // HOMEPAGE_H
