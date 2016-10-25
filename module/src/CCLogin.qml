
import QtQuick 2.1
import Enginio 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import CCLogin 1.0
import QtQuick.Dialogs 1.1
Rectangle {
    id: login
    property alias mouseArea: mouseArea
    property bool processflag: false
    width: 800
    height: 400
    radius: 1
    border.color: "#590606"
    border.width: 2
    CCLogin
    {
        id:cclogin
        onSig_login_result:
        {
            //关闭登陆动画
            load_gif.opacity = 0

            //根据登陆结果处理
            switch (result)
            {
            //登陆成功
            case 0:
                loginUI.visible = false
                normalUI.visible = true
             //   messageDialog.text = "登陆成功"
             //   messageDialog.visible = true
                break;
            //无此用户名
            case 1:
                messageDialog.text = "登陆失败:无此用户名"
                messageDialog.visible = true
                break;
            //密码错误
            case 2:
                messageDialog.text = "登陆失败:密码错误"
                messageDialog.visible = true
                break;
            //达到最大登陆次数
            case 3:
                messageDialog.text = "登陆失败:达到最大登陆次数"
                messageDialog.visible = true
                break;
            case 4:
                loginUI.visible = false
                normalUI.visible = true
                break;
            }
        }
        onSig_process_result:
        {

            switch (result)
            {
            case 0:
                processflag = false
                //close process AnimatedImage
                process_gif.opacity = 0
                // btn active
                textInput1.readOnly = false
                textInput2.readOnly = false
                textInput3.readOnly = false
                textInput4.readOnly = false
                tiffselectbtn1.activeFocusOnPress = true
                tiffselectbtn2.activeFocusOnPress = true
                tiffselectbtn3.activeFocusOnPress = true
                tiffselectbtn4.activeFocusOnPress = true
                precessbtn.activeFocusOnPress = false
                messageDialog.text = "处理完成"
                messageDialog.visible = true
                break;
            case 1:
                process_gif.opacity = 0
                messageDialog.text = "tiff文件不存在或者路径有误"
                messageDialog.visible = true
                break;
            case 2:
                process_gif.opacity = 0
                messageDialog.text = "xml文件不存在或者路径有误"
                messageDialog.visible = true
                break;
            case 3:
                process_gif.opacity = 0
                messageDialog.text = "rpb文件不存在或者路径有误"
                messageDialog.visible = true
                break;
            case 4:
                process_gif.opacity = 0
                messageDialog.text = "输出文件夹不存在或者路径有误"
                messageDialog.visible = true
                break;
            case 5:
                // set process flag false
                processflag = true
                // btn disable
                precessbtn.activeFocusOnPress = false
                tiffselectbtn1.activeFocusOnPress = false
                tiffselectbtn2.activeFocusOnPress = false
                tiffselectbtn3.activeFocusOnPress = false
                tiffselectbtn4.activeFocusOnPress = false
                textInput1.readOnly = true
                textInput2.readOnly = true
                textInput3.readOnly = true
                textInput4.readOnly = true
                // open process AnimatedImage
                process_gif.opacity = 1
                break;
            case 6:
                process_gif.opacity = 0
                // signal when stop cancel
                processflag = false
                //close process AnimatedImage
                process_gif.opacity = 0
                // btn active
                textInput1.readOnly = false
                textInput2.readOnly = false
                textInput3.readOnly = false
                textInput4.readOnly = false
                tiffselectbtn1.activeFocusOnPress = true
                tiffselectbtn2.activeFocusOnPress = true
                tiffselectbtn3.activeFocusOnPress = true
                tiffselectbtn4.activeFocusOnPress = true
                precessbtn.activeFocusOnPress = false
                messageDialog.text = "取消成功"
                messageDialog.visible = true
                cclogin.slot_cancel_process()
                break
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: -2
        anchors.leftMargin: 0
        anchors.topMargin: 2
        anchors.fill: parent
    }

    BorderImage {
        id: background
        x: 2
        y: 2
        width: 796
        height: 396
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        opacity: 0.4
        visible: true
        clip: false
        source: "qrc:///home_bg.jpg"
        anchors.fill: parent
    }


    Item {
        id: loginUI
        anchors.fill: parent
        visible:true
        width: 800
        height: 400
    Text {
        id: welcome
        x:70
        y:50
        width: 388
        height: 35
      //  anchors.centerIn: parent
       // text: "Welcome to the Disease Control Image Processing System"
        text:qsTr("欢迎来到中国疾病控制预防中心遥感图像处理系统")
        font.pointSize: 16
        style: Text.Raised
        font.italic: true
    //    horizontalAlignment: Text.AlignHCenter
   //     verticalAlignment: Text.AlignVCenter
   //     font.pixelSize: 15
  //      anchors.verticalCenterOffset: -151
  //      anchors.horizontalCenterOffset: -85
    }

    Text {
        id: txtsignin
        x: 256
        y: 80
        width: 116
        height: 36
        color: "#0a4c15"
        text: qsTr("Please sign in !")
        font.italic: false
        font.bold: true
        font.family: "Times New Roman"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
        visible: false
    }

    TextField {
        id: username
        x: 286
        y: 132
        width: 122
        height: 30
        placeholderText: "Username"
        font.pixelSize: 12
    }

    TextField {
        id: password
        x: 286
        y: 182
        width: 122
        height: 30
        placeholderText: "Password"
        font.pixelSize: 12
        echoMode: 2
    }

    Text {
        id: usernametxt
        x: 173
        y: 132
        width: 82
        height: 30
        text: qsTr("用户名")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: 15
    }

    Text {
        id: passwordtxt
        x: 173
        y: 182
        width: 82
        height: 30
        text: qsTr("密码")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        font.pixelSize: 15
    }


    Button {
        id: loginbtn
        x: 173
        y: 236
        width: 235
        height: 32
        text: qsTr("登录")
        checkable: false
        antialiasing: false
        z: 0
        rotation: 0
        scale: 1
        clip: false
        activeFocusOnPress: true
        onClicked: trylogin()
    }
    }
    //消息框

    MessageDialog
    {
        id: messageDialog
        title: "May I have your attention please"
        text: "It's so cool that you are using Qt Quick."
        onAccepted: {
            console.log("And of course you could only agree.")
            messageDialog.visible = false
        }
        visible: false
       // Component.onCompleted: visible = true
    }
    //登陆动画
    AnimatedImage
    {
        id: load_gif; source: "qrc:///load.gif"
        anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
        z: 100
        opacity: 0
    }

    function trylogin() {
        // 判断用户名是否有效
        if (username.text == "")
        {
            messageDialog.text = "请输入用户名"
            messageDialog.visible = true
            return
        }
        // 判断密码是否有效
        if (password.text == "")
        {
            messageDialog.text = "请输入密码"
            messageDialog.visible = true
            return
        }
        // 显示登录动画
        load_gif.opacity = 1

        // 登录请求
        cclogin.user_id = username.text
        cclogin.password = password.text
      //  cclogin.flag_auto = CheckBox.selected
      //  cclogin.flag_auto = CheckBox.selected
        cclogin.slot_login_req()
    }
    Item {
        id: normalUI
        anchors.fill: parent
        visible:false
        width: 800
        height: 400
        Text {
            id: normalUIwelcome
            x:160
            y:20
            width: 480
            height: 40
          //  anchors.centerIn: parent
            text: "请选择高分影响和保存路径"
            font.pointSize: 16
            style: Text.Raised
            font.italic: true
        //    horizontalAlignment: Text.AlignHCenter
       //     verticalAlignment: Text.AlignVCenter
       //     font.pixelSize: 15
      //      anchors.verticalCenterOffset: -151
      //      anchors.horizontalCenterOffset: -85
        }
        BorderImage {
            id: normalUIbg
            x: 2
            y: 2
            width: 796
            height: 396
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            opacity: 0.4
            visible: true
            clip: false
            source: "qrc:///home_bg.jpg"
            anchors.fill: parent
        }
        Item {
            id: tiffpart

            Text {
                id: text1
                x: 160
                y: 80
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("Tiff file")
                color: "#590606"
                font.pixelSize: 12
            }
            TextField {
                id: textInput1
                x: 250
                y: 80
                width: 300
                height: 40
                placeholderText: "Select \".tiff \" file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn1
                x: 560
                y: 80
                width: 80
                height: 40
                text: qsTr("...")
                checkable: false
                antialiasing: false
                z: 0
                rotation: 0
                scale: 1
                clip: false
                activeFocusOnPress: true
                onClicked: fileDialog1.visible = true
            }
            FileDialog {
                id: fileDialog1
                title: "Please choose a .tiff file"
                selectFolder:false
                //selectedNameFilter:"*.tiff"
                visible: false
                onAccepted: {
                    cclogin.file_tiff = fileDialog1.fileUrl
                    textInput1.text = fileDialog1.fileUrl
                    fileDialog1.visible = false;
                }
                onRejected: {
                    fileDialog1.visible = false;
                }
            }
        }
        Item {
            id: xmlpart

            Text {
                id: text2
                x: 160
                y: 140
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("xml file")
                color: "#590606"
                font.pixelSize: 12
            }
            TextField {
                id: textInput2
                x: 250
                y: 140
                width: 300
                height: 40
                placeholderText: "Select \".xml \" file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn2
                x: 560
                y: 140
                width: 80
                height: 40
                text: qsTr("...")
                checkable: false
                antialiasing: false
                z: 0
                rotation: 0
                scale: 1
                clip: false
                activeFocusOnPress: true
                onClicked: fileDialog2.visible = true
            }
            FileDialog {
                id: fileDialog2
                title: "Please choose a .xml file"
                selectFolder:false
                visible: false
                onAccepted: {
                    cclogin.file_xml = fileDialog2.fileUrl
                    textInput2.text = fileDialog2.fileUrl
                    fileDialog2.visible = false;
                }
                onRejected: {
                    fileDialog2.visible = false;
                }
            }
        }
        Item {
            id: rpbpart

            Text {
                id: text3
                x: 160
                y: 200
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("rpb file")
                color: "#590606"
                font.pixelSize: 12
            }
            TextField {
                id: textInput3
                x: 250
                y: 200
                width: 300
                height: 40
                placeholderText: "Select \".rpb \" file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn3
                x: 560
                y: 200
                width: 80
                height: 40
                text: qsTr("...")
                checkable: false
                antialiasing: false
                z: 0
                rotation: 0
                scale: 1
                clip: false
                activeFocusOnPress: true
                onClicked: fileDialog3.visible = true
            }
            FileDialog {
                id: fileDialog3
                title: "Please choose a .rpb file"
                visible: false
                selectFolder:false
                onAccepted: {
                    cclogin.file_rpb = fileDialog3.fileUrl
                    textInput3.text = fileDialog3.fileUrl
                    fileDialog3.visible = false;
                }
                onRejected: {
                    fileDialog3.visible = false;
                }
            }
        }
        Item {
            id: savedir

            Text {
                id: text4
                x: 160
                y: 260
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("save directory")
                color: "#590606"
                font.pixelSize: 12
            }
            TextField {
                id: textInput4
                x: 250
                y: 260
                width: 300
                height: 40
                placeholderText: "Select output directory"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn4
                x: 560
                y: 260
                width: 80
                height: 40
                text: qsTr("...")
                checkable: false
                antialiasing: false
                z: 0
                rotation: 0
                scale: 1
                clip: false
                activeFocusOnPress: true
                onClicked: fileDialog4.visible = true
            }
            FileDialog {
                id: fileDialog4
                title: "Please choose a directory"
                visible: false
                selectFolder:true
                onAccepted: {
                    cclogin.save_dir = fileDialog4.fileUrl
                    textInput4.text = fileDialog4.fileUrl
                    fileDialog4.visible = false;
                }
                onRejected: {
                    fileDialog4.visible = false;
                }
            }
        }
        Button {
            id: precessbtn
            x: 400
            y: 320
            width: 200
            height: 40
            text: qsTr("OK")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true    
            //onClicked: tryfinishselect()
            onClicked: tryfinishselect()
            opacity: 0.5
        }
        Button {
            id: cancelbtn
            x: 500
            y: 100
            width: 80
            height: 40
            text: qsTr("Cancel")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true
            visible: processflag
            onClicked:cclogin.slot_cancel_process()
        }
    }
    //登陆动画
    AnimatedImage
    {
        id: process_gif; source: "qrc:///process.gif"
        anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
        z: 100
        opacity: 0
    }


    function tryfinishselect() {

        // 判断tiff是否为空
        if(textInput1.text == "")
        {
            messageDialog.text = "请选择高分tiff文件"
            messageDialog.visible = true
            return
        }
        // 判断xml是否为空
        if (textInput2.text == "")
        {
            messageDialog.text = "请选择高分xml文件"
            messageDialog.visible = true
            return
        }
        // 判断rpb是否为空
        if (textInput3.text == "")
        {
            messageDialog.text = "请选择高分rpb文件"
            messageDialog.visible = true
            return
        }
        // 判断save dir是否为空
        if (textInput4.text == "")
        {
            messageDialog.text = "请选择输出路径"
            messageDialog.visible = true
            return
        }
        // 处理图像动画
        process_gif.opacity = 1
        //处理请求
        cclogin.file_tiff = textInput1.text
        cclogin.file_xml = textInput2.text
        cclogin.file_rpb = textInput3.text
        cclogin.save_dir = textInput4.text
        cclogin.slot_finish_select();
    }

}
