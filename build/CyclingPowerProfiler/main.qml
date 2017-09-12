import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 480
    height: 620
    title: qsTr("Cycling Power Profiler")
    background: Rectangle {
        color: "#CCCCCC"
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Label {
                text: qsTr("Profile View")
                anchors.centerIn: parent
            }
        }
    }

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Rider Properties")
        }
        TabButton {
            text: qsTr("Power Profile")
        }
    }
}
