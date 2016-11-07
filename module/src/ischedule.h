// this class is for control image processing shedule

#ifndef ISCHEDULE_H
#define ISCHEDULE_H

#define SCHEDULE (ischedule::getInstance())

#include "QObject"
#include "QThread"
#include <QVariant>
#include "CCBaseTypeDefine.h"
#include "imgcontrol.h"
#include <memory.h>
class CCLogin;
class ImgControl;
class ischedule : public QObject{
    Q_OBJECT
    QThread workThread;
public:
     static ischedule* getInstance();
private:
    ischedule();
    virtual ~ischedule();
public slots:
    // receive the signal from UI
    void slot_for_UI(QString q, QVariant s);
    void slot_for_imgcontrol(QString s);
signals:
    // send signal to UI
    void sig_to_imgcontrol_cancel(QString s);
    void sig_to_UI(QString q, QVariant s);
    void sig_to_imgcontrol(QString q1,QString q2,QString q3,QString q4, QString q5);
private:
    void img_process_begin();
private:
    // copy constructor
    ischedule(const ischedule&);
    // assign constructor
    ischedule& operator = (const ischedule &);
    volatile bool continueflag;
    static ischedule * m_pIschedule;
    QString m_ftiff;
    QString m_fxml;
    QString m_frpb;
    QString m_dsave;
    QString m_wantedProducts;
    ImgControl * m_pic;
};
#endif // ISCHEDULE_H

