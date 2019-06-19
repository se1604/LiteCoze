//auther: duHongpeng(duA)
//time: 2019.3.28
//5.26
//6.17
//6.18
import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.1
import clientUI 1.0

Window {
    visible: true
    width: 640
    height: 480
    id: clientWindow

    Connections {
        target: client
        onShowNewFriendInfo: {
            console.log("ff")
            memberListModel.append({"name":nickName, "motto":id})
            newFriendText.text = "+1"
        }
    }

    property  bool ifClicked: false

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
                    onClicked: {
                        search.visible = true
                        newFriend.visible = true
                        viewB.delegate = chatCo
                        client.flushAccountInfo()
                    }
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
                    onClicked: {
                        search.visible = false
                        newFriend.visible = false
                        viewB.delegate = circleCo
                    }
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

        //搜索
        Rectangle {
            id: search
            width: 30
            height: 30
            anchors.left: parent.left
            anchors.leftMargin: 90
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            color: "red"
            radius: 180
            visible: true

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    client.startSearchUI()
                }
            }
        }

        //新朋友按钮
        Rectangle {
            id: newFriend
            width: 30
            height: 30
            anchors.left: search.right
            anchors.leftMargin: 4
            anchors.bottom: search.bottom
            color: "blue"
            radius: 180
            visible: true
            Text {
                id: newFriendText
                anchors.centerIn: parent
                color: "white"
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    ifClicked = !ifClicked
                }
            }
        }

        //新朋友界面
        Rectangle {
            id: newFriendJ
            width: 250
            height: 300
            anchors.left: newFriend.right
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            color: "blue"
            visible: ifClicked

            ListView {
                id: listRecView
                anchors.fill: parent

                model: memberListModel
                delegate: component
                clip: true
            }
        }

        Component {
            id: component
            Rectangle {
                width: newFriendJ.width
                height: 40

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.color = "#D2D5D5"
                    }
                    onExited: {
                        parent.color = "#F6F6F6"
                    }
                    onClicked: {

                    }
                }

                color: "#F6F6F6"

                Rectangle {
                    id: touxiang
                    width: height
                    height: parent.height - 3
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 3
                    radius: 180

                    color: "yellow"
                }

                Text {
                    id: nameText
                    text: name

                    anchors.left: touxiang.right
                    anchors.leftMargin: parent.width * 0.02
                    anchors.top: touxiang.top
                }

                Text {
                    id: mottoText
                    text: motto

                    anchors.left: nameText.left
                    anchors.bottom: touxiang.bottom
                    anchors.bottomMargin: parent.width * 0.02
                }

                Button {
                    id: button1
                    width: 50
                    height: 30
                    text: "忽略"
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    onClicked: {
                        memberListModel.remove(listRecView.currentIndex)
                    }
                }
                Button {
                    width: 50
                    height: 30
                    text: "接受"
                    anchors.right: button1.left
                    anchors.rightMargin: 5
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    onClicked: {
                        client.acceptAddFriendRequest(mottoText.text, nameText.text)
                        memberListModel.remove(listRecView.currentIndex)
                    }
                }
            }
            }

        ListModel {
            id: memberListModel
        }
    }
}
