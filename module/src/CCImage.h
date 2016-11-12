#ifndef CCIMAGE
#define CCIMAGE
#include "QImage"
#include <string>
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

#endif // CCIMAGE
