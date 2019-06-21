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
            newmemberListModel.append({"name":nickName, "motto":id})
            newFriendText.text = "+1"
        }
    }

    Connections {
        target: client
        onShowNewGroupInfo: {
            console.log("ff")
            newGroupListModel.append({"name":name, "motto":id, "groupname":groupgame, "roomid":roomid})
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
            //            color: "red"
            border.width: 1
            border.color: "red"

            radius: 180
            visible: true

            Text {
                id: searchText
                color: "red"
                text: qsTr("+")
                font.pointSize: 18

                anchors.centerIn: parent
            }

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
            //            color: "blue"
            border.width: 1
            border.color: "blue"
            radius: 180
            visible: true
            Text {
                id: newFriendText
                anchors.centerIn: parent
                font.pointSize: 15
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
            width: 350
            height: 250
            anchors.left: newFriend.right
            anchors.leftMargin: 6
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 4
            color: "white"
            border.color: "#dbc3c3"
            border.width: 1
            visible: ifClicked

            ListView {
                id: newRecView
                anchors.fill: parent

                model: newmemberListModel
                delegate: newcomponent
                clip: true
            }
        }
        //xin peng you
        Component {
            id: newcomponent
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
                        parent.color = "white"
                    }
                    onClicked: {

                    }
                }

                color: "white"
                border.width: 1
                border.color: "#dbc3c3"

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
                        newmemberListModel.remove(newRecView.currentIndex)
                        newFriendText.text = ""
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
                        newmemberListModel.remove(newRecView.currentIndex)
                        newFriendText.text = ""
                    }
                }
            }
        }

        //qun
        Component {
            id: newgroupcomponent
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
                        parent.color = "white"
                    }
                    onClicked: {

                    }
                }

                color: "white"
                border.width: 1
                border.color: "#dbc3c3"

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
                    text: "请求加入群：" + groupname

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
                        newGroupListModel.remove(newRecView.currentIndex)
                        newFriendText.text = ""
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
                        client.acceptAddGroupRequest(mottoText.text, nameText.text)
                        newGroupListModel.remove(newRecView.currentIndex)
                        newFriendText.text = ""
                    }
                }
            }
        }

        ListModel {
            id: newmemberListModel
            ListElement {
                name: "啊爷"
                motto: "你好啊。。"
            }

            ListElement {
                name: "小明"
                motto: "一起跨年哦"
            }
        }
        ListModel {
            id: newGroupListModel
            ListElement {
                name: "Tom"
                gname: "世界首脑交流会议"
            }

            ListElement {
                name: "Jarry"
                gname: "兰若若的幼儿园"
            }
        }


        //创建群
        //按钮
        Rectangle {
            id: creatGroupRec
            width: 30
            height: 30
            anchors.left: newFriend.left
            anchors.bottom: newFriend.top
            anchors.bottomMargin: 4
            //            color: "blue"
            border.width: 1
            border.color: "blue"
            radius: 180
            visible: false
            Text {
                id: creatGroupT
                anchors.centerIn: parent
                font.pointSize: 15
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    createGroupJ.visible = true
                }
            }
        }
    }

    Rectangle {
        id: createGroupJ
        width: 250
        height: 100
        border.width: 1
        anchors.centerIn: parent
        visible: false

        ColumnLayout {
            id: columnLayout
            anchors.centerIn: parent
            spacing: 2

            RowLayout {
                id: rowLayout
                spacing: 2
                Label {
                    text: "群 名"
                }
                TextField {
                    id: groupName
                }
            }


            RowLayout {
                id: rowLayout1
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2
                Button {
                    text: "确定"
                    onClicked: {
                        createGroupJ.visible = false
                    }
                }
                Button {
                    text: "取消"
                    onClicked: {
                        createGroupJ.visible = false
                    }
                }
            }
        }
    }
}
