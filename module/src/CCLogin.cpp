
#include "CCLogin.h"
#include "QString"
#include "base64.h"
#include "QTextStream"
#include "QDebug"
#include "QThread"
#include "ischedule.h"
#include "CCBaseTypeDefine.h"

#define config_file QString("config.txt")
const QString _init_user_name = "123";
const QString _init_password = "123";
const bool _init_rememberflag = false;
const bool _init_autoflag = false;
CCLogin::CCLogin(): _user_id("")
  , _password("")
  , _flag_auto(false)
  , _flag_remember(false)
  , login_counter(0)
{
    qDebug("CCLogin constructor");
    /* 滴答初始化 */
    timer = new QTimer(this);
    /* 绑定信号槽 */
    if(!connect(timer,SIGNAL(timeout()), this, SLOT(slot_tick()))) {
        qDebug("timer connect failed");
    }
    QFile file_cfg(config_file);

    QString str;

    if (!file_cfg.exists())
    {
        qDebug("%s does not exist!\n",config_file.toStdString().c_str());

        user_id_real = _init_user_name;
        password_real = _init_password;
        _flag_remember = _init_rememberflag;
        _flag_auto = _init_autoflag;
        file_cfg.close();
   }
    else
    {
        qDebug("read %s !\n",config_file.toStdString().c_str());
        file_cfg.open(QIODevice::ReadOnly);
        QTextStream in(&file_cfg);
        //读取文件
        do
        {
            str.clear();
            std::string s;
           // QString qs;
            /* 从配置文件中读取用户名，第一行 */
            s = in.readLine().toStdString();
         //   printf("username:%s\n",s.c_str());
            std::string stemp = Base64::base64_decode(s);
          //  printf("username decode :%s\n",stemp.c_str());
            user_id_real = QString::fromStdString(Base64::base64_decode(s));
           // printf("username decode :%s\n",user_id_real.toStdString().c_str());
            // 从配置文件中读取密码，第二行 //
            s="";
            s = in.readLine().toStdString();
            password_real = QString::fromStdString(Base64::base64_decode(s));
          //  printf("password decode :%s\n",password_real.toStdString().c_str());
            // 从配置文件中读取记住密码标志位，第三行 //
            s="";
            s = in.readLine().toStdString();
            QString flag_rem_temp = QString::fromStdString(Base64::base64_decode(s));
            _flag_remember = flag_rem_temp.toInt() == 1 ? true : false;
            // 从配置文件中读取自动登录标志位，第四行 //
            s="";
            s = in.readLine().toStdString();
            QString flag_auto_temp = QString::fromStdString(Base64::base64_decode(s));
            _flag_auto = flag_auto_temp.toInt() == 1 ? true : false;
/*
 *           printf(" username:%s\n password :%s \n remember password:%s\n auto login:%s\n",
 *                 _user_id.toStdString().c_str(),_password.toStdString().c_str(),
 *                 _flag_remember ? "true" : "false", _flag_auto ? "true" : "false"
 *                 );
*/
            // if remember password
            if(_flag_remember) {
                // show the username and password

            }
            if (_flag_auto) {

            }

        } while (0);

        file_cfg.close();
    }
    connect(this,SIGNAL(sig_for_schedule(QString,QVariant)),SCHEDULE,SLOT(slot_for_UI(QString,QVariant)));
    connect(SCHEDULE,SIGNAL(sig_to_UI(QString,QVariant)),this,SLOT(slot_for_schedule(QString,QVariant)));
}

/* 析构函数*/
CCLogin::~CCLogin()
{
    qDebug("CCLogin::~CCLogin()");
    disconnect(this,SIGNAL(sig_for_schedule(QString,QVariant)),SCHEDULE,SLOT(slot_for_UI(QString,QVariant)));
    disconnect(SCHEDULE,SIGNAL(sig_to_UI(QString,QVariant)),this,SLOT(slot_for_schedule(QString,QVariant)));
    login_counter = 0;
}

/* 读取用户名 */
QString CCLogin::user_id()
{
    return _user_id;
}

/* 写入用户名 */
void CCLogin::set_user_id(QString uid)
{
    _user_id = uid;
}

/* 读取密码 */
QString CCLogin::password()
{
    return _password;
}
/* 写入密码 */
void CCLogin::set_password(QString pwd)
{
    _password = pwd;
}
/* 记住密码标志位读取 */
bool CCLogin::flag_remember()
{
    return _flag_remember;
}

/* 记住密码标志位设置 */
void CCLogin::set_flag_remember(bool isremember)
{
    _flag_remember = isremember;
}

/* 自动登陆标志位读取 */
bool CCLogin::flag_auto()
{
    return _flag_auto;
}

/* 自动登陆标志位设置 */
void CCLogin::set_flag_auto(bool isauto)
{
    _flag_auto = isauto;
}

