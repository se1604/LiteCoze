import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    //好友或群聊框
    Rectangle

    {
        id: friendOrGroup
        width: parent.width * 0.25
        height: parent.height * 0.1

        color: "#F6F6F6"

        border.width: 1
        border.color: "#E4EAEA"

        //下划线
        Rectangle {
            id: xiahuaxianRectangle1
            height: parent.height * 0.05
            width: parent.width * 0.3
            anchors.bottom: parent.bottom
            x: rectangle1.x + friendText.width/2 - width/2
            color: "blue"

            visible: false
        }

        Rectangle {
            id: xiahuaxianRectangle1_1
            height: parent.height * 0.05
            width: parent.width * 0.3
            anchors.bottom: parent.bottom
            x: rectangle1.x + friendText.width/2 - width/2
            color: "blue"

            visible: true
        }

        Rectangle {
            id: xiahuaxianRectangle2
            height: parent.height * 0.05
            width: parent.width * 0.3
            anchors.bottom: parent.bottom
            x: rectangle1.x + rectangle1.width - groupText.width/2 - width/2
            color: "blue"

            visible: false
        }

        Rectangle {
            id: xiahuaxianRectangle2_1
            height: parent.height * 0.05
            width: parent.width * 0.3
            anchors.bottom: parent.bottom
            x: rectangle1.x + rectangle1.width - groupText.width/2 - width/2
            color: "blue"

            visible: false
        }

        Rectangle {
            id: rectangle1
            anchors.centerIn: parent
            width: parent.width * 0.6
            height: friendText.height

            color: "#F6F6F6"

            //好友
            Text {
                id: friendText
                text: qsTr("好友")
                font.pointSize: 12
                color: "#D2D5D5"

                anchors.left: parent.left

                MouseArea {
                    id: mouse1
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        listRecView.model = memberListModel
                        listRecView.delegate = memberListDelegate
                        xiahuaxianRectangle1_1.visible = true
                        xiahuaxianRectangle2_1.visible = false
                        friendText1.visible = true
                        groupText1.visible = false
                    }
                    onEntered: {
                        xiahuaxianRectangle1.visible = true
                        friendText.color = "black"
                    }
                    onExited: {
                        xiahuaxianRectangle1.visible = false
                        friendText.color = "#D2D5D5"
                    }
                }
            }

            Text {
                id: friendText1
                text: qsTr("好友")
                font.pointSize: 12
                color: "black"
                visible: true

                anchors.left: parent.left
            }

            //群
            Text {
                id: groupText
                text: qsTr("群聊")
                font.pointSize: 12
                color: "#D2D5D5"

                anchors.right: parent.right

                MouseArea {
                    id: mouse2
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        listRecView.model = groupListModel
                        listRecView.delegate = groupListDelegate
                        xiahuaxianRectangle2_1.visible = true
                        xiahuaxianRectangle1_1.visible = false
                        groupText1.visible = true
                        friendText1.visible = false
                    }
                    onEntered: {
                        xiahuaxianRectangle2.visible = true
                        groupText.color = "black"
                    }
                    onExited: {
                        xiahuaxianRectangle2.visible = false
                        groupText.color = "#D2D5D5"
                    }
                }
            }

            Text {
                id: groupText1
                text: qsTr("群聊")
                font.pointSize: 12
                color: "black"
                visible: false

                anchors.right: parent.right
            }
        }
    }

    //列表框
      //好友model和delegate

    //显示好友信息在列表上
    Connections {
        target: client
        onShowAccountInfo: {
            console.log("ff")
            memberListModel.clear()
            memberListModel.append({"name":nickName, "motto":id})
        }
    }

    ListModel {
        id: memberListModel

//        ListElement {
//            name: "啊爷"
//            motto: "你好啊。。"
//        }

//        ListElement {
//            name: "小明"
//            motto: "一起跨年哦"
//        }
    }

    Component {
        id: memberListDelegate

        Rectangle {
            width: listRectangle.width
            height: listRectangle.width * 0.3

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
                    chatModle.clear()
                    chatModle.append({"name":name, "id":motto})
                    chatListView.model = chatModle
                    chatListView.delegate = chatComponentDelegate
                }
            }

            color: "#F6F6F6"

            Rectangle {
                id: touxiang
                width: parent.width * 0.2
                height: width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.05
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


            ListModel {
                id: chatModle
            }
        }
    }

      //群model和delegate
    ListModel {
        id: groupListModel

        ListElement {
            name: "世界首脑交流会议"
        }

        ListElement {
            name: "兰若若的幼儿园"
        }
    }
    Component {
        id: groupListDelegate

        Rectangle {
            width: listRectangle.width
            height: listRectangle.width * 0.3

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    parent.color = "#D2D5D5"
                }
                onExited: {
                    parent.color = "#F6F6F6"
                }
            }

            color: "#F6F6F6"

            Rectangle {
                id: touxiang
                width: parent.width * 0.2
                height: width
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.05
                radius: 180

                color: "green"
            }

            Text {
                id: nameText
                text: name

                anchors.left: touxiang.right
                anchors.leftMargin: parent.width * 0.02
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    //view
    Rectangle {
        id: listRectangle
        width: friendOrGroup.width
        height: parent.height - friendOrGroup.height
        anchors.top: friendOrGroup.bottom

        color: "#F6F6F6"

        border.width: 1
        border.color: "#E4EAEA"

        ListView {
            id: listRecView
            anchors.fill: parent

            model: memberListModel
            delegate: memberListDelegate
            clip: true
        }
    }

//    聊天框
//      delegate
    Component {
        id: chatComponentDelegate

        ChatRectangle {
            id: chatRectangleDelegate
            width: chatRectangleView.width
            height: chatRectangleView.height

            topChatText.text: name
            topChatId.text: id
        }
    }

      //view
    Rectangle {
        id: chatRectangleView
        width: parent.width - friendOrGroup.width
        height: parent.height
        anchors.left: friendOrGroup.right

        ListView {
            id: chatListView
            anchors.fill: parent
        }
    }
}
