import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

import APIController 1.0

Window {
    id: root

    visible: true

    width: windowWidth/3
    height: windowHeight/2

    title: qsTr("Quwi")

    color: "#F4F4F4"

    Loader {
        id: loader

        anchors.fill: parent

        Component.onCompleted:  {
            console.log("Completed")
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
                root.width = windowWidth/2
                root.height= windowHeight/1.5
                controller.getProjects()
            }
            else
            {
                loader.setSource("LoginPage.qml")
                root.width = windowWidth/3
                root.height= windowHeight/2
            }
        }
    }
}
