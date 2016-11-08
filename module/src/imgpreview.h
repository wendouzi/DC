#ifndef IMGPREVIEW
#define IMGPREVIEW
#include "QImage"
#include "GFimg.h"
#include "QString"
#include "qquickimageprovider.h"
#include "QQuickPaintedItem"
#include "QRectF"
#include "QPainter"
#define RGB_SCALE int(2550)
#define GF_PREVIEW  QString("gf.preview")
#define AUTO_FILL_COLOR QString("black")
class ImgPreview : public QQuickImageProvider {
private:
    //QImage * qimg;
    GFimg * gf;
public:
    ImgPreview(GFimg * gft);
    QImage  requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

class ElementGroup {
public:
    ElementGroup();
    ElementGroup(const QRectF & rectg);
    ~ElementGroup();
private:
    QRectF m_rect;
};


class PreViewPainter : public QQuickPaintedItem {
    Q_OBJECT
public:
    PreViewPainter(QQuickItem * parent = 0);
    ~PreViewPainter();
    Q_INVOKABLE void undo();
};

#endif // IMGPREVIEW

