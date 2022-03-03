import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick .Controls 2.12

QtObject {
    property var loginWindow: Window {
        id: login
        width: 320
        height: 240
        visible: true
        title: qsTr("Login")

        Button {
            id: loginBtn
            text: "登陆"
            onClicked: {
                login.visible = false;
                main.visible = true;
            }
        }
    }
    property var mainWindow: Window {
        id: main
        width: 640
        height: 480
        visible: false
        title: qsTr("Main")

        Button {
            id: backLoginBtn
            text: "返回登陆"
            onClicked: {
                login.visible = true;
                main.visible = false;
            }
        }
    }
}


