#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class ApiManager : public QWidget
{
    Q_OBJECT
public:
    explicit ApiManager(QWidget* parent = nullptr);
    void registerUser(const QString&, const QString&, const QString&);
    void loginUser(const QString&, const QString&);
    void addHall(const QString&, int);
    void reservePlace(int);

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

private:
    QNetworkAccessManager* manager;
    QString baseURL = "https://andriipanchuk.pythonanywhere.com";
    QString publicApiKey = "cinema_public_key_2024";
    QString adminApiKey = "key_my_pc";

};

#endif // APIMANAGER_H
