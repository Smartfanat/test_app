import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import APIController 1.0

ApplicationWindow {
    id: root

    visible: true

    width: windowWidth/3.5
    height: windowHeight/2

    title: qsTr("Quwi")

    color: "#F4F4F4"

    Loader {
        id: loader

        anchors.fill: parent

        Component.onCompleted:  {
            root.minimumWidth = windowWidth/3.5
            root.minimumHeight = windowHeight/2
            setSource("LoginPage.qml")
        }
    }

    Controller {
        id: controller
    }

    Connections {
        target: controller
        onLoggedChanged: {
            if (controller.logged)
            {
                loader.setSource("Projects.qml")
                root.width = root.minimumWidth = windowWidth/2
                root.height = root.minimumHeight= windowHeight/1.5
                controller.getProjects()
            }
            else
            {
                loader.setSource("LoginPage.qml")
                root.width = root.minimumWidth = windowWidth/3.5
                root.height= root.minimumHeight = windowHeight/2
            }
        }
    }
}
