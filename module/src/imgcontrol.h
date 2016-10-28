#ifndef IMGCONTROL_H
#define IMGCONTROL_H
#include <QThread>
#include <QVariant>
#include "CCBaseTypeDefine.h"
class ImgControl : public  QObject {
    Q_OBJECT
    QThread workThread;
public:
    ImgControl();
    virtual ~ImgControl();
signals:
    void sig_to_schedule(QString s);
public  slots:
    void slot_to_process(QString _tiff, QString _xml, QString _rpb, QString sdir);
};


#endif // IMGCONTROL

