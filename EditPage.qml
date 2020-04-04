import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: editPage

    property bool active: false
    property string projectName: ""
    property string logoUrl: ""
    property bool  isWatcher: false
    property int id: 0

    color: "#F4F4F4"

    Rectangle {
        id: rect

        color: "white"

        width: parent.width
        height: parent.height*0.1

        Rectangle {
            width: parent.width/3
            height: parent.height
            anchors.right: parent.right
            color: parent.color

            RowLayout{
                anchors.fill: parent
                spacing: parent.width/50
                Button{
                    text: qsTr("PROJECTS")
                    Layout.preferredWidth: parent.width/2.5
                    onClicked: {
                        controller.getProjects()
                        loader.setSource("Projects.qml")
                    }
                }
                Button{
                    Layout.preferredWidth: parent.width/2.5
                    text: qsTr("LOGOUT")
                    onClicked: {
                        controller.logout()
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.top: rect.bottom
        anchors.topMargin: parent.height*0.02
        width: parent.width/2
        height: parent.height*0.5
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        GridLayout {
            anchors.fill: parent
            rows: 4
            columns: 5
            anchors.margins: parent.height*0.02

            Label {
                text: qsTr("Active")
            }
            Switcher {
                id: activeSwitcher
                checked: active
                Layout.columnSpan: 3
                onCheckedChanged: {
                    if (active != checked)
                    {
                        controller.updateValue(id, textField.text, activeSwitcher.checked, wacherSwitcher.checked)
                        active = checked
                    }
                }
            }

            RoundImage {
                id: img
                Layout.rowSpan: 2
                width: rect.width/10
                height: rect.width/10
                source: logoUrl
                textImage: logoUrl < 1 ? (projectName.length > 0 ? projectName[0] : "1") : ""
            }

            Label {
                text: qsTr("Name")
            }
            TextField {
                id: textField
                text: projectName
                Layout.columnSpan: 1
            }
            Button {
                id: btn
                font.bold: true
                background: Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    height: textField.height
                    width: textField.height
                    radius: 5
                    color: "#395277"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Ok")
                        color: "white"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            controller.updateValue(id, textField.text, activeSwitcher.checked, wacherSwitcher.checked)
                        }
                    }
                }
            }
            Label {
                text: qsTr("Users")
                Layout.columnSpan: 5
            }
            Switcher {
                id: wacherSwitcher
                text: qsTr("Add me as watcher to tickets created by others")
                Layout.columnSpan: 5
                checked: isWatcher

                onCheckedChanged: {
                    if (isWatcher != checked)
                    {
                        controller.updateValue(id, textField.text, activeSwitcher.checked, wacherSwitcher.checked)
                        isWatcher = checked
                    }
                }
            }
        }
    }
}
