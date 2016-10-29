import QtQuick 2.4
import QtQuick.Window 2.2
Window {
    visible: true
    width:800
    height:400
    minimumHeight: 400
    maximumHeight: 400
    minimumWidth: 800
    maximumWidth: 800
    title: "Disease Control Image Process System"

    CCLogin {
        anchors.fill: parent
        visible:true
    //    mouseArea.onClicked: {
     //       Qt.quit();
     //   }
    }
    HomePage {
        anchors.fill: parent
        visible:false
    }
}
