#ifndef CCBASETYPEDEFINE_H
#define CCBASETYPEDEFINE_H
#include <iostream>
#include <QString>
#define VERSION  QString("1.0")
typedef unsigned int AppId;
const AppId InvalidAppId = 0xffffffff;

#define REQ_IMG_PRO_START       QString("img.start")
#define REQ_IMG_PRO_STOP        QString("img.stop")
#define REQ_IMG_PRO_CANCEL      QString("img.cancel")

#define RES_IMG_PRO_START       QString("img.start")
#define RES_IMG_PRO_STOP        QString("img.stop")
#define RES_IMG_PRO_CANCEL      QString("img.cancel")
#define RES_IMG_PRO_FINISH      QString("img.finish")
#define RES_IMG_PRO_FAILED      QString("img.failed")

#define RESULT_SUCESS           QString("img.sucess")
#define RESULT_FAILED           QString("img.failed")
#define FILE_EMPTY              QString("input.empty")
#define TIFF_FILE_NAME          QString("tiff.file.name")
#define XML_FILE_NAME           QString("xml.file.name")
#define RPB_FILE_NAME           QString("rpb.file.name")
#define SAVE_DIR_NAME           QString("save.dir.name")

#define TIFF_FILEDIALOG    int(1)
#define XML_FILEDIALOG     int(2)
#define RPB_FILEDIALOG     int(3)
#define SDIR_FILEDIALOG    int(4)

#define TOTAL_PRODUCTS     int(7)
#define NDVI_ORDER         int(0)
#define NDWI_ORDER         int(1)
#define SVI_ORDER          int(2)
#define DISTANCE_ORDER     int(3)
#define KT_ORDER           int(4)
#define DINGLUO_ORDER      int(5)
#define FENGXIAN_ORDER     int(6)


#ifdef WIN32
#define DIR_BEGIN   8
#else
#define DIR_BEGIN   7
#endif
/*********************************************************************
*                               登录间隔 *单位:ms
***********************************************************************/
#define INTERVAL_LOGIN     int(10000)

/*********************************************************************
*                             最大登录次数
**********************************************************************/
#define NUM_LOGIN               5

/***************************记住密码标志位的有效值 ************/
#define VALID_FLAG  1


#define assert(exp) { if (!(exp)) { std::cout << "Assertion failed: " << #exp << "\n" << "line: " << __LINE__ << "\n" << "file: " << __FILE__ << "\n";exit(EXIT_FAILURE); } }
#endif // CCBASETYPEDEFINE_H
