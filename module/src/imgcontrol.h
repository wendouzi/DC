#ifndef IMGCONTROL_H
#define IMGCONTROL_H
#include <QThread>
#include <QVariant>
#include "CCBaseTypeDefine.h"
#include "cancel_flag.h"
class ImgControl : public  QObject {
    Q_OBJECT
    QThread workThread;
public:
    ImgControl();
    virtual ~ImgControl();
signals:
    void sig_to_schedule(QString s);
public  slots:
    void slot_to_process(QString _tiff, QString _xml, QString _rpb, QString sdir, QString products);
    void slot_for_cancel(QString s);
private:
    bool m_bcancelFlag;
};

#endif // IMGCONTROL

