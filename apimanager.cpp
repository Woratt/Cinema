#include "apimanager.h"

ApiManager::ApiManager(QWidget* parent): QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &ApiManager::onReplyFinished);
}

void ApiManager::registerUser(const QString& login, const QString& password, const QString& email)
{
    QJsonObject json;
    json["login"] = login;
    json["password"] = password;
    json["email"] = email;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::loginUser(const QString& login, const QString& password)
{
    QJsonObject json;
    json["login"] = login;
    json["password"] = password;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::reservePlace(int numOfPlace){

}

void ApiManager::addHall(const QString& name, int seat_count)
{
    QJsonObject json;
    json["name"] = name;
    json["seat_count"] = seat_count;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/addHall"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::onReplyFinished(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray response = reply->readAll();
        QJsonDocument doc =QJsonDocument::fromJson(response);
        QJsonObject json = doc.object();

        QString url = reply->url().toString();
        QString message = json["message"].toString();
        if(json["success"].isBool()){
            if(url.contains("/register")){
                emit registrationSuccess(message);
            }else if(url.contains("/login")){
                emit loginSuccess(message);
            }else if(url.contains("/addHall")){
                emit hallSuccess(message);
            }
        }else{
            if(url.contains("/register")){
                emit registrationError(message);
            }else if(url.contains("/login")){
                emit loginError(message);
            }else if(url.contains("/addHall")){
                emit hallError(message);
            }
        }
    }else{
        emit registrationError("Network error: " + reply->errorString());
    }

    reply->deleteLater();
}
