#ifndef CCBASETYPEDEFINE_H
#define CCBASETYPEDEFINE_H
#include <iostream>
typedef unsigned int AppId;
const AppId InvalidAppId = 0xffffffff;

#define IMG_PRO_START "img.start"
#define IMG_PRO_STOP "img.stop"
#define IMG_PRO_CANCEL "img.cancel"
#define IMG_PRO_FINISH "img.finish"
#define IMG_PRO_FAILED "img.failed"
#define TIFF_FILE_NAME "tiff.file.name"
#define XML_FILE_NAME "xml.file.name"
#define RPB_FILE_NAME "xml.file.name"
#define SAVE_DIR_NAME "xml.file.name"


#define assert(exp) { if (!(exp)) { std::cout << "Assertion failed: " << #exp << "\n" << "line: " << __LINE__ << "\n" << "file: " << __FILE__ << "\n";exit(EXIT_FAILURE); } }
#endif // CCBASETYPEDEFINE_H
