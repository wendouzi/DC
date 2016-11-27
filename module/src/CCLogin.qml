
import QtQuick 2.1
import Enginio 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.0
import CCLogin 1.0
import CCPreviewPainter 1.0
import QtQuick.Dialogs 1.1
import CCPreview 1.0
Rectangle {
    id: login
    anchors.fill: parent
    //property alias mouseArea: mouseArea
    property bool processflag: false
    radius: 1
    border.color: "#590606"
    border.width: 2
    CCLogin
    {
        id:cclogin
        objectName: "CCLoginUI"
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
            // process done
            case 0:
                processflag = false
                //close process AnimatedImage
                process_gif.opacity = 0
                // btn active
                textInput1.enabled = true
                textInput2.enabled = true
                textInput3.enabled = true
                textInput4.enabled = true
                textInput5.enabled = true
                outputproducts.enabled = true
                tiffselectbtn1.enabled = true
                tiffselectbtn2.enabled = true
                tiffselectbtn3.enabled = true
                tiffselectbtn4.enabled = true
                tiffselectbtn5.enabled = true
                precessbtn.enabled = true
                messageDialog.text = "处理完成"
                messageDialog.visible = true
                break;
            // tiff error
            case 1:
                process_gif.opacity = 0
                messageDialog.text = "tiff文件不存在或者路径有误"
                messageDialog.visible = true
                break;
            // xml error
            case 2:
                process_gif.opacity = 0
                messageDialog.text = "xml文件不存在或者路径有误"
                messageDialog.visible = true
                break;
            // rpb error
            case 3:
                process_gif.opacity = 0
                messageDialog.text = "rpb文件不存在或者路径有误"
                messageDialog.visible = true
                break;
            // save dir error
            case 4:
                process_gif.opacity = 0
                messageDialog.text = "输出文件夹不存在或者路径有误"
                messageDialog.visible = true
                break;
            // processing
            case 5:
                // set process flag true
                processflag = true
                // btn disable
                precessbtn.enabled = false
                tiffselectbtn1.enabled = false
                tiffselectbtn2.enabled = false
                tiffselectbtn3.enabled = false
                tiffselectbtn4.enabled = false
                tiffselectbtn5.enabled = false
                outputproducts.enabled = false
                textInput1.enabled = false
                textInput2.enabled = false
                textInput3.enabled = false
                textInput4.enabled = false
                textInput5.enabled = false
                // open process AnimatedImage
                process_gif.opacity = 1
                break;
            // cancel process
            case 6:
                process_gif.opacity = 0
                // signal when stop cancel
                processflag = false
                //close process AnimatedImage
                process_gif.opacity = 0
                // btn active
                textInput1.enabled = true
                textInput2.enabled = true
                textInput3.enabled = true
                textInput4.enabled = true
                textInput5.enabled = true
                tiffselectbtn1.enabled = true
                tiffselectbtn2.enabled = true
                tiffselectbtn3.enabled = true
                tiffselectbtn4.enabled = true
                tiffselectbtn5.enabled = true
                outputproducts.enabled = true
                precessbtn.enabled = true
                messageDialog.text = "取消成功"
                messageDialog.visible = true
                //cclogin.slot_cancel_process()
                break;
            // none products selected
            case 7:
                process_gif.opacity = 0
                messageDialog.text = "没有选中任何产品"
                messageDialog.visible = true
                break;
            default:
                break;
            }
        }

        onSig_select_file:
        {
            switch (result)
            {
            case 1:
                textInput1.text = file_tiff
                break;
            case 2:
                textInput2.text = file_xml
                break;
            case 3:
                textInput3.text = file_rpb
                break;
            case 4:
                textInput4.text = save_dir
                break;
            case 5:
                textInput5.text = file_poi
            }
        }
    }
   /*
    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: -2
        anchors.leftMargin: 0
        anchors.topMargin: 2
    }
*/
    BorderImage {
        id: background
        anchors.rightMargin: 0
        anchors.bottomMargin: -2
        anchors.leftMargin: 0
        anchors.topMargin: 2
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
    Text {
        id: titleCN
        x:parent.width/2 - 150
        y:30
        width: 300
        height: 18
        text:qsTr("    中 国 疾 病 控 制 预 防 中 心   ")
        font.pointSize: 16
        style: Text.Raised
        anchors.centerIn: titleCN
        font.bold: true
        //font.italic: true
    }
    Text {
        id: titleLine
        x:parent.width/2 - 150
        y:50
        width: 300
        height: 10
        text:qsTr("===========================================")
        font.pointSize: 8
        style: Text.Raised
        anchors.centerIn: titleLine
        //font.italic: true
    }
    Text {
        id: titleEN
        x:parent.width/2 - 150
        y:65
        width: 300
        height: 15
        text:qsTr("CHINESE CENTER FOR DISEASE CONTROL ADN PREVENTION")
        font.pointSize: 12
        style: Text.Raised
        anchors.centerIn: titleEN
        font.family: "Times"
        font.bold: true
        //font.italic: true
    }

    Text {
        id: usernametxt
        x: parent.width/2 - 100
        y: 132
        width: 100
        height: 30
        text: qsTr("用户名")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        font.pixelSize: 15
    }

    Text {
        id: passwordtxt
        x: parent.width/2 -100
        y: 182
        width: 100
        height: 30
        text: qsTr("密码")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        font.pixelSize: 15
    }
    TextField {
        id: username
        x: parent.width/2
        y: 132
        width: 100
        height: 30
        placeholderText: "Username"
        font.pixelSize: 12
    }

    TextField {
        id: password
        x: parent.width/2
        y: 182
        width: 100
        height: 30
        placeholderText: "Password"
        font.pixelSize: 12
        echoMode: 2
    }

    Button {
        id: loginbtn
        x: parent.width/2 - 100
        y: 236
        width: 200
        height: 32
        text: qsTr("   登    录   ")
        checkable: false
        antialiasing: false
        z: 0
        rotation: 0
        scale: 1
        clip: false
        activeFocusOnPress: true
        onClicked: trylogin()
    }
    Item {
        Text {
            id: introduction
            x:470
            y:100
            width: 300
            height: 280
            text:qsTr(" 血吸虫病是一种严重危害人类健康的疾病，钉螺是在我国流行的日本血吸虫唯一的中间宿主，消灭钉螺是阻断血吸虫病传播的最有效措施。高分影像能够实时地提供地表的有效地物信息、并可进行综合分析，为快速确定钉螺可孽生的位置、面积及扩散趋势提供了重要的监测手段。")
            font.pixelSize: 20
            style: Text.Raised
            wrapMode: Text.Wrap
            lineHeight: 1.2
            visible: false
        }
        Text {
            id: copyright
            x:60
            y:440
            width: 800
            height: 25
            text:qsTr("Copyright © 2016 Powered By Chinese Center for Disease Control and Prevention. All rights reserved.")
            font.pixelSize: 14
            style: Text.Raised
            opacity: 0.5
        }
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
        Text {
            id: normalUIwelcome
            x:60
            y:20
            width: 480
            height: 40
          //  anchors.centerIn: parent
            text: "请选择高分影像和输出路径"
            font.pixelSize: 20
            font.bold: true
            style: Text.Raised
           // font.italic: true
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
            anchors.fill:parent
            opacity: 0.4
            visible: true
            clip: false
            source: "qrc:///home_bg.jpg"
        }
        Item {
            id: tiffpart

            Text {
                id: text1
                x: 40
                y: 60
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("选择Tiff文件")
                color: "#590606"
                font.pixelSize: 14
            }
            TextField {
                id: textInput1
                x: 140
                y: 60
                width: 200
                height: 40
                readOnly: false
                placeholderText: "Select \".tiff \" file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn1
                x: 360
                y: 60
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
                nameFilters: ["Image Files (*.tiff)"];
                selectFolder:false
                //selectedNameFilter:"*.tiff"
                visible: false
                onAccepted: {
                    cclogin.file_tiff = fileDialog1.fileUrl
                    cclogin.slot_for_fileDialog(1);
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
                x: 40
                y: 120
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("选择xml文件")
                color: "#590606"
                font.pixelSize: 14
            }
            TextField {
                id: textInput2
                x: 140
                y: 120
                width: 200
                height: 40
                readOnly: false
                placeholderText: "Select \".xml \" file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn2
                x: 360
                y: 120
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
                nameFilters: ["Image Files (*.xml)"];
                selectFolder:false
                visible: false
                onAccepted: {
                    cclogin.file_xml = fileDialog2.fileUrl
               //     textInput2.text = fileDialog2.fileUrl
                    cclogin.slot_for_fileDialog(2);
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
                x: 40
                y: 180
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("选择RPB文件")
                color: "#590606"
                font.pixelSize: 14
            }
            TextField {
                id: textInput3
                x: 140
                y: 180
                width: 200
                height: 40
                readOnly: false
                placeholderText: "Select \".rpb \" file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn3
                x: 360
                y: 180
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
                nameFilters: ["Image Files (*.rpb)"];
                visible: false
                selectFolder:false
                onAccepted: {
                    cclogin.file_rpb = fileDialog3.fileUrl
              //      textInput3.text = fileDialog3.fileUrl
                    cclogin.slot_for_fileDialog(3);
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
                x: 40
                y: 240
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("选择输出文件夹")
                color: "#590606"
                font.pixelSize: 14
            }
            TextField {
                id: textInput4
                x: 140
                y: 240
                width: 200
                height: 40
                readOnly: false
                placeholderText: "Select output directory"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn4
                x: 360
                y: 240
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
              //      textInput4.text = fileDialog4.fileUrl
                    cclogin.slot_for_fileDialog(4);
                    fileDialog4.visible = false;
                }
                onRejected: {
                    fileDialog4.visible = false;
                }
            }
        }
        Item {
            id: poi

            Text {
                id: text5
                x: 40
                y: 340
                width: 80
                height: 40
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: qsTr("兴趣点经纬度")
                color: "#590606"
                font.pixelSize: 14
            }
            TextField {
                id: textInput5
                x: 140
                y: 340
                width: 200
                height: 40
                readOnly: false
                placeholderText: "Select POI (.txt)file"
                font.pixelSize: 12
            }
            Button {
                id: tiffselectbtn5
                x: 360
                y: 340
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
                onClicked: fileDialog5.visible = true
            }
            FileDialog {
                id: fileDialog5
                title: "Please choose a POI(.txt) file"
                nameFilters: ["Image Files (*.txt)"];
                visible: false
                selectFolder:false
                onAccepted: {
                    cclogin.file_poi = fileDialog5.fileUrl
              //      textInput4.text = fileDialog4.fileUrl
                    cclogin.slot_for_fileDialog(5);
                    fileDialog5.visible = false;
                }
                onRejected: {
                    fileDialog5.visible = false;
                }
            }
        }
/*
        Component{
            id: checkStyle

            CheckBoxStyle{

                indicator: Rectangle{
                    implicitWidth: 18;
                    implicitHeight: 18;
                    border.color: control.hovered? "darkblue":"gray";
                    border.width: 1;
                    Canvas{
                        anchors.fill: parent;
                        anchors.margins: 3;
                        visible: control.checked;
                        onPaint: {

                            var ctx = getContext("2d");
                            ctx.save();
                            ctx.strokeStyle = "#c00020";
                            ctx.lineWidth = 2;
                            ctx.beginPath();
                            ctx.moveTo(0,height/2);
                            ctx.lineTo(width/3 , height);
                            //ctx.moveTo(0 , height);
                            ctx.lineTo(width , 0);
                            ctx.stroke();
                            ctx.restore();
                        }
                    }
                }


                label: Text{
                    color: control.checked ?"blue":"black";
                    text: control.text;

                }

            }

        }
*/
        Column {
            id: outputproducts
            x: 40
            y: 300
            width: 300
            height: 70
            spacing: 10
            Row {
                CheckBox {
                    id:ndviproduct
                    text: qsTr("NDVI")
                   // style: checkStyle
                    checked: cclogin.ndvi_prod
                }
                CheckBox {
                    id:ndwiproduct
                    text: qsTr("NDWI")
                   // style: checkStyle
                    checked: cclogin.ndwi_prod
                }
                CheckBox {
                    id:sviproduct
                    text: qsTr("SVI")
                   // style: checkStyle
                    checked: cclogin.svi_prod
                }
                CheckBox {
                    id:distanceproduct
                    text: qsTr("与水距离")
                   // style: checkStyle
                    checked: cclogin.distance_prod
                }
            }
            Row {
                CheckBox {
                    id:ktproduct
                    text: qsTr("缨帽变换")
                   // style: checkStyle
                    checked: cclogin.KT_prod
                }

                CheckBox {
                    id:dingluoproduct
                    text: qsTr("钉螺预测")
                  //  style: checkStyle
                    checked: cclogin.dingluo_prod
                }
                CheckBox {
                    id:fengxianproduct
                    text: qsTr("风险评估")
                  //  style: checkStyle
                    checked: cclogin.fengxian_prod
                }
            }
        }

        Button {
            id: precessbtn
            x: 40
            y: 400
            width: 120
            height: 40
            text: qsTr("开始处理")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true    
            //onClicked: tryfinishselect()
            onClicked: tryfinishselect()
            opacity: 1
        }
        Button {
            id: cancelbtn
            x: 200
            y: 400
            width: 120
            height: 40
            text: qsTr("取消")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true
            //visible: processflag
            visible : true
            enabled:processflag
            onClicked:cclogin.slot_cancel_process()
        }
        Button {
            id: poiselectbtn
            x: 360
            y: 400
            width: 80
            height: 40
            text: qsTr("区域统计")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true
            //visible: processflag
            visible : true
            enabled: false
            //onClicked:{}
        }
        Button {
            id: beforepreviewbtn
            x: 200
            y: 400
            width: 80
            height: 40
            text: qsTr("预览")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true
            //visible: processflag
            visible : false
            enabled: false
            //onClicked:{}
        }
        Button {
            id: afterpreviewbtn
            x: 300
            y: 400
            width: 120
            height: 40
            text: qsTr("结果预览")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true
            //visible: processflag
            visible : false
            enabled: false
            //onClicked:{}
        }
        Button {
            id: comparepreviewbtn
            x: 400
            y: 400
            width: 80
            height: 40
            text: qsTr("影像对比")
            checkable: false
            antialiasing: false
            z: 0
            rotation: 0
            scale: 1
            clip: false
            activeFocusOnPress: true
            //visible: processflag
            visible : false
            enabled: false
            //onClicked:{}
        }

        Item {
           id:preview
           x:500 //476
           y:40
           width: painter.previewwidth+4
           height: painter.previewheight+4
           visible: true



           Rectangle {
               anchors.fill: parent
               border.width: 2
               border.color: "darkblue"
           }
           Text {
               x:parent.width/2 - 60
               y:parent.height/2 - 30
               width:60
               height:60
               text:qsTr("图像操作区")
               font.italic: true
               color:"#590606"
               font.pointSize: 20
           }
           CCPreview {
               objectName: "CCPreviewer"
               x:2
               y:2
               id:previewer
               anchors.fill: parent
           }
           CCPainter {
               objectName: "CCPainter"
               x:2
               y:2
               id:painter
               anchors.fill: parent
           }
       }

 /*
        Rectangle{
            id: preview
            x: 650
            y: 100
            implicitWidth: 100;
            implicitHeight: 100;
            //border.color: control.hovered? "darkblue":"gray";
            border.width: 1;
            Image {
               anchors.fill: parent
               //source:"qrc:///preview/gf_preview22"
            }

            Canvas{
                anchors.fill: parent;
                anchors.margins: 3;
                visible: tru
            }
        }
*/

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
        cclogin.file_poi = textInput5.text
        cclogin.ndvi_prod = ndviproduct.checked
        cclogin.ndwi_prod = ndwiproduct.checked
        cclogin.svi_prod = sviproduct.checked
        cclogin.distance_prod = distanceproduct.checked
        cclogin.KT_prod = ktproduct.checked
        cclogin.dingluo_prod = dingluoproduct.checked
        cclogin.fengxian_prod = fengxianproduct.checked
        cclogin.slot_finish_select();
    }

}
