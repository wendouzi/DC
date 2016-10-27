

#include "ischedule.h"
#include "QDebug"
#include <QLibrary>
ischedule* ischedule::m_pIschedule = NULL;
ischedule::ischedule():QThread()
    , continueflag(false)
    , m_ftiff("")
    , m_fxml("")
    , m_frpb("")
    , m_dsave("")
    , m_pGF(NULL)
{
    qDebug("ischedule::ischedule() construct func");
}
ischedule::~ischedule() {
    qDebug("ischedule::~ischedule() destruct func");
}
void ischedule::slot_for_UI(QString q,QVariant s) {
    qDebug("ischedule::slot_for_UI()");
    // carry the information about file path
    if(q.compare(IMG_PRO_START) == 0) {
        // parse the QVariant to get the file path info and save
        QVariantMap qm = (QVariantMap)qv;
        m_ftiff = qm.value(TIFF_FILE_NAME);
        m_frpb = qm.value(RPB_FILE_NAME);
        m_fxml = qm.value(XML_FILE_NAME);
        m_dsave = qm.value(SAVE_DIR_NAME);
        // if file is not empty
        if(m_ftiff.empty() || m_fxml.empty()
                || m_frpb.empty() || m_dsave.empty()) {
            qDebug("tiff or xml or rpb or save dir is empty");
            QVariant qv;
            emit sig_to_UI(FILE_EMPTY,qv);
        }
        // begin to run()
        start();
    }
}

void ischedule::run() {
    qDebug("ischedule::run()");

    QMap<QString, QVariant> qm;
    QVariant qv;
    sleep(10000);
/*
    m_pGF = new GFimg(m_ftiff, 0, m_fxml,m_frpb);
    m_pGF->getCorner();
    m_pGF->init();
    m_pGF->caldensity();
    m_pGF->writeDen(m_dsave);
    delete m_pGF; m_pGF=NULL;
    qm.insert(IMG_PRO_FAILED,"10");
    qv = QVariant(qm);
*/
    emit sig_to_UI(IMG_PRO_FINISH,qv);
}

ischedule * ischedule::getInstance() {
    qDebug("ischedule::getInstance()");
    if(NULL == m_pIschedule) {
        m_pIschedule = new ischedule();
        return m_pIschedule;
    }
    return m_pIschedule;
}
