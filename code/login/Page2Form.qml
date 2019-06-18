import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt3D.Render 2.9
import QtQuick.Layouts 1.1

Page {
    width: 600
    height: 400
    id: page2

    ColumnLayout {
        id: columnLayout
        anchors.centerIn: parent
        spacing: 4

            RowLayout {
                id: rowLayout
                spacing: 2
                Label {
                    text: "帐 号"
                }
                TextField {
                    id: id
                }
            }


            RowLayout {
                id: rowLayout1
                spacing: 2
                Label {
                    text: "昵 称"
                }
                TextField {
                    id: nickname
                }
            }

        RowLayout {
            id: rowLayout2
            spacing: 2
            Label {
                text: "密 码"
            }
            TextField {
                id: password
            }
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1
            Button {
                text: "注   册"
                onClicked: {
                    mylogin.myRegister(id.text, nickname.text, password.text)
                }
            }
        }
    }
}
