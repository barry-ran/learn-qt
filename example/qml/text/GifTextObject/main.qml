import QtQuick 2.12
import QtQuick.Window 2.12

import com.qm.sdk 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    TextEdit {
        id: edit
        anchors.fill: parent

        Component.onCompleted: {
            GifTextObject.registerHandler(edit.textDocument);
            GifTextObject.insertGif(edit.textDocument, "C:/Users/Admin/Desktop/gif.gif");
        }
    }
}
