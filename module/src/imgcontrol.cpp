#include "imgcontrol.h"
#include "GFimg.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>
#include <QStringList>
ImgControl::ImgControl() {
    qDebug("ImgControl::constructor");
}

ImgControl::~ImgControl() {
    qDebug("ImgControl::destructor");
}

void ImgControl::slot_to_process(QString _tiff, QString _xml, QString _rpb, QString _sdir) {
    qDebug("ImgControl::slot_to_process");
    QChar sep = QDir::separator();
    QString sFilePath = _sdir+ sep+ QString("README.txt");
    qDebug("test file path : %s", sFilePath.toStdString().c_str());
    QFile file(sFilePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        emit sig_to_schedule(RESULT_FAILED);
        return;
    }
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QTextStream out(&file);
    out<<"The GAOFEN image processed at : "<< str.toStdString().c_str()<< "  by Disease Control Image Process System."<<endl;
    out<<"Copyright © 2016 Powered By Chinese Center For Disease Control and Prevention. All rights reserved. " << endl;

    out.flush();
    file.close();
    /*
    qDebug("_tiff:%s",_tiff.toStdString().c_str());
    qDebug("_xml:%s",_xml.toStdString().c_str());
    qDebug("_rpb:%s",_rpb.toStdString().c_str());
    qDebug("_sdir:%s",_sdir.toStdString().c_str());
    QStringList para;
    QProcess proc;
    para<<_tiff << _rpb << _xml << _sdir;
    proc.start("cal_gf.exe",para);
*/

    GFimg * m_pGF = new GFimg(_tiff.toStdString(), 0, _xml.toStdString(),_rpb.toStdString());
    m_pGF->getCorner();
    m_pGF->init();
    m_pGF->caldensity();
    m_pGF->writeDen(_sdir.toStdString());
    delete m_pGF; m_pGF=NULL;

    emit sig_to_schedule(RESULT_SUCESS);
}