/* read tiff file */
QString CCLogin::file_tiff()
{
    return _tiff_file;
}

/* set tiff file */
void CCLogin::setFile_tiff(QString ft)
{
    _tiff_file = ft;
}

/* read xml file */
QString CCLogin::file_xml()
{
    return _xml_file;
}
/* set xml file */
void CCLogin::setFile_xml(QString fx)
{
    _xml_file = fx;
}


/* read rpb file */
QString CCLogin::file_rpb()
{
    return _rpb_file;
}

/* set rpb file */
void CCLogin::setFile_rpb(QString fr)
{
    _rpb_file = fr;
}

/* read save directory */
QString CCLogin::save_dir()
{
    return _save_dir;
}

/* set rpb file */
void CCLogin::setSave_dir(QString sd)
{
    _save_dir = sd;
}

/* read ndvi wanted or not */
bool CCLogin::ndvi_prod()
{
   return  wantedProducts[NDVI_ORDER];
}

/* set ndvi wanted */
void CCLogin::setNdvi_prod(bool iswanted)
{
    wantedProducts[NDVI_ORDER] = iswanted;
}

/* read ndwi wanted or not */
bool CCLogin::ndwi_prod()
{
   return  wantedProducts[NDWI_ORDER];
}

/* set ndwi wanted */
void CCLogin::setNdwi_prod(bool iswanted)
{
    wantedProducts[NDWI_ORDER] = iswanted;
}

/* read svi wanted or not */
bool CCLogin::svi_prod()
{
   return  wantedProducts[SVI_ORDER];
}

/* set svi wanted */
void CCLogin::setSvi_prod(bool iswanted)
{
    wantedProducts[SVI_ORDER] = iswanted;
}

/* read distance wanted or not */
bool CCLogin::distance_prod()
{
    return wantedProducts[DISTANCE_ORDER] ;
}

/* set distance wanted */
void CCLogin::setDistance_prod(bool iswanted)
{
    wantedProducts[DISTANCE_ORDER] = iswanted;
}

/* read KT wanted or not */
bool CCLogin::KT_prod()
{
   return  wantedProducts[KT_ORDER];
}

/* set KT wanted */
void CCLogin::setKT_prod(bool iswanted)
{
    wantedProducts[KT_ORDER] = iswanted;
}

/* read dingluo wanted or not */
bool CCLogin::dingluo_prod()
{
   return  wantedProducts[DINGLUO_ORDER];
}

/* set dingluo wanted */
void CCLogin::setDingluo_prod(bool iswanted)
{
    wantedProducts[DINGLUO_ORDER] = iswanted;
}

/* read fengxian wanted or not */
bool CCLogin::fengxian_prod()
{
   return  wantedProducts[FENGXIAN_ORDER];
}

/* set fengxian wanted */
void CCLogin::setFengxian_prod(bool iswanted)
{
    wantedProducts[FENGXIAN_ORDER] = iswanted;
}

/*  槽函数登录请求 */
void CCLogin::slot_login_req()
{
    printf("CCLogin::slot_tick()\n");
    //计数器加1 //
    login_counter++;
    // 判断登录次数 //
    if (login_counter < NUM_LOGIN) {
        // 判断用户名是否正确 //
        if (0 == QString::compare(user_id_real, _user_id)) {
            // 判断密码是否正确 //
            if(0 == QString::compare(password_real, _password)) {
                emit sig_login_result(0); // 用户名和密码都正确 //
            }
            else {
                emit sig_login_result(2);// 密码错误 //
            }
        }
        else {
            emit sig_login_result(1); // 无此用户名 //
        }
    }
    else {
        emit sig_login_result(3);
    }
}
/*********************************************************************
*                           槽函数:心跳滴答函数 *说明:1滴答触发1次
**********************************************************************/

void CCLogin::slot_tick()
{
    qDebug("CCLogin::slot_tick() %d ms has end\n", INTERVAL_LOGIN);
    emit sig_process_result(6);
    timer->stop();
}

/*********************************************************************
*                           槽函数:登陆响应
*                         参数:data:接收的数据
**********************************************************************/

void CCLogin::slot_login_ack(QByteArray data)
{

}

/****** 槽函数： 完成选择，开始处理响应********/
/* signal 0: sucess
 * signal 1: wrong tiff file
 * signal 2: wrong xml  file
 * signal 3: wrong rpb file
 * signal 4: wrong save directory
 **/
