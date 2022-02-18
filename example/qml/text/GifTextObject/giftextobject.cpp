#include <QMovie>
#include <QPainter>
#include <QQuickTextDocument>

#include "giftextobject.h"

GifTextObject::GifTextObject(QObject *parent)
    : QObject{parent}
{

}

GifTextObject* GifTextObject::instance() {
    static auto gif_text_object = new GifTextObject();
    return gif_text_object;
}

void GifTextObject::registerMyselfType()
{
    qmlRegisterSingletonType<GifTextObject>("com.qm.sdk", 1, 0, "GifTextObject", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return GifTextObject::instance();
    });
}

void GifTextObject::registerHandler(QQuickTextDocument* doc) {
    doc->textDocument()->documentLayout()->registerHandler(GifTextFormat, instance());
}

void GifTextObject::insertGif(QQuickTextDocument* doc, const QUrl& url) {
    QMovie* movie = new QMovie(url.toString());
    bool b = movie->isValid();
    movie->setCacheMode(QMovie::CacheNone);
    connect(movie, &QMovie::finished, movie, &QMovie::start);
    connect(movie, &QMovie::frameChanged, this, [url, this](int) {
        //QMovie *movie = qobject_cast<QMovie *>(sender());
        //textDocument()->addResource(QTextDocument::ImageResource, url, movie->currentPixmap());
        //emit needUpdate();
    });
    connect(movie, &QMovie::started, this, [url, doc, this](){
        QMovie *movie = qobject_cast<QMovie *>(sender());

        QTextCharFormat gifCharFormat;
        gifCharFormat.setObjectType(GifTextFormat);

        QImage image = movie->currentImage();
        gifCharFormat.setProperty(GifData, image);

        QTextCursor cursor(doc->textDocument());
        cursor.setPosition(0);
        // 可以插进去，但是是一个空白（drawObject没有被调用），和这个一样 https://stackoverflow.com/questions/26867612/qtextobjectinterface-with-qml-textedit-qquicktextedit
        cursor.insertText(QString(QChar::ObjectReplacementCharacter), gifCharFormat);
        // insertHtml是正常的
        //cursor.insertHtml("<a href=\"zly.jpg\"><img src=\"file:C:/Users/Admin/Desktop/gif.gif\" height=\"100\" width=\"100\"></a>");
    });
    movie->start();
}

QSizeF GifTextObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format) {
    //QMovie* gif = qvariant_cast<QMovie*>(format.property(GifData));
    //QSize size = gif->currentImage().size();
    QImage bufferedImage = qvariant_cast<QImage>(format.property(GifData));
    QSize size = bufferedImage.size();

    return QSizeF(size);
}

void GifTextObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format) {
    //QMovie* gif = qvariant_cast<QMovie*>(format.property(GifData));
    //painter->drawImage(rect, gif->currentImage());
    QImage bufferedImage = qvariant_cast<QImage>(format.property(GifData));
    painter->drawImage(rect, bufferedImage);
}
