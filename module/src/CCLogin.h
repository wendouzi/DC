#ifndef CCLOGIN_H
#define CCLOGIN_H

#include <QTimer>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QtGlobal>
#include <QVariant>
#include "CCBaseTypeDefine.h"
#include <bitset>
class ischedule;


class CCLogin : public QObject
{
    Q_OBJECT
    //属性:用户名
    Q_PROPERTY(QString user_id READ user_id WRITE set_user_id NOTIFY sig_user_id_changed)
    //属性:密码
    Q_PROPERTY(QString password READ password WRITE set_password NOTIFY sig_password_changed)
    //属性:记住密码标志
    Q_PROPERTY(bool flag_remember READ flag_remember   WRITE set_flag_remember NOTIFY sig_flag_remember_changed)
    //属性:自动登录标志
    Q_PROPERTY(bool flag_auto READ flag_auto  WRITE set_flag_auto NOTIFY sig_flag_auto_changed)
    //属性：tiff文件
    Q_PROPERTY(QString file_tiff READ file_tiff WRITE setFile_tiff NOTIFY sig_file_tiffChanged)
    //属性：xml文件
    Q_PROPERTY(QString file_xml READ file_xml WRITE setFile_xml NOTIFY sig_file_xmlChanged)
    //属性：rpb文件
    Q_PROPERTY(QString file_rpb READ file_rpb WRITE setFile_rpb NOTIFY sig_file_rpbChanged)
    //属性：save dir
    Q_PROPERTY(QString save_dir READ save_dir WRITE setSave_dir NOTIFY sig_save_dirChanged)

    //***************checkbox****************************/
    // attribute: checkbox ndvi
    Q_PROPERTY(bool ndvi_prod READ ndvi_prod WRITE setNdvi_prod NOTIFY sig_wantedProducts_Changed)
    // attribute: checkbox ndwi
    Q_PROPERTY(bool ndwi_prod READ ndwi_prod WRITE setNdwi_prod NOTIFY sig_wantedProducts_Changed)
    // attribute: checkbox svi
    Q_PROPERTY(bool svi_prod READ svi_prod WRITE setSvi_prod NOTIFY sig_wantedProducts_Changed)
    // attribute: checkbox distance
    Q_PROPERTY(bool distance_prod READ distance_prod WRITE setDistance_prod NOTIFY sig_wantedProducts_Changed)
    // attribute: checkbox KT-transform bright wet green
    Q_PROPERTY(bool KT_prod READ KT_prod WRITE setKT_prod NOTIFY sig_wantedProducts_Changed)
    // attribute: checkbox dingluo
    Q_PROPERTY(bool dingluo_prod READ dingluo_prod WRITE setDingluo_prod NOTIFY sig_wantedProducts_Changed)
    // attribute: checkbox fengxian
    Q_PROPERTY(bool fengxian_prod READ fengxian_prod WRITE setFengxian_prod NOTIFY sig_wantedProducts_Changed)


public:
    //构造函数

    CCLogin();

    //解析函数

    ~CCLogin();

    // 用户名读取

    QString user_id();

    // 用户名设置

    void set_user_id(QString uid);

    // 密码读取

    QString password();

    // 密码设置

    void set_password(QString pwd);

    // 记住密码标志位读取

    bool flag_remember();

    // 记住密码标志位设置

    void set_flag_remember(bool isremember);

    // 自动登陆标志位读取

    bool flag_auto();

    /* read tiff file */
    QString file_tiff();
    /* set tiff file */
    void setFile_tiff(QString ft);

    /* read xml file */
    QString file_xml();
    /* set xml file */
    void setFile_xml(QString fx);

    /* read rpb file */
    QString file_rpb();
    /* set rpb file */
    void setFile_rpb(QString fr);

    /* read save directory */
    QString save_dir();
    /* set rpb file */
    void setSave_dir(QString sd);
    /* 自动登陆标志位设置 */
    void set_flag_auto(bool isauto);

