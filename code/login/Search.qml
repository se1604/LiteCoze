import QtQuick 2.9
import QtQuick.Controls 2.2
import searchUI 1.0

ApplicationWindow {
    id: window
    visible: false
    width: 384
    height: 288
    title: qsTr("search")

    MySearch {
        id: mysearch
    }

    Connections {
        target: mysearch
        onShowSearchUI: {
            console.log("ff")
            window.visible = true
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        SearchForFriend {
            //好友
        }

        SearchForGroup {
            //群
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }
}
