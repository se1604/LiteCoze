import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.LocalStorage 2.0

Item {
    //好友或群聊框

    property  bool ifmee: false

    Rectangle
    {
        id: friendOrGroup
        width: parent.width * 0.25
        height: parent.height * 0.1

        color: "#F6F6F6"

        border.width: 1
        border.color: "#E4EAEA"

        //离线消息加载到本地数据库
        Connections {
            target: client
            onShowFriendMsg: {
                //            console.log("ff")
//                saveData()

                function saveData(){
                    console.log("a")
                    console.log(id)
                    var db = LocalStorage.openDatabaseSync("MyDB", "1.0", "My model SQL", 50000);
                    db.transaction(
                                function(tx) {
//                                    tx.executeSql('DROP TABLE ' + 'ab'+roomid+id);
                                    tx.executeSql('CREATE TABLE IF NOT EXISTS ' + 'ab'+roomid+id +'(message TEXT, me BOOL)');
                                    tx.executeSql('INSERT INTO ' + 'ab'+roomid+id + ' VALUES(?,?)', [msg, ifmee]);
//                                    tx.executeSql('INSERT INTO ' + 'ab'+topChatRoomid.text + ' VALUES(?,?)', [myItem.message, myItem.me]);
                                }
                                )
                }
            }
        }

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
                        newRecView.model = newmemberListModel
                        newRecView.delegate = newcomponent
                        creatGroupRec.visible = false
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
                        newRecView.model = newGroupListModel
                        newRecView.delegate = newgroupcomponent
                        creatGroupRec.visible = true
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
//            memberListModel.clear()
            memberListModel.append({"name":nickName, "motto":id, "roomid":roomid, "myid":myid})
        }
    }

    Connections {
        target: client
        onClearAccountInfo: {
//            console.log("ff")
            memberListModel.clear()
        }
    }

    ListModel {
        id: memberListModel

//                ListElement {
//                    name: "啊爷"
//                    motto: "你好啊。。"
//                }

//                ListElement {
//                    name: "小明"
//                    motto: "一起跨年哦"
//                }

//        Component.onCompleted: loadData()
//        Component.onDestruction: saveData()

//        function saveData(){
//            var db = LocalStorage.openDatabaseSync("MyDB", "1.0", "My model SQL", 50000);
//            db.transaction(
//                        function(tx) {
//                            tx.executeSql('DROP TABLE FriendList');
//                            tx.executeSql('CREATE TABLE IF NOT EXISTS FriendList(motto TEXT primary key, name TEXT)');
//                            var index = 0;
//                            while (index < memberListModel.count) {
//                                var myItem = memberListModel.get(index);
//                                tx.executeSql('INSERT INTO FriendList VALUES(?,?)', [myItem.motto, myItem.name]);
//                                index++;
//                            }
//                        }
//                        )
//        }

//        function loadData(){
//            var db = LocalStorage.openDatabaseSync("MyDB", "1.0", "My model SQL", 50000);
//            db.transaction(
//                        function(tx) {
//                            // Create the database if it doesn't already exist
////                            tx.executeSql('DROP TABLE FriendList');
//                            tx.executeSql('CREATE TABLE IF NOT EXISTS FriendList(motto TEXT primary key, name TEXT)');

//                            var rs = tx.executeSql('SELECT * FROM FriendList');
//                            var index = 0;
//                            if (rs.rows.length > 0) {
//                                var index = 0;
//                                while (index < rs.rows.length) {
//                                    var myItem = rs.rows.item(index);
//                                    memberListModel.append( {
//                                                       "motto": myItem.motto,
//                                                       "name": myItem.name });
//                                    index++;
//                                }
//                            } else {

//                            }
//                        }
//                        )
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
                    chatModle.append({"name":name, "id":motto, "roomid":roomid, "myid":myid})
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
    Connections {
        target: client
        onShowGrouplistInfo: {
            console.log("dd")
//            memberListModel.clear()
            groupListModel.append({"name":name, "roomid":roomid, "myid":myid})
        }
    }
    ListModel {
        id: groupListModel

//        ListElement {
//            name: "世界首脑交流会议"
//            roomid: "000123545"
//        }

//        ListElement {
//            name: "兰若若的幼儿园"
//            roomid: "00054328"
//        }
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
                onClicked: {
                    chatGroupModle.clear()
                    chatGroupModle.append({"name":name, "roomid":roomid, "myid":myid})
                    chatListView.model = chatGroupModle
                    chatListView.delegate = chatGroupComponentDelegate
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
            ListModel {
                id: chatGroupModle
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
            topChatmyId.text: myid
            topChatRoomid.text: roomid

        }
    }

    Component {
        id: chatGroupComponentDelegate

        ChatGroupRectangle {
            id: chatGroupRectangleDelegate
            width: chatRectangleView.width
            height: chatRectangleView.height

            topChatText.text: name
            topChatId.text: myid
            topChatRoomid.text: roomid
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
