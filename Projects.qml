import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
    id: projectsPage

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
                    }
                }
                Button{
                    Layout.preferredWidth: parent.width/2.5
                    text: qsTr("LOGOUT")
                    onClicked: {
                        controller.logout()
                        loader.setSource("LoginPage.qml")
                    }
                }
            }
        }
    }

    ListView {
        id: view

        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height*0.9
        anchors.top: rect.bottom
        anchors.topMargin: 10
        spacing: 10
        model: controller.model()

        clip: true

        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        ScrollBar.vertical: ScrollBar {}

        delegate: Rectangle {
            id: delegateRect
            width: view.width/2
            anchors.horizontalCenter: parent.horizontalCenter
            height: 80
            Layout.alignment: Qt.AlignVCenter
            color: "white"


            RowLayout {
                spacing: 10
                anchors.fill: delegateRect

                RoundImage {
                    id: img
                    Layout.preferredHeight: 64
                    Layout.preferredWidth: 64
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.leftMargin: 10
                    source: model.logoUrl
                    textImage: model.logoUrl < 1 ? (model.name.length > 0 ? model.name[0] : "1") : ""
                }

                Text {
                    text: qsTr(model.name).substring(0, 11)

                    Layout.minimumWidth: parent.width*0.2
                }

                Item { Layout.minimumWidth: 10 }

                Text {
                    color: model.active? "green" : "red"
                    text: model.active? qsTr("Active") : qsTr("Inactive")
                }

                Item { id: spacer; Layout.minimumWidth: 10 }

                GridLayout {
                    Layout.alignment: Qt.AlignRight
                    Layout.rightMargin: parent.width*0.03
                    columns: 2
                    rows: 3
                    Label {
                        text: qsTr("time this week");
                    }
                    Label {
                        text: qsTr("00:00:00");
                    }
                    Label {
                        text: qsTr("this month");
                    }
                    Label {
                        text: qsTr("00:00:00");
                    }
                    Label {
                        text: qsTr("total");
                    }
                    Label {
                        text: model.spendTimeAll;
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    loader.setSource("EditPage.qml")
                    loader.item.id = model.id
                    loader.item.projectName = model.name
                    loader.item.logoUrl = model.logoUrl
                    loader.item.active = model.active
                    loader.item.isWatcher = model.watcher
                }
            }
        }
    }

    Connections {
        target: controller
        onModelUpdated: {
            view.model = controller.model()
        }
    }
}
