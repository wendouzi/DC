#include "imgpreview.h"
#include "QDebug"
#include "QImage"
#include "QColor"
#include "CCImage.h"
#include "QRectF"
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

ElementGroup::ElementGroup():m_pen(Qt::black)
  , m_startpoint(-1,-1)
  , m_lastpoint(-1,-1) {

}

ElementGroup::~ElementGroup()
{

}
ElementGroup::ElementGroup(const ElementGroup & e) {
    this->m_pen = e.m_pen;
    this->m_startpoint = e.m_startpoint;
    this->m_lastpoint = e.m_lastpoint;
}

void ElementGroup::setStartPoint(const QPointF &p) {
    m_startpoint = p;
}
void ElementGroup::setLastPoint(const QPointF &p) {
    m_lastpoint = p;
}

bool ElementGroup::isEmpty() {
    if( m_startpoint.x() == -1 || m_startpoint.y() == -1) {
        return true;
    }
    else {
        return false;
    }
}
QPointF * ElementGroup::getStartPoint() {
    return &m_startpoint;
}

QPointF * ElementGroup::getLastPoint() {
    return &m_lastpoint;
}


PreViewPainter::PreViewPainter(QQuickItem *parent):QQuickPaintedItem(parent)
    , m_previewwidth(PREVIEW_WIDTH)
    , m_previewheight(PREVIEW_HEIGHT)
    , m_bpressed(false)
    , m_LastFile(INVALIDSELECT)
    , m_rectF(NULL)
    , m_ccimage(NULL)
    , m_bupdate(false)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    m_rectF = new QRectF(0,0,PREVIEW_WIDTH,PREVIEW_HEIGHT);
    m_ccimage = CCImage::getInstance();
}

PreViewPainter::~PreViewPainter() {

}

int PreViewPainter::previewwidth() {
    return m_previewwidth;
}

void PreViewPainter::setPreviewwidth(int w) {
    m_previewwidth = w;
}

int PreViewPainter::previewheight() {
    return m_previewheight;
}

void PreViewPainter::setPreviewheight(int h) {
    m_previewwidth = h;
}

void PreViewPainter::undo() {

}

void PreViewPainter::onSelectedFile(QString q) {
    qDebug("PreViewPainter::onSelectedFile()");
    if(q.compare(INVALIDSELECT) != 0 && q.compare(m_LastFile) !=0){
        m_bupdate = true;
    }
    else {
        m_bupdate = false;
    }
    m_LastFile = q;
    this->update();
}

void PreViewPainter::mousePressEvent(QMouseEvent *event) {
    if(!(event->button() & acceptedMouseButtons())) {
        QQuickPaintedItem::mousePressEvent(event);
    }
    else {
        qDebug("PreviewPainter::mouse Pressed");
        m_bpressed = true;
        QPointF startpoint = event->localPos();
        m_element.setStartPoint(startpoint);
        m_element.setLastPoint(startpoint);
        event->setAccepted(true);
        update();
    }
}

void PreViewPainter::mouseMoveEvent(QMouseEvent *event) {
    if(!m_bpressed || m_element.isEmpty()) {
        QQuickPaintedItem::mouseMoveEvent(event);
    }
    else {
        qDebug("PreviewPainter::mousePressEvent");
        QPointF lastpoint = event->localPos();
        m_element.setLastPoint(lastpoint);
        update();
    }
}

void PreViewPainter::mouseReleaseEvent(QMouseEvent *event) {
    if(!m_bpressed || m_element.isEmpty() || !(event->button() & acceptedMouseButtons())) {
        QQuickPaintedItem::mouseReleaseEvent(event);
    }
    else {
        qDebug("PreviewPainter::mousePressEvent");
        QPointF lastpoint = event->localPos();
        m_element.setLastPoint(lastpoint);
        m_bpressed = false;
        update();
    }
}

void PreViewPainter::purgePaintElements() {

}

void PreViewPainter::paint(QPainter *painter) {
    qDebug("PreViewPainter::paint()");
    /*
    if(m_LastFile.compare(INVALIDSELECT) != 0) {
        if(m_bupdate) {
            //ccimg->initImg("/home/yangxianping/workspace/gf/data/GF1_WFV1_E111.8_N29.7_20150521_L1A0000818473/GF1_WFV1_E111.8_N29.7_20150521_L1A0000818473.tiff");
            //ccimg->initImg(PREVIEW_TESE_CASE);
            m_ccimage->initImg(m_LastFile.toStdString());
            QImage * qimg = m_ccimage->getImg();
            painter->setRenderHint(QPainter::Antialiasing);
            painter->drawImage(*m_rectF,*qimg);
            m_bupdate = false;
        }
    }
    */
    painter->drawRect(m_element.getStartPoint()->rx()
                      ,m_element.getStartPoint()->ry()
                      ,m_element.getLastPoint()->rx() - m_element.getStartPoint()->rx()
                      ,m_element.getLastPoint()->ry() - m_element.getStartPoint()->ry()
                      );
}

PreView::PreView(QQuickItem *parent):
    QQuickPaintedItem(parent)
  , m_LastFile(INVALIDSELECT)
  , m_rectF(NULL)
  , m_bupdate(false)
{
    qDebug("PreView::PreView() constructor");
    m_ImageManager = new ImageManager();
    m_ImageManager->moveToThread(&workThread);
    connect(&workThread,SIGNAL(finished()), m_ImageManager,SLOT(deleteLater()));
    connect(this,SIGNAL(sig_prepare_image(QString)),m_ImageManager,SLOT(slot_prepare_image(QString)));
    connect(m_ImageManager,SIGNAL(sig_image_ready()),this,SLOT(onImageReady()));
    connect(this,SIGNAL(sig_paint_img(QString, QPainter*)), m_ImageManager,SLOT(slot_paint_image(QString,QPainter*)));
    workThread.start();
}

PreView::~PreView() {
    qDebug("PreView::~PreView() destructor");
    disconnect(this,SIGNAL(sig_prepare_image(QString)),m_ImageManager,SLOT(slot_prepare_image(QString)));
    disconnect(m_ImageManager,SIGNAL(sig_image_ready()),this,SLOT(onImageReady()));
    disconnect(this,SIGNAL(sig_paint_img(QString,QPainter*)), m_ImageManager,SLOT(slot_paint_image(QString,QPainter*)));
    workThread.quit();
    workThread.wait();
}

void PreView::paint(QPainter *painter) {
    qDebug("PreView::paint()");
        if(m_bupdate) {
            CCImage * m_ccimage = CCImage::getInstance();
            QImage *qimg = m_ccimage->getImg();
            if(qimg != NULL) {
              painter->setRenderHint(QPainter::Antialiasing);
              QRectF qr(2,2,PREVIEW_WIDTH,PREVIEW_HEIGHT);
                painter->drawImage(qr,*qimg);
            }
            m_bupdate = false;

    }
}

void PreView::onSelectedFile(QString q) {
    qDebug("PreViewPainter::onSelectedFile()");
    if(q.compare(INVALIDSELECT) != 0 && q.compare(m_LastFile) !=0){
        emit sig_prepare_image(q);
        qDebug("emit signal to prepare image");
    }
    else {
    }
    m_LastFile = q;
    //m_bupdate = true;
    //this->update();
}

void PreView::onImageReady() {
    qDebug("receiver the signal of image ready");
    m_bupdate = true;
    this->update();
}
