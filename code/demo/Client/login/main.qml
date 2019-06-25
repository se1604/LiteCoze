//auther: duHongpeng(duA)
//time: 2019.3.28
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import clientUI 1.0

Window {
    visible: false
    width: 640
    height: 480
    id: clientWindow


    MyClient {
        id: client
    }

    Connections {
        target: client
        onShowClientUI: {
            console.log("ff")
            clientWindow.visible = true
        }
    }

    //顶层视图
    Rectangle {
        id: topRectangle
        width: parent.width
        height: parent.height * 0.15

        color: "blue"

        RowLayout {
            anchors.centerIn: parent
            spacing: 20


            Text {
                id: liaotianT
                text: qsTr("聊天")
                font.pointSize: 15
                font.bold: true
                color: "white"
                MouseArea {
                    anchors.fill: parent
                    onClicked: viewB.delegate = chatCo
                }
            }
            Text {
                id: pengyouquanT
                text: qsTr("朋友圈")
                font.pointSize: 12
                font.bold: false
                color: "white"
                MouseArea {
                    anchors.fill: parent
                    onClicked: viewB.delegate = circleCo
                }
            }
        }
    }

    //底层视图
    ListModel {
        id: listMo
        ListElement {}
    }

    Component {
        id: chatCo
        BottomRectanglePage {
            width: bottomRectangle.width
            height: bottomRectangle.height
        }
    }
    Component {
        id: circleCo
        FriendCirclePage {
            width: bottomRectangle.width
            height: bottomRectangle.height
        }
    }

    Rectangle {
        id: bottomRectangle
        width: parent.width
        height: parent.height - topRectangle.height
        anchors.top: topRectangle.bottom

        ListView {
            id: viewB
            model: listMo
            delegate: chatCo
        }
    }
}
