import QtQuick 2.9
import QtQuick.Controls 2.2
import loginUI 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 384
    height: 288
    title: qsTr("Login&Register")

    MyLogin {
        id: mylogin
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
            //登录
        }

        Page2Form {
            //注册
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

    Button {
        onClicked: {
            window.close()
        }
    }
}
