#ifndef GIFTEXTOBJECT_H
#define GIFTEXTOBJECT_H

#include <QTextObjectInterface>

class QQuickTextDocument;
class GifTextObject : public QObject, public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)

public:
    enum {
        GifTextFormat = QTextFormat::UserObject + 1
    };
    enum GifProperties {
        GifData = 1
    };

    explicit GifTextObject(QObject *parent = nullptr);

    static GifTextObject* instance();
    static void registerMyselfType();
    Q_INVOKABLE void registerHandler(QQuickTextDocument* doc);
    Q_INVOKABLE void insertGif(QQuickTextDocument* doc, const QUrl& url);


    QSizeF intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format) override;
    void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format) override;

signals:

};

#endif // GIFTEXTOBJECT_H
