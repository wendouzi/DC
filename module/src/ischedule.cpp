

#include "ischedule.h"
#include "QDebug"
#include <QLibrary>
ischedule* ischedule::m_pIschedule = NULL;
ischedule::ischedule():QObject()
    , continueflag(false)
    , m_ftiff("")
    , m_fxml("")
    , m_frpb("")
    , m_dsave("")
    , m_pic(NULL)
{
    qDebug("ischedule::ischedule() construct func");
    m_pic = new ImgControl();
    m_pic->moveToThread(&workThread);
    connect(&workThread, SIGNAL(finished()), m_pic, SLOT(deleteLater()));
    connect(this,SIGNAL(sig_to_imgcontrol(QString,QString,QString,QString)),m_pic, SLOT(slot_to_process(QString,QString,QString,QString)));
    connect(m_pic, SIGNAL(sig_to_schedule(QString)),this, SLOT(slot_for_imgcontrol(QString)));
    workThread.start();
}
ischedule::~ischedule() {
    qDebug("ischedule::~ischedule() destruct func");
    disconnect(&workThread, SIGNAL(finished()), m_pic, SLOT(deleteLater()));
    disconnect(this,SIGNAL(sig_to_imgcontrol(QString,QString,QString,QString)),m_pic, SLOT(slot_to_process(QString,QString,QString,QString)));
    disconnect(m_pic, SIGNAL(sig_to_schedule(QString)),this, SLOT(slot_for_imgcontrol(QString)));

}
void ischedule::slot_for_UI(QString q,QVariant s) {
    qDebug("ischedule::slot_for_UI(), cmd : %s ", q.toStdString().c_str());
    // carry the information about file path
    if(0 == q.compare(REQ_IMG_PRO_START)) {

        // parse the QVariant to get the file path info and save
        QVariantMap qm = s.toMap();
        QVariant temp = qm.value(TIFF_FILE_NAME);
        if(!temp.canConvert(QVariant::String)) {
            qDebug("QVariant can not convert to String");
            return;
        }
        m_ftiff = qm.value(TIFF_FILE_NAME).toString();
        m_frpb = qm.value(RPB_FILE_NAME).toString();
        m_fxml = qm.value(XML_FILE_NAME).toString();
        m_dsave = qm.value(SAVE_DIR_NAME).toString();
        // if file is not empty
        if(m_ftiff.isEmpty() || m_fxml.isEmpty()
                || m_frpb.isEmpty() || m_dsave.isEmpty()) {
            qDebug("tiff or xml or rpb or save dir is empty");
            QVariant qv;
            emit sig_to_UI(FILE_EMPTY,qv);
            return;
        }
        img_process_begin();
        // begin to run()
    }
    else if (0 == q.compare(REQ_IMG_PRO_CANCEL)) {
        // cancel image process
    }
    else if (0 == q.compare(REQ_IMG_PRO_STOP)) {
        // stop image process
    }
}

void ischedule::img_process_begin() {
    qDebug("ischedule::img_process_begin");
    emit sig_to_imgcontrol(m_ftiff, m_fxml, m_frpb, m_dsave);
}

void ischedule::slot_for_imgcontrol(QString s) {
    qDebug("ischedule::slot_for_imgcontrol");
    if (0 == s.compare(RESULT_SUCESS)) {
        QVariant qv;
        qDebug("ischedule::slot_for_imgcontrol receive sig from imgcontrol: RESULT_SUCESS ");
        emit sig_to_UI(RES_IMG_PRO_FINISH,qv);
    }
}

ischedule * ischedule::getInstance() {
    qDebug("ischedule::getInstance()");
    if(NULL == m_pIschedule) {
        m_pIschedule = new ischedule();
        return m_pIschedule;
    }
    return m_pIschedule;
}
