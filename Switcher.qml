import QtQuick 2.0
import QtQuick.Controls 2.5

Switch {
    id: control

    indicator: Rectangle {
        implicitHeight: 26
        implicitWidth: implicitHeight*2
        radius: parent.width/3
        color: control.checked ? "#17a81a" : "red"
        border.color: control.checked ? "#17a81a" : "#cccccc"

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            x: control.checked ? parent.width - width : 0
            width: parent.width/2
            height: parent.height*0.8
            radius: parent.width/3
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
        }
    }
}
