import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt3D.Render 2.9
import QtQuick.Layouts 1.1

Page {
    width: 600
    height: 400
    id: page1

    Connections {
        target: mysearch
        onShowFindInfo: {
            console.log("ff")
            memberListModel.append({"name":nickName, "motto":id})
        }
    }

    Rectangle {
        id: search
        width: parent.width
        height: 30

        TextEdit {
            id: textEdit
            height: parent.height
            width: parent.width * 0.8
            text: "search"
            font.pointSize: 14

        }

        Button {
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0

            text: "搜索"
            onClicked: {
                mysearch.findNetizen(textEdit.text)
            }
        }
    }

    //view
    Rectangle {
        id: list
        anchors.top: search.bottom
        width: parent.width
        height: parent.height - search.height

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
            width: list.width
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
                width: 50
                height: 30
                text: "添加"
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                onClicked: {
                    mysearch.addFriend(mottoText.text)
                }
            }
        }
        }

    ListModel {
        id: memberListModel

        ListElement {
            name: "啊爷"
            motto: "你好啊。。"
        }

        ListElement {
            name: "小明"
            motto: "一起跨年哦"
        }
    }
}
