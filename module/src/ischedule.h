// this class is for control image processing shedule

#ifndef ISCHEDULE_H
#define ISCHEDULE_H

#define SCHEDULE (ischedule::getInstance())

#include "QObject"
#include "QThread"
#include <QVariant>
#include "CCBaseTypeDefine.h"
#include "GFimg.h"
class CCLogin;
class ischedule : public QThread {
    Q_OBJECT
public:
     static ischedule* getInstance();
private:
    ischedule();
    virtual ~ischedule();
public slots:
    // receive the signal from UI
    void slot_for_UI(QString q, QVariant s);
signals:
    // send signal to UI
    void sig_to_UI(QString q, QVariant s);
protected:
    void run();
private:
    // copy constructor
    ischedule(const ischedule&);
    // assign constructor
    ischedule& operator = (const ischedule &);
    volatile bool continueflag;
    static ischedule * m_pIschedule;
    std::string m_ftiff;
    std::string m_fxml;
    std::string m_frpb;
    std::string m_dsave;
    GFimg * m_pGF;
};
#endif // ISCHEDULE_H

