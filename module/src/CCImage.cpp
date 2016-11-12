#include "CCImage.h"
#include "CCBaseTypeDefine.h"
#include "QColor"
#include "QImage"
#include "gdal_priv.h"
#include <stdio.h>
CCImage * CCImage::ccimg = NULL;
CCImage * CCImage::getInstance() {
    qDebug("CCImage::getInstance()");
    if(NULL == ccimg) {
        ccimg = new CCImage();
        return ccimg;
    }
    else {
        return ccimg;
    }
}

CCImage::CCImage() {
    ccimg = NULL; qimg = NULL;
}

QImage* CCImage::getImg() {
    return qimg;
}

CCImage::~CCImage() {
    qDebug("CCImage::~CCImage()");
    if(!ccimg) {
        if(!qimg) {
            delete qimg; qimg = NULL;
        }
        delete ccimg; ccimg = NULL;
    }
}

void CCImage::initImg(std::string tfile) {
    qDebug("CCImage::initImg()");
    if(tfile.compare(PREVIEW_TESE_CASE) == 0) {
        if(!qimg) {
            qimg = new QImage(PREVIEW_WIDTH,PREVIEW_HEIGHT,QImage::Format_RGB888);
        }
        for(int row =0 ; row < PREVIEW_HEIGHT; ++row) {
            for(int col =0; col < PREVIEW_WIDTH; ++col) {
                //qimg->setColor(qimg->pixelIndex(col,row),QColor(200,1,1).rgb());
                qimg->setPixel(row,col,QColor(236,182,120).rgb());
            }
        }
    }
    else if (tfile.compare(lastfile) == 0){
    }
    else {
        GDALAllRegister();
        GDALDataset * pDataset = NULL;
        pDataset = (GDALDataset *)GDALOpen(tfile.c_str(),GA_ReadOnly);
        if(pDataset == NULL)
        {
             qDebug("File to open file: %s\n", tfile.c_str());
            // GDALCose(pDataset);
             return ;
        }
        int nRasterCount = GDALGetRasterCount(pDataset);
        int width = GDALGetRasterXSize(pDataset);
        int height = GDALGetRasterYSize(pDataset);
        int widthstep = width / PREVIEW_WIDTH;
        int heightstep = height / PREVIEW_HEIGHT;
        qDebug("nRasterCount:%d,width:%d,height:%d\n",nRasterCount,width,height);
        qDebug("PREVIEW_WIDTH,%d, PREVIEW_HEIGHT, %d",PREVIEW_WIDTH,PREVIEW_HEIGHT );
        qDebug("widthsetp: %d, heightstep:%d\n",widthstep, heightstep);
        GDALRasterBand * pBand1 = pDataset->GetRasterBand(1);
        GDALRasterBand * pBand2 = pDataset->GetRasterBand(2);
        GDALRasterBand * pBand3 = pDataset->GetRasterBand(3);
        quint16  * pMemDatatemp= (quint16 *) CPLMalloc(sizeof(GDT_UInt16) * width * height);
        quint16  * pMemData1 = (quint16 *) CPLMalloc(sizeof(quint16) * PREVIEW_HEIGHT * PREVIEW_WIDTH);
        quint16  * pMemData2 = (quint16 *) CPLMalloc(sizeof(quint16) * PREVIEW_HEIGHT * PREVIEW_WIDTH);
        quint16  * pMemData3 = (quint16 *) CPLMalloc(sizeof(quint16) * PREVIEW_HEIGHT * PREVIEW_WIDTH);

        if(CE_Failure == pBand1->RasterIO(GF_Read,0,0,
                width,height,pMemDatatemp,
                width,height,GDT_UInt16,0,0)) {
                    qDebug("ead the 1st band error");
                    return ;
        }
        for(int col = 0; col < PREVIEW_WIDTH; col++) {
            for(int row =0 ; row < PREVIEW_HEIGHT; row++) {
                pMemData1[row*PREVIEW_WIDTH+col] = pMemDatatemp[row*heightstep*width+col*widthstep];
            }
        }
        if(CE_Failure == pBand2->RasterIO(GF_Read,0,0,
                width,height,pMemDatatemp,
                width,height,GDT_UInt16,0,0)) {
                    qDebug("ead the 2st band error");
                    return ;
        }
        for(int col = 0; col < PREVIEW_WIDTH; col++) {
            for(int row =0 ; row < PREVIEW_HEIGHT; row++) {
                pMemData2[row*PREVIEW_WIDTH+col] = pMemDatatemp[row*heightstep*width+col*widthstep];
            }
        }
        if(CE_Failure == pBand3->RasterIO(GF_Read,0,0,
                width,height,pMemDatatemp,
                width,height,GDT_UInt16,0,0)) {
                    qDebug("ead the 3st band error");
                    return ;
        }
        for(int col = 0; col < PREVIEW_WIDTH; col++) {
            for(int row =0 ; row < PREVIEW_HEIGHT; row++) {
                pMemData3[row*PREVIEW_WIDTH+col] = pMemDatatemp[row*heightstep*width+col*widthstep];
            }
        }

        quint16 bmax[3]= {0,0,0};
        quint16 bmin[3] = {1024,1024,1024};
        for(int idx = 0; idx < PREVIEW_HEIGHT*PREVIEW_WIDTH; idx++){
            if(pMemData1[idx] > bmax[0]) bmax[0] = pMemData1[idx];
            if(pMemData2[idx] > bmax[1]) bmax[1] = pMemData2[idx];
            if(pMemData3[idx] > bmax[2]) bmax[2] = pMemData3[idx];
            if(pMemData1[idx] < bmin[0]) bmin[0] = pMemData1[idx];
            if(pMemData2[idx] < bmin[1]) bmin[1] = pMemData2[idx];
            if(pMemData3[idx] < bmin[2]) bmin[2] = pMemData3[idx];
        }
        printf("min[%hu,%hu,%hu],max[%hu,%hu,%hu]",bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
        for(int idx = 0; idx < PREVIEW_HEIGHT*PREVIEW_WIDTH; idx++){
            pMemData1[idx] =  COLOR_MAX_INT * (pMemData1[idx] - bmin[0])/(bmax[0]-bmin[0]+1) ;
            pMemData2[idx] =  COLOR_MAX_INT * (pMemData2[idx] - bmin[1])/(bmax[1]-bmin[1]+1) ;
            pMemData3[idx] =  COLOR_MAX_INT * (pMemData3[idx] - bmin[2])/(bmax[2]-bmin[2]+1) ;
        }

        GDALClose((GDALDatasetH)pDataset);
        CPLFree(pMemDatatemp);

        if(!qimg) {
            qimg = new QImage(PREVIEW_WIDTH,PREVIEW_HEIGHT,QImage::Format_ARGB32_Premultiplied);
            qimg->fill(QColor(Qt::white).rgb());
        }
        for(int col = 0; col < PREVIEW_WIDTH; col++) {
            for(int row =0 ; row < PREVIEW_HEIGHT; row++) {
                qimg->setPixel(col,row,QColor(pMemData3[row*PREVIEW_WIDTH+col],pMemData2[row*PREVIEW_WIDTH+col],pMemData1[row*PREVIEW_WIDTH+col]).rgb());
            }
        }
      CPLFree(pMemData1); CPLFree(pMemData2);CPLFree(pMemData3);
    }
}
