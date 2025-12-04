#include "loadposter.h"

LoadPoster::LoadPoster(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_currentReply(nullptr)
{
}

LoadPoster::~LoadPoster()
{
    cancelLoading();
}

void LoadPoster::loadImage(const QUrl &imageUrl)
{
    cancelLoading();

    if (!imageUrl.isValid()) {
        emit loadingFailed("Неправильний URL");
        return;
    }

    QNetworkRequest request(imageUrl);

    m_currentReply = m_networkManager->get(request);

    connect(m_currentReply, &QNetworkReply::finished,
            this, &LoadPoster::onReplyFinished);
}

void LoadPoster::cancelLoading()
{
    if (m_currentReply) {
        m_currentReply->disconnect();
        m_currentReply->abort();
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }
}

void LoadPoster::onReplyFinished()
{
    if (!m_currentReply)
        return;

    if (m_currentReply->error() == QNetworkReply::NoError) {
        QByteArray imageData = m_currentReply->readAll();
        QPixmap pixmap;

        if (pixmap.loadFromData(imageData)) {
            emit imageLoaded(pixmap);
        } else {
            emit loadingFailed("Не вдалося завантажити зображення");
        }
    } else {
        emit loadingFailed(m_currentReply->errorString());
    }

    m_currentReply->deleteLater();
    m_currentReply = nullptr;
}
