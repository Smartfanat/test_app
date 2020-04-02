import QtQuick 2.0
import QtQuick.Controls 2.5

Switch {
    id: control

    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 26
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#17a81a" : "red"
        border.color: control.checked ? "#17a81a" : "#cccccc"

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            x: control.checked ? parent.width - width : 0
            width: 22
            height: 22
            radius: 13
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"
        }
    }
}
