#ifndef IMGPREVIEW
#define IMGPREVIEW
#include "QImage"
#include "GFimg.h"
#include "QString"
#include "qquickimageprovider.h"
#include "QQuickPaintedItem"
#include "QRectF"
#include "QPainter"
#include "QQuickItem"
#include "QPen"
#include "QLineF"
#include "QPointF"
#include "CCImage.h"
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
    ElementGroup(const ElementGroup & e);
    void setStartPoint(const QPointF & p);
    void setLastPoint(const QPointF & p);
    QPointF *  getStartPoint();
    QPointF * getLastPoint();
    bool isEmpty();
    ~ElementGroup();
private:
    QPen m_pen;
    QPointF m_startpoint;
    QPointF m_lastpoint;
};


class PreViewPainter : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(int previewwidth READ previewwidth WRITE setPreviewwidth NOTIFY previewwidthChanged)
    Q_PROPERTY(int previewheight READ previewheight WRITE setPreviewheight NOTIFY previewheightChanged)
public:
    PreViewPainter(QQuickItem * parent = 0);
    ~PreViewPainter();
    Q_INVOKABLE void undo();
    void paint(QPainter *painter);

    int previewwidth();
    void setPreviewwidth(int w);
    int previewheight();
    void setPreviewheight(int h);
signals:
    void previewwidthChanged();
    void previewheightChanged();
public slots:
    void onSelectedFile(QString q);
protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void purgePaintElements();
private:
    int m_previewwidth;
    int m_previewheight;
    ElementGroup  m_element;
    bool m_bpressed;
    bool m_bupdate;
    QString m_LastFile;
    QRectF * m_rectF;
    CCImage * m_ccimage;
};

#endif // IMGPREVIEW

