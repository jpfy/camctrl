import QtQuick 2.6
import QtQuick.Controls 2.2

Pane {
    background: Rectangle {
        color: "#444444"
        border.width: 0
    }
    x: 600
    width: 200
    height: 440
    anchors.top: mainBar.bottom
    anchors.topMargin: 0
    anchors.right: parent.right
    anchors.rightMargin: 0

    property string menuTitle: "Projects"

    Button { id: newProjButton
        enabled: true
        width: 80
        height: 48
        text: "NEW"
        font.italic: true
        topPadding: 15
        font.pointSize: 15
//        font.family: "Courier"
        display: AbstractButton.TextBesideIcon
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: -3
        visible: true

        onClicked: {
            newProjectUI.visible = true
        }
    }

    Button { id: deleteProjButton
        enabled: true
        width: 80
        height: 48
        text: qsTr("DEL")
        font.italic: true
        topPadding: 15
        font.pointSize: 15
//        font.family: "Courier"
        anchors.left: parent.left
        anchors.leftMargin: 95
        anchors.top: parent.top
        visible: true
        anchors.topMargin: -3

        onClicked: {
            delProjectUI.visible = true
        }

    }

    ToolSeparator {
        id: toolSeparator6
        anchors.top: parent.top
        anchors.topMargin: 39
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        orientation: Qt.Horizontal
    }

    Button { id: selectProjButton
        width: 176
        height: 48
        text: "SELECT"
        font.italic: true
        anchors.left: parent.left
        anchors.leftMargin: 0
        topPadding: 15
        anchors.top: parent.top
        visible: true
        anchors.topMargin: 57
        display: AbstractButton.TextBesideIcon
        font.pointSize: 15
//        font.family: "Courier"

        onClicked: {
            app.currentProject = projectUI.projectListModel.get(listView.currentIndex, "fileName")
            cam.set_project(app.currentProject)
        }

    }

    ToolSeparator {
        id: toolSeparator7
        anchors.left: parent.left
        orientation: Qt.Horizontal
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 98
        anchors.rightMargin: 0
    }

    Button { id: openProjButton
        enabled: false
        width: 176
        height: 48
        text: "OPEN"
        font.italic: true
        anchors.left: parent.left
        anchors.leftMargin: 0
        topPadding: 15
        anchors.top: parent.top
        visible: true
        anchors.topMargin: 115
        font.pointSize: 15
        display: AbstractButton.TextBesideIcon
//        font.family: "Courier"
    }

    ToolSeparator {
        anchors.topMargin: 154
        anchors.leftMargin: 0
        anchors.left: parent.left
        anchors.rightMargin: 0
        orientation: Qt.Horizontal
        anchors.top: parent.top
        anchors.right: parent.right
    }

    Button { id: syncProj_Button
        width: 176
        height: 48
        text: "SYNC"
        font.italic: true
        anchors.topMargin: 171
        visible: true
        anchors.leftMargin: 0
        anchors.left: parent.left
        font.pointSize: 15
        enabled: true
        anchors.top: parent.top
//        font.family: "Courier"
        topPadding: 15

        onClicked: {
            stack.push(syncPane)
            mainBar.currentMenuName = syncPane.menuTitle
        }
    }
}
