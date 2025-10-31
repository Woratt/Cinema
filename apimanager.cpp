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

void ApiManager::reservePlace(int numOfSession, int numOfPlace){
    QJsonObject json;
    json["session_id"] = numOfSession;
    json["seat_number"] = numOfPlace;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/reservePlace"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::unreservePlace(int numOfSession, int numOfPlace){
    QJsonObject json;
    json["session_id"] = numOfSession;
    json["seat_number"] = numOfPlace;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/unreservePlace"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

    manager->post(request, data);
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

void ApiManager::addMovie(const QString& title, int duration, const QString& genre){
    QJsonObject json;
    json["title"] = title;
    json["duration"] = duration;
    json["genre"] = genre;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/addMovie"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::addSession(int movie_id, int hall_id, int start_time){
    QJsonObject json;
    json["movie_id"] = movie_id;
    json["hall_id"] = hall_id;
    json["start_time"] = start_time;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/addSession"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

QVector<int> ApiManager::getReservePlaces(int session_id){
    m_reservedPlaces.clear();
    QUrl url(baseURL + "/getReservePlaces");
    QUrlQuery query;
    query.addQueryItem("session_id", QString::number(session_id));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

    m_reply = manager->get(request);

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    return m_reservedPlaces;
}

void ApiManager::onReadyRead(){
    QByteArray data = m_reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray seatsArray = doc.array();
    for (int i = 0; i < seatsArray.size(); ++i) {
        m_reservedPlaces.push_back(seatsArray[i].toInt());
    }
}

void ApiManager::onReplyFinished(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
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
