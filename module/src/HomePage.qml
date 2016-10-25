import QtQuick 2.4
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
Item {
    width: 800
    height: 400
    property alias mouseArea: mouseArea
    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: -2
        anchors.leftMargin: 0
        anchors.topMargin: 2
        anchors.fill: parent
    }
    Text {
        id: welcome
        x:160
        y:20
        width: 480
        height: 40
      //  anchors.centerIn: parent
        text: "Please select the Gaofen image and result folder!"
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
        source: "home_bg.jpg"
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
        }
        FileDialog {
            id: fileDialog1
            title: "Please choose a .tiff file"
            visible: false
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
        }
        FileDialog {
            id: fileDialog2
            title: "Please choose a .xml file"
            visible: false
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
        }
        FileDialog {
            id: fileDialog3
            title: "Please choose a .rpb file"
            visible: false
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
        }
        FileDialog {
            id: fileDialog4
            title: "Please choose a directory"
            visible: false
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
    }

}