    /* read ndvi wanted or not */
    bool ndvi_prod();
    /* set ndvi wanted */
    void setNdvi_prod(bool iswanted);

    /* read ndwi wanted or not */
    bool ndwi_prod();
    /* set ndwi wanted */
    void setNdwi_prod(bool iswanted);

    /* read svi wanted or not */
    bool svi_prod();
    /* set svi wanted */
    void setSvi_prod(bool iswanted);

    /* read KT wanted or not */
    bool distance_prod();
    /* set KT wanted */
    void setDistance_prod(bool iswanted);

    /* read KT wanted or not */
    bool KT_prod();
    /* set KT wanted */
    void setKT_prod(bool iswanted);

    /* read dingluo wanted or not */
    bool dingluo_prod();
    /* set dingluo wanted */
    void setDingluo_prod(bool iswanted);

    /* read fengxian wanted or not */
    bool fengxian_prod();
    /* set fengxian wanted */
    void setFengxian_prod(bool iswanted);


 signals:

    /* 用户名改变信号 */

    void sig_user_id_changed();
    /* 密码改变信号 */
    void sig_password_changed();
    /* 记住密码标志位改变 */
    void sig_flag_remember_changed();
    /* 自动登陆标志位改变 */
    void sig_flag_auto_changed();
    /* tiff file 改变 */
    void sig_file_tiffChanged();
    /* xml file 改变 */
    void sig_file_xmlChanged();
    /* rpb file 改变 */
    void sig_file_rpbChanged();
    /* save dir 改变 */
    void sig_save_dirChanged();

    void sig_wantedProducts_Changed(int s);

    /*********************************************************************
        *                           信号:登陆结果
        *参数:result:0:成功
        *           1:无此用户名
        *           2:密码错误
        *           3:达到登陆的最大次数
        **********************************************************************/

    void sig_login_result(int result);

    /***********信号：处理结果***********/
    void sig_process_result(int result);

    /*********************************************************************
      *                               发送网络帧
        *参数:id:用户名
        *    password:密码
        *    cmd:帧命令
        *    index:发送序列号
        *    frame:发送的报文
        **********************************************************************/

   // void sig_net_tx_frame_with_id(uint32_t id,uint32_t password,int cmd,uint16_t index,QByteArray frame);

    /************** signals for Image schedule **********************/
    void sig_for_schedule(QString q,QVariant s);

    void sig_select_file(int result);

public slots:
    /*********************************************************************
        *                           槽函数:登陆请求
        **********************************************************************/

    void slot_login_req();

    /*********************************************************************
    *                           槽函数:登陆响应
    *参数:data:接收的数据
    **********************************************************************/

   void slot_login_ack(QByteArray data);

   /*  finish select file and begin to process */
   void slot_finish_select();

   /*************cancel slot****************/
   void slot_cancel_process();

   /************* slot for schedule ************/

   void slot_for_schedule(QString q, QVariant s);

   void slot_for_fileDialog(int s);

private slots:

    /********************************************************************
    *       槽函数:心跳滴答函数,说明:1滴答触发1次
    *********************************************************************/
    void slot_tick();

private:
    /* 用户名 */
    QString _user_id;
    /* 密码 */
    QString _password;
    /* real username */
    QString user_id_real;
    /* real password */
    QString password_real;
    /* 记住密码标志位 */
    bool _flag_remember;
    /* 自动登录标志位 */
    bool _flag_auto;
    /* tiff file */
    QString _tiff_file;
    /* xml file */
    QString _xml_file;
    /* rpb file */
    QString _rpb_file;
    /* save dir */
    QString _save_dir;
    /*   滴答定时器 */
    QTimer *timer;
    /* 登录计数 */
    int login_counter;
    bool _flag_continue;
    bool wantedProducts[TOTAL_PRODUCTS];
};
#endif // CCLOGIN_H