void CCLogin::slot_finish_select()
{

    qDebug("CCLogin::slot_finish_select\n");
    qDebug("tiff file: %s \n",_tiff_file.toStdString().c_str());
    qDebug("xml file: %s \n",_xml_file.toStdString().c_str());
    qDebug("rpb file: %s \n",_rpb_file.toStdString().c_str());
    qDebug("save dir: %s \n",_save_dir.toStdString().c_str());
    if(QFile::exists(_tiff_file) && _tiff_file.endsWith(".tiff")) {

        if(QFile::exists(_xml_file) && _xml_file.endsWith(".xml")) {

            if(QFile::exists(_rpb_file) && _rpb_file.endsWith(".rpb")) {

                QDir msdir(_save_dir);
                if(msdir.exists()) {
                    _flag_continue = true;
                    emit sig_process_result(5);
                    // begin to process
                    QMap<QString,QVariant> qm;
                    QVariant qv;
                    qm.insert(TIFF_FILE_NAME,QVariant(_tiff_file));
                    qm.insert(XML_FILE_NAME,QVariant(_xml_file));
                    qm.insert(RPB_FILE_NAME,QVariant(_rpb_file));
                    qm.insert(SAVE_DIR_NAME,QVariant(_save_dir));
                    qv = QVariant(qm);
                    emit sig_for_schedule(REQ_IMG_PRO_START,qv);
                }
                else {
                    emit sig_process_result(4);
                }
            }
            else {
                emit sig_process_result(3);
            }
        }
        else {
            emit sig_process_result(2);
        }
    }
    else {
        emit sig_process_result(1); // tiff file is not correct
    }
}

/********cancel process****************/
void CCLogin::slot_cancel_process()
{
    qDebug("CCLogin::slot_cancel_process");

    QVariant q;
    emit sig_for_schedule(REQ_IMG_PRO_CANCEL,q);
    if(_flag_continue) {
        qDebug("timer begin to time");
        timer->start(INTERVAL_LOGIN);
    }
    _flag_continue = false;
}

void CCLogin::slot_for_schedule(QString q, QVariant s) {
    qDebug("CCLogin::slot_for_schedule");
    QVariantMap qvm;
    if(0 == q.compare(RES_IMG_PRO_START)) {
        qDebug("CCLogin::slot_for_schedule, %s",RES_IMG_PRO_START.toStdString().c_str());
    }
    else if (0 == q.compare(RES_IMG_PRO_STOP)) {
        qDebug("CCLogin::slot_for_schedule, %s",RES_IMG_PRO_STOP.toStdString().c_str());
    }
    else if (0 == q.compare(RES_IMG_PRO_CANCEL)) {
        qDebug("CCLogin::slot_for_schedule, %s",RES_IMG_PRO_CANCEL.toStdString().c_str());
        emit sig_process_result(6);
    }
    else if (0 == q.compare(RES_IMG_PRO_FINISH)) {
        qDebug("CCLogin::slot_for_schedule, %s",RES_IMG_PRO_FINISH.toStdString().c_str());
        emit sig_process_result(0);
    }
    else if (0 == q.compare(RES_IMG_PRO_FAILED)) {
        qDebug("CCLogin::slot_for_schedule, %s",RES_IMG_PRO_FAILED.toStdString().c_str());
    }
}

void CCLogin::slot_for_fileDialog(int s) {
    qDebug("CCLogin::slot_for_fileDialog(%d)",s);
    if(s == TIFF_FILEDIALOG) {
        _tiff_file = _tiff_file.mid(DIR_BEGIN);
        QString temp_xml_file = _tiff_file;
        QString temp_rpb_file = _tiff_file;
        temp_xml_file.replace(".tiff",".xml");
        temp_rpb_file.replace(".tiff",".rpb");
        if (QFile::exists(temp_xml_file)) {
            _xml_file = temp_xml_file;
            qDebug("xml file: %s \n",_xml_file.toStdString().c_str());
            emit sig_select_file(XML_FILEDIALOG);
        }
        if (QFile::exists(temp_rpb_file)) {
            _rpb_file = temp_rpb_file;
            qDebug("rpb file: %s \n",_rpb_file.toStdString().c_str());
            emit sig_select_file(RPB_FILEDIALOG);
        }
        qDebug("tiff file: %s \n",_tiff_file.toStdString().c_str());
        emit sig_select_file(TIFF_FILEDIALOG);
    }
    else if (s == XML_FILEDIALOG) {
        _xml_file = _xml_file.mid(DIR_BEGIN);
        qDebug("tiff file: %s \n",_xml_file.toStdString().c_str());
        emit sig_select_file(XML_FILEDIALOG);
    }
    else if (s == RPB_FILEDIALOG) {
        _rpb_file = _rpb_file.mid(DIR_BEGIN);
        qDebug("tiff file: %s \n",_rpb_file.toStdString().c_str());
        emit sig_select_file(RPB_FILEDIALOG);
    }
    else if (s == SDIR_FILEDIALOG) {
        _save_dir = _save_dir.mid(DIR_BEGIN);
        qDebug("tiff file: %s \n",_save_dir.toStdString().c_str());
        emit sig_select_file(SDIR_FILEDIALOG);
    }
}
