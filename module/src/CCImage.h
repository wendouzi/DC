#ifndef CCIMAGE
#define CCIMAGE
#include "QImage"
#include <string>
#include "QThread"
#include "CCBaseTypeDefine.h"
class CCImage {
private:
    CCImage();
    static CCImage * ccimg;
    QImage * qimg;
    std::string lastfile;
public:
    static CCImage * getInstance();
    QImage * getImg();
    void initImg(std::string tfile = PREVIEW_TESE_CASE);
    ~CCImage();
};

class ImageManager : public QObject {
    Q_OBJECT
    QThread workThread;
public:
    ImageManager();
    ~ImageManager();
public slots:
    void slot_prepare_image(QString q);
    void slot_paint_image(QString q, QPainter * painter);
signals:
    void sig_image_ready();
};

#endif // CCIMAGE
