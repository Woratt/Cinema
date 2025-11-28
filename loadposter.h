#ifndef LOADPOSTER_H
#define LOADPOSTER_H

#include <QObject>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class LoadPoster : public QObject
{
    Q_OBJECT
public:
    LoadPoster(QObject *parent = nullptr);
    ~LoadPoster();

    void loadImage(const QUrl &imageUrl);
    void cancelLoading();
signals:
    void imageLoaded(const QPixmap &pixmap);
    //void loadingProgress(int percent);
    void loadingFailed(const QString &errorMessage);
private:
    //void onReadyRead();
    //void onFinished();
    //void onError(QNetworkReply::NetworkError);
    void onReplyFinished();
    //void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_currentReply;
};

#endif // LOADPOSTER_H
