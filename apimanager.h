#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QEventLoop>
#include <QFile>
#include <QHttpMultiPart>
#include <QFileInfo>

struct Session {
    int id;
    int duration;
    int start_time;
    int hall_id;
};

class ApiManager : public QWidget
{
    Q_OBJECT
public:
    explicit ApiManager(QWidget* parent = nullptr);
    void registerUser(const QString&, const QString&, const QString&);
    void loginUser(const QString&, const QString&);
    void addHall(const QString&, int);
    void reservePlace(int, int);
    void unreservePlace(int, int);
    void addMovie(const QString&, int, const QString&, const QString&);
    void addSession(int, int, int);
    void uploadPoster(const QString&);
    void addMovieWithPoster(const QString&, int, const QString&, const QString&);
    void registerAdmin(const QString&, const QString&);
    void loginAdmin(const QString&, const QString&);
    QVector<Session> getSessionsForMovie(int);
    QJsonArray getAllMovies();
    QVector<int> getReservePlaces(int);
    QVector<QByteArray> getInfoForAllMovie();

signals:
    void registrationSuccess(const QString&);
    void registrationError(const QString&);
    void loginSuccess(const QString&);
    void loginError(const QString&);
    void hallSuccess(const QString&);
    void hallError(const QString&);
    void reservePlaceSucces(const QString&);
    void reservePlaceError(const QString&);
    void uploadFinished(const QString& fileUrl);
    void uploadFailed(const QString& error);

private slots:
    void onReplyFinished(QNetworkReply*);
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void onUploadFinished();
    void onNetworkError(QNetworkReply::NetworkError error);
    void onReadyRead();

private:
    QVector<int> m_reservedPlaces;

    QNetworkAccessManager* manager;
    QString baseURL = "https://andriipanchuk.pythonanywhere.com";
    QString publicApiKey = "cinema_public_key_2024";
    QString adminApiKey = "key_my_pc";

    QString takeLink();

    QNetworkReply *m_reply;
    QByteArray m_data;
};

#endif // APIMANAGER_H
