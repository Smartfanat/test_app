import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Rectangle{
    id: root
    property string source: ""
    property string textImage: ""

    Rectangle {
        visible: textImage.length>0
        color: "lightblue"
        anchors.fill: parent
        radius: Math.min(width, height)
        Text {
            font.pointSize: textImage.length>0 ? root.height == 0 ? 1 : root.height*0.4 : 1
            anchors.centerIn: parent
            text: textImage
        }
    }

    Image {
        id: img
        anchors.fill: parent
        visible: textImage.length<1

        layer.enabled: true
        source: parent.source

        layer.effect: OpacityMask {
            maskSource: Item {
                width: img.width
                height: img.height
                Rectangle {
                    anchors.centerIn: parent
                    width: img.adapt ? img.width : Math.min(img.width, img.height)
                    height: img.adapt ? img.height : width
                    radius: Math.min(width, height)
                }
            }
        }
    }
}
