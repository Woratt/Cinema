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

class ApiManager : public QWidget
{
    Q_OBJECT
public:
    explicit ApiManager(QWidget* parent = nullptr);
    void registerUser(const QString&, const QString&, const QString&);
    void loginUser(const QString&, const QString&);
    void addHall(const QString&, int);
    void reservePlace(int, int);
    void addMovie(const QString&, int, const QString&);
    void addSession(int, int, int);
    QVector<int> getReservePlaces(int);

signals:
    void registrationSuccess(const QString&);
    void registrationError(const QString&);
    void loginSuccess(const QString&);
    void loginError(const QString&);
    void hallSuccess(const QString&);
    void hallError(const QString&);
    void reservePlaceSucces(const QString&);
    void reservePlaceError(const QString&);

private slots:
    void onReplyFinished(QNetworkReply*);
    void onReadyRead();

private:
    //QVector<int> getArrfromJson();
    QVector<int> m_reservedPlaces;

    QNetworkAccessManager* manager;
    QString baseURL = "https://andriipanchuk.pythonanywhere.com";
    QString publicApiKey = "cinema_public_key_2024";
    QString adminApiKey = "key_my_pc";

    QNetworkReply *m_reply;

};

#endif // APIMANAGER_H
