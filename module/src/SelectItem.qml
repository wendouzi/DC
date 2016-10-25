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
            x: 30
            y: 60
            width: 100
            height: 40
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Tiff file")
            color: "#590606"
            font.pixelSize: 12
        }
        TextField {
            id: textInput1
            x: 140
            y: 60
            width: 200
            height: 40
            placeholderText: "Select \".tiff \" file"
            font.pixelSize: 12
        }
        Button {
            id: tiffselectbtn
            x: 400
            y: 60
            width: 40
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
            id: fileDialog
            title: "Please choose a file"
            visible: false
        }
    }

}
