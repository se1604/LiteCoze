import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt3D.Render 2.9
import QtQuick.Layouts 1.1

Page {
    width: 600
    height: 400
    id: page1

    ColumnLayout {
        id: columnLayout
        anchors.centerIn: parent
        spacing: 3

            RowLayout {
                id: rowLayout
                spacing: 2
                Label {
                    text: "帐 号"
                }
                TextField {
                }
            }


        RowLayout {
            id: rowLayout1
            spacing: 2
            Label {
                text: "密 码"
            }
            TextField {
            }
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 1
            Button {
                text: "登  录"
            }
        }
    }
}
