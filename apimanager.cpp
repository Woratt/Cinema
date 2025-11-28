#include "apimanager.h"

ApiManager::ApiManager(QWidget* parent): QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &ApiManager::onReplyFinished);
}
void ApiManager::registerAdmin(const QString& login, const QString& password){
    QJsonObject json;
    json["login"] = login;
    json["password"] = password;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/registerAdmin"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::loginAdmin(const QString& login, const QString& password){
    QJsonObject json;
    json["login"] = login;
    json["password"] = password;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/loginAdmin"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
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

void ApiManager::addMovie(const QString& title, int duration, const QString& genre, const QString& puthFile){
    uploadPoster(puthFile);
    connect(this, &ApiManager::uploadFinished, this, [=](const QString& posterUrl) {
        qDebug() << "posterUrl: " << posterUrl;
        addMovieWithPoster(title, duration, genre, posterUrl);
    });
}
void ApiManager::addMovieWithPoster(const QString& title, int duration, const QString& genre, const QString& posterUrl) {
    QJsonObject json;
    json["title"] = title;
    json["duration"] = duration;
    json["genre"] = genre;
    json["linkPoster"] = posterUrl;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/addMovie"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    QNetworkReply* reply = manager->post(request, data);
}

QJsonArray ApiManager::getAllMovies(){
    QUrl url(baseURL + "/getMovies");
    QNetworkRequest request(url);
    request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

    m_data.clear();

    m_reply = manager->get(request);

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray moviesArray = doc.array();

    m_data.clear();

    return moviesArray;
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

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray seatsArray = doc.array();
    for (int i = 0; i < seatsArray.size(); ++i) {
        m_reservedPlaces.push_back(seatsArray[i].toInt());
    }

    m_data.clear();

    return m_reservedPlaces;
}

QVector<QByteArray> ApiManager::getInfoForAllMovie(){
    QVector<QByteArray> movies;
    int movie_id = 0;
    while(true){
        QUrl url(baseURL + "/getMovie");
        QUrlQuery query;
        query.addQueryItem("movie_id", QString::number(movie_id));
        url.setQuery(query);

        QNetworkRequest request(url);
        request.setRawHeader("X-API-Key", publicApiKey.toUtf8());

        m_reply = manager->get(request);

        QEventLoop loop;
        connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
        connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        if(m_data.isEmpty()){
            break;
        }else{
            movies.append(m_data);
            m_data.clear();
            m_reply->deleteLater();
            ++movie_id;
        }
    }
    return movies;
}

void ApiManager::uploadPoster(const QString& filePath){
    QFile *file = new QFile(filePath);
    if (!file->exists()) {
        delete file;
        emit uploadFailed("File does not exist: " + filePath);
        return;
    }

    if (!file->open(QIODevice::ReadOnly)) {
        delete file;
        emit uploadFailed("Cannot open file: " + filePath);
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    QString disposition = QString("form-data; name=\"poster_file\"; filename=\"%1\"")
                              .arg(QFileInfo(filePath).fileName());
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(disposition));
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    QNetworkRequest request(QUrl(baseURL + "/upload_poster"));
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    m_reply = manager->post(request, multiPart);

    connect(m_reply, &QNetworkReply::uploadProgress, this, &ApiManager::onUploadProgress);
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, this, &ApiManager::onUploadFinished);
    connect(m_reply, &QNetworkReply::errorOccurred, this, &ApiManager::onNetworkError);
}

void ApiManager::onUploadProgress(qint64 bytesSent, qint64 bytesTotal) {
    qDebug() << "Upload progress:" << bytesSent << "/" << bytesTotal;
}

void ApiManager::onUploadFinished() {
    if (m_reply->error() == QNetworkReply::NoError) {
        QByteArray response = m_reply->readAll();
        qDebug() << "Upload success:" << response;

        QJsonDocument doc = QJsonDocument::fromJson(m_data);
        QJsonObject obj = doc.object();

        if (obj["success"].toBool()) {
            QString fileUrl = obj["full_url"].toString();
            emit uploadFinished(fileUrl);
        } else {
            emit uploadFailed(obj["error"].toString());
        }
    } else {
        emit uploadFailed(m_reply->errorString());
    }

    m_reply->deleteLater();
    m_reply = nullptr;
}

QString ApiManager::takeLink(){
    m_data = m_reply->readAll();
    qDebug() << "Server response:" << m_data;

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonObject obj = doc.object();

    return obj["full_url"].toString();
}

void ApiManager::onNetworkError(QNetworkReply::NetworkError error) {
    Q_UNUSED(error)
    emit uploadFailed(m_reply->errorString());
}

void ApiManager::onReadyRead(){
    m_data = m_reply->readAll();
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
