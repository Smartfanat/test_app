import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
    id: root

    anchors.centerIn: parent

    color: "#F4F4F4"

    Rectangle {
        anchors.centerIn: parent
        width: parent.width/3
        height: parent.height/2
        color: parent.color

        ColumnLayout
        {
            anchors.fill: parent


            spacing: 2

            Label {
                text: qsTr("LOGIN")
                font.bold: true
            }

            TextField {
                id: emailField
                placeholderText: qsTr("Email")
            }

            TextField {
                id: passwordField
                echoMode: TextInput.Password
                placeholderText: qsTr("Password")
            }

            Button {
                Layout.minimumWidth: passwordField.width*0.5
                Layout.minimumHeight: passwordField.height
                Text {
                    anchors.centerIn: parent
                    text: qsTr("LOGIN")
                    color: "white"
                }

                background: Rectangle {
                    radius: 5
                    color: "#0f488c"
                }

                onClicked: {
                    controller.login(emailField.text, passwordField.text)
                }
            }
        }
    }
}
