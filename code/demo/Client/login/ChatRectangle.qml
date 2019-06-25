import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: chatItem
    property alias topChatText: topChatText
    property alias topChatId: topChatId
    property  bool ifme


    //聊天框顶层显示基本信息
    Rectangle {
        id: topChatRe
        width: parent.width
        height: parent.height * 0.1
        anchors.top: parent.top
        anchors.left: parent.left

        border.width: 1
        border.color: "#E4EAEA"

        Text {
            id: topChatText
            font.pointSize: 16

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: topChatId
            font.pointSize: 16

            anchors.left: topChatText.right
            anchors.leftMargin: 10
//            x: 200
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Connections {
        target: client
        onShowFriendMsg: {
//            console.log("ff")
            if(id === topChatId.text){
                ifme = false
                midChatModel.append({"message":msg, "me": ifme})
            }
        }
    }

    //聊天框中间显示聊天内容
    ListModel {
        id: midChatModel
    }
    Component {
        id: midChatDelegate

        Rectangle {
            id: rectangleCom
            width: midChatRe.width
            height: textRec.height > touxiangRec.height ? textRec.height + 15  : touxiangRec.height + 15
//            color: "red"

            Rectangle {
                id: touxiangRec
                width: 40
                height: 40
                radius: 180

//                anchors.right: parent.right
//                anchors.rightMargin: 9
                x: me ? 430 : 10
                anchors.top: parent.top
                anchors.topMargin: 9

                color: "blue"
            }

            Rectangle {
                id: textRec
                width: midChatText.width + 20
                height: midChatText.implicitHeight + 20
//                anchors.right: touxiangRec.left
//                anchors.rightMargin: 9
                x: me ? 430-textRec.width-9 : 10+touxiangRec.width+9
                anchors.top: touxiangRec.top
                radius: 10

                color: "pink"

                Text {
                    id: midChatText
                    x: 10
                    y: 10
                    width: Math.min(midChatText.implicitWidth,  rectangleCom.width* 0.75)
                    wrapMode: Text.WordWrap

                    text: message
                }
            }
        }
    }
    Rectangle {
        id: midChatRe
        width: parent.width
        height: parent.height * 0.6
        anchors.top: topChatRe.bottom
        anchors.left: parent.left

        border.width: 1
        border.color: "#E4EAEA"



        ScrollView {
            id: midScrollView
            anchors.fill: parent

            ListView {
                model: midChatModel
                delegate: midChatDelegate
            }
        }
    }

    //聊天框底部输入聊天信息
    Rectangle {
        id: bottChatRe
        width: parent.width
        height: parent.height - topChatRe.height - midChatRe.height
        anchors.top: midChatRe.bottom
        anchors.left: parent.left
        
        border.width: 1
        border.color: "#E4EAEA"

        Rectangle {
            id: bottTopChatRe
            width: parent.width
            height: parent.height * 0.2
            anchors.top: parent.top
        }
        
        TextArea {
            id: bottTextArea
            text: qsTr("Text Area")
            wrapMode: Text.Wrap
            
            width: parent.width
            height: parent.height * 0.5
            anchors.top: bottTopChatRe.bottom
        }
        
        Item {
            id: bottBottomItem
            width: parent.width
            height: parent.height * 0.3
            anchors.bottom: parent.bottom

            Button {
                id: senderButton
                text: "发送"

                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5

                onClicked: {
                    ifme = true
                    midChatModel.append({"message":bottTextArea.text, "me": ifme})

                    client.selectFriend(topChatId.text)
                    client.sendNewMessage(bottTextArea.text)
                }
            }
        }
    }
}
