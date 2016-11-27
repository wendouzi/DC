#include "imgcontrol.h"
#include "GFimg.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>
#include <QStringList>
#include "products.h"
ImgControl::ImgControl():
    m_bcancelFlag(false)
{
    qDebug("ImgControl::constructor");
}

ImgControl::~ImgControl() {
    m_bcancelFlag = false;
    qDebug("ImgControl::destructor");
}
void ImgControl::slot_for_cancel(QString s) {
    qDebug("ImgControl::slot_for_cancel()");
    if(s.compare(REQ_IMG_PRO_CANCEL) == 0) {
        qDebug("receive REQ_IMG_PRO_CANCEL");
        m_bcancelFlag = true;
    }
}

void ImgControl::slot_to_process(QString _tiff, QString _xml, QString _rpb, QString _sdir, QString prods, QString _poi) {
    qDebug("ImgControl::slot_to_process");
    QChar sep = QDir::separator();
    QString sFilePath = _sdir+ sep+ QString("README.txt");
    qDebug("test file path : %s", sFilePath.toStdString().c_str());
    QFile file(sFilePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        emit sig_to_schedule(RESULT_FAILED);
        qDebug("open README.txt failed ");
        return;
    }
    QString ALL_PRODUCTS[TOTAL_PRODUCTS] ={"ndvi","ndwi","svi","distance","KT","Density","Risk"};
    bool want[TOTAL_PRODUCTS] = {false, false, false, false, false, false, false};
    for(int i = 0; i < TOTAL_PRODUCTS; i++) {
        want[i] = prods.at(i) == '1';
        qDebug("%s products want: %s", ALL_PRODUCTS[i].toStdString().c_str(), want[i] ? "yes": "no");
    }
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QTextStream out(&file);
    out<<QString("The GAOFEN image processed at : ")<< str.toStdString().c_str()<< QString("  by Disease Control Image Process System.")<<endl;
    out<<QString("Copyright © 2016 Powered By Chinese Center For Disease Control and Prevention. All rights reserved. ") << endl;
    out.flush();
    GFimg * m_pGF = new GFimg(_tiff.toStdString(), _xml.toStdString(), _rpb.toStdString(), _sdir.toStdString());
    m_pGF->getCorner();
    m_pGF->init();
    m_pGF->getUrban();
   // m_pGF->write(var_urban,"urban.tiff");
    Product pro;
    if(want[NDVI_ORDER]) {
        pro.ndvi = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {
        }
        else {
            out<< QString("Begin to calculate NDVI ") << endl;
            m_pGF->getNDVI();
            //m_pGF->print(print_ndvi);
            out << QString("calculate NDVI done, begin to write to save directory")<< endl;
            m_pGF->write(var_ndvi, "ndvi.tiff");
            out<< QString("write ndvi done") << endl;

        }
    }
    if(want[NDWI_ORDER]) {
        pro.ndwi = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {
        }
        else {
            out<< QString("Begin to calculate NDWI ") << endl;
            m_pGF->getNDWI();
            out << QString("calculate NDWI done, begin to write to save directory")<< endl;
            m_pGF->write(var_ndwi, "ndwi.tiff");
            out<< QString("write ndwi done") << endl;
        }
    }
    if(want[SVI_ORDER]) {
        pro.svi = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {
        }
        else {
            out<< QString("Begin to calculate SVI ") << endl;
            m_pGF->getSVI();
            out << QString("calculate SVI done, begin to write to save directory")<< endl;
            m_pGF->write(var_svi, "svi.tiff");
            out<< QString("write svi done") << endl;
        }
    }

    if(want[DISTANCE_ORDER]) {
        pro.distance = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {

        }
        else {
            out<< QString("Begin to calculate distance ") << endl;
            m_pGF->getDistance2water(Water2Pixel);
            out << QString("calculate distance done, begin to write to save directory")<< endl;
            m_pGF->write(var_dist, "distance.tiff");
            out<< QString("write distance done") << endl;
        }
    }
    if(want[KT_ORDER]) {
        pro.kt = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {

        }
        else {
            out<< QString("Begin to calculate KT transform ") << endl;
            m_pGF->getKTtransform();
            out << QString("calculate KT transform done, begin to write to save directory")<< endl;
            m_pGF->write(var_bright, "KT_bright.tiff");
            m_pGF->write(var_wet, "KT_wet.tiff");
            m_pGF->write(var_green,"KT_green.tiff");
            out<< QString("write bright, wet, green done") << endl;
        }
    }

    if(want[DENSITY_ORDER]) {
        pro.density = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {
        }
        else {
            out<< QString("Begin to calculate DENSITY ") << endl;
            m_pGF->caldensity(SVI_DIST);
            out << QString("calculate DENSITY done, begin to write to save directory")<< endl;
            m_pGF->write(var_density, "svi_dist_density.tiff");
            out<< QString("write density done") << endl;
        }
    }
    if(want[RISK_ORDER]) {
        pro.risk = true;
        if(cancelFlag::getInstance()->getCancelFlag()) {

        }
        else {
            out<< QString("RISK function still not finished ") << endl;
            m_pGF->CalRisk();
            out << QString("calculate RISK done, begin to write to save directory")<< endl;
            m_pGF->write(var_risk, "risk.tiff");
            out<< QString("write risk done") << endl;
        }
    }
    if(_poi.compare(FILE_EMPTY) != 0) {
        if(cancelFlag::getInstance()->getCancelFlag()) {
        }
        else {
            out<< QString("Begin to extract POIs ") << endl;
            QString extractFilePath = _sdir+ sep+ QString("extractResult.txt");
        //    m_pGF->generate_Lat_Long();
        //    m_pGF->readGeoinfo(_poi.toStdString());
        //    m_pGF->doextract(extractFilePath.toStdString());

            pro.distance = true;
            m_pGF->extractPOIs(pro,_poi.toStdString(),extractFilePath.toStdString());
        }
    }

    if(cancelFlag::getInstance()->getCancelFlag()) {
        out<<QString("cancel process")<<endl;
        qDebug("imgcontrol::slot_to_progress,cancel procecss");
        emit sig_to_schedule(RES_IMG_PRO_CANCEL);
        cancelFlag::getInstance()->setCancelFlag(false);
    }
    else {
        std::pair<int,int> lu(1880,4990);
        std::pair<int,int> rd(5055, 7715);
    //m_pGF->setPOI(lu,rd);
    // calculate and write to file
    // m_pGF->caldensity(SVI_DIST);
    // pair<列号，行号> // //

    //m_pGF->areacount(lu, rd);

   // m_pGF->writeDen(_sdir.toStdString());
   // m_pGF->print(print_distance);
   // m_pGF->print(print_svi);
   // m_pGF->print(print_density);
        emit sig_to_schedule(RESULT_SUCESS);
    }
    file.close();
    delete m_pGF; m_pGF=NULL;
}
