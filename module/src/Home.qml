import QtQuick 2.4
import QtQuick.Window 2.2
Window {
    id:mainwindow
    visible: true
    width:960
    height:480
    minimumHeight: 480
    maximumHeight: 480
    minimumWidth: 960
    maximumWidth: 960
    title: "Disease Control Image Process System"

    CCLogin {
        anchors.fill: parent
        visible:true
    }
    HomePage {
        anchors.fill: parent
        visible:false
    }

}


