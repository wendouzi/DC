#include "imgpreview.h"
#include "QDebug"
#include "QImage"
#include "QColor"
ImgPreview::ImgPreview(GFimg * gft) :
    QQuickImageProvider(QQuickImageProvider::Image)
{
    qDebug("ImgPreview::ImgPreview(), constructor");
    gf = gft;
}

QImage  ImgPreview::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int w = 512;
    int h = 512;
    if(size)
        *size = QSize(w,h);

    if (id.compare(GF_PREVIEW) != 0) {
            QImage qqimg(w,h,QImage::Format_RGB888);
            qqimg.fill(QColor(AUTO_FILL_COLOR));
            // write the color name
          return qqimg;
    }
    //if(w > gf->width || h > gf->height) {return NULL;}
    QImage qimg(w,h,QImage::Format_RGB888);
    int rowstep = gf->height / h;
    int colstep = gf->width / w;
    for(int row = 0; row < gf->height; row += rowstep) {
        for (int col = 0; col < gf->width; col += colstep) {
            int idx = row * gf->width + col;
            float rt = gf->band3[idx] * RGB_SCALE ;
            int r = (int) rt;
            if (r > 255) {
                r = 255;
            }else {
                r = r % 256 ;
            }
            int g = gf->band2[idx]* RGB_SCALE ;
            if (g > 255) {
                g = 255;
            }else {
                g = g % 256 ;
            }
            int b = gf->band1[idx]* RGB_SCALE;
            if (b > 255) {
                b = 255;
            }else {
                b = b % 256 ;
            }
            qimg.setColor(qimg.pixelIndex(col/colstep,row/rowstep),QColor(r,g,b).rgb());
            //qimg.setPixelColor(col/colstep,row/rowstep,QColor(r,g,b));
        }
    }
    return qimg;
}

ElementGroup::ElementGroup() {

}

ElementGroup::~ElementGroup() {

}
ElementGroup::ElementGroup(const QRectF &rectg) {
    this->m_rect = rectg;
}

PreViewPainter::PreViewPainter(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{

}

PreViewPainter::~PreViewPainter() {

}

void PreViewPainter::undo() {

}

void PreViewPainter::paint(QPainter *painter) {

}
