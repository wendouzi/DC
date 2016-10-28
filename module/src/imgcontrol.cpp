#include "imgcontrol.h"
#include "GFimg.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
ImgControl::ImgControl() {
    qDebug("ImgControl::constructor");
}

ImgControl::~ImgControl() {
    qDebug("ImgControl::destructor");
}

void ImgControl::slot_to_process(QString _tiff, QString _xml, QString _rpb, QString sdir) {
    qDebug("ImgControl::slot_to_process");
    GFimg *m_pGF = new GFimg(_tiff.toStdString(), 0, _xml.toStdString(),_rpb.toStdString());
    /*
    m_pGF->getCorner();
    m_pGF->init();
    m_pGF->caldensity();
    m_pGF->writeDen(_sdir);
    */
    delete m_pGF; m_pGF=NULL;
    QChar sep = QDir::separator();
    QString sFilePath = sdir+ sep+ QString("DCtest.txt");
    qDebug("test file path : %s", sFilePath.toStdString().c_str());
    QFile file(sFilePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        emit sig_to_schedule(RESULT_FAILED);
        return;
    }
    QTextStream out(&file);
    out<<"the wirte word"<<endl;
    out.flush();
    file.close();
    emit sig_to_schedule(RESULT_SUCESS);
}
