#include "apimanager.h"

ApiManager::ApiManager(QWidget* parent): QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &ApiManager::onReplyFinished);
}
void ApiManager::registerAdmin(const QString& login, const QString& password, const QString& admin_ip){
    qDebug() << "registerAdmin";
    QJsonObject json;
    json["login"] = login;
    json["password"] = password;
    json["admin_ip"] = admin_ip;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/registerAdmin"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::loginAdmin(const QString& login, const QString& password){
    QJsonObject json;
    json["username"] = login;
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

QVector<Movie> ApiManager::getAllMovies(){
    QVector<Movie> movies;
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
    for (int i = 0; i < moviesArray.size(); ++i) {
        QJsonObject movieObj = moviesArray[i].toObject();

        Movie movie;
        movie.id = movieObj["id"].toInt();
        movie.title = movieObj["title"].toString();
        movie.genre = movieObj["genre"].toString();
        movie.posterUrl = movieObj["linkPoster"].toString();

        movies.append(movie);
    }
    return movies;

    //return moviesArray;
}

void ApiManager::addSession(int movie_id, int hall_id, const QString& dateTime){
    QJsonObject json;
    json["movie_id"] = movie_id;
    json["hall_id"] = hall_id;
    json["session_datetime"] = dateTime;

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

QVector<User> ApiManager::getAllUsers(){
    QVector<User> users;
    QUrl url(baseURL + "/getAllUsers");

    QNetworkRequest request(url);
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    m_reply = manager->get(request);

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray usersArray = doc.array();
    for(int i = 0; i < usersArray.size(); ++i){
        QJsonObject userObj = usersArray[i].toObject();
        User user;
        user.id = userObj["id"].toInt();
        user.login = userObj["login"].toString();
        user.email = userObj["email"].toString();
        users.append(user);
    }
    m_data.clear();

    return users;

}

QVector<Admin> ApiManager::getAllAdmins(){
    QVector<Admin> admins;
    QUrl url(baseURL + "/getAllAdmins");

    QNetworkRequest request(url);
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    m_reply = manager->get(request);

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray adminsArray = doc.array();
    for(int i = 0; i < adminsArray.size(); ++i){
        QJsonObject adminObj = adminsArray[i].toObject();
        Admin admin;
        admin.id = adminObj["id"].toInt();
        admin.login = adminObj["login"].toString();
        admin.ip = adminObj["ip"].toString();
        admins.append(admin);
    }
    m_data.clear();

    return admins;
}

QVector<Session> ApiManager::getSessionsForMovie(int movie_id){
    QVector<Session> sessions;
    QUrl url(baseURL + "/getSessionsForMovies");
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

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray sessionsArray = doc.array();
    for (int i = 0; i < sessionsArray.size(); ++i) {
        QJsonObject sessionObj = sessionsArray[i].toObject();
        Session session;
        session.id = sessionObj["id"].toInt();
        session.hallName = sessionObj["hall_name"].toString();
        QString dateTime = sessionObj["session_datetime"].toString();

        QStringList parts = dateTime.split(" ");
        if (parts.size() >= 4) {
            QString dayStr = parts[1];
            QString monthStr = parts[2];
            QString yearStr = parts[3];
            QString time = parts[4].mid(0, 5);
            qDebug() << parts.size();

            QMap<QString, QString> months;
            months["Jan"] = "01"; months["Feb"] = "02"; months["Mar"] = "03";
            months["Apr"] = "04"; months["May"] = "05"; months["Jun"] = "06";
            months["Jul"] = "07"; months["Aug"] = "08"; months["Sep"] = "09";
            months["Oct"] = "10"; months["Nov"] = "11"; months["Dec"] = "12";

            QString month = months[monthStr];

            session.date = dayStr + "-" + month + "-" + yearStr;
            session.time = time;

        }
        sessions.append(session);
    }

    m_data.clear();

    return sessions;
}

QVector<Session> ApiManager::getAllSessions(){
    QVector<Session> sessions;
    QUrl url(baseURL + "/getAllSessions");

    QNetworkRequest request(url);
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    m_reply = manager->get(request);

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray sessionsArray = doc.array();
    for (int i = 0; i < sessionsArray.size(); ++i) {
        QJsonObject sessionObj = sessionsArray[i].toObject();
        Session session;
        session.id = sessionObj["id"].toInt();
        session.movie_title = sessionObj["movie_title"].toString();
        session.hallName = sessionObj["hall_name"].toString();
        QString dateTime = sessionObj["session_datetime"].toString();

        QStringList parts = dateTime.split(" ");
        if (parts.size() >= 4) {
            QString dayStr = parts[1];
            QString monthStr = parts[2];
            QString yearStr = parts[3];
            QString time = parts[4].mid(0, 5);
            qDebug() << parts.size();

            QMap<QString, QString> months;
            months["Jan"] = "01"; months["Feb"] = "02"; months["Mar"] = "03";
            months["Apr"] = "04"; months["May"] = "05"; months["Jun"] = "06";
            months["Jul"] = "07"; months["Aug"] = "08"; months["Sep"] = "09";
            months["Oct"] = "10"; months["Nov"] = "11"; months["Dec"] = "12";

            QString month = months[monthStr];

            session.date = dayStr + "-" + month + "-" + yearStr;
            session.time = time;

        }
        sessions.append(session);
    }

    m_data.clear();

    return sessions;
}

QVector<Hall> ApiManager::getAllHalls(){
    QVector<Hall> halls;
    QUrl url(baseURL + "/getAllHalls");

    QNetworkRequest request(url);
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    m_reply = manager->get(request);

    QEventLoop loop;
    connect(m_reply, &QNetworkReply::readyRead, this, &ApiManager::onReadyRead);
    connect(m_reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(m_data);
    QJsonArray hallsArray = doc.array();
    for(int i = 0; i < halls.size(); ++i){
        QJsonObject hallObj = hallsArray[i].toObject();
        Hall hall;
        hall.id = hallObj["id"].toInt();
        hall.name = hallObj["name"].toString();
        hall.seatCount = hallObj["seat_count"].toInt();
        halls.append(hall);
    }
    return halls;
}

void ApiManager::deleteUser(int user_id){
    QJsonObject json;
    json["user_id"] = user_id;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/deleteUser"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::deleteAdmin(int admin_id){
    QJsonObject json;
    json["admin_id"] = admin_id;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/deleteAdmin"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::deleteSession(int session_id){
    QJsonObject json;
    json["session_id"] = session_id;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/deleteSession"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
}

void ApiManager::deleteMovie(int movie_id){
    QJsonObject json;
    json["movie_id"] = movie_id;

    QJsonDocument doc(json);

    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl(baseURL + "/deleteMovie"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-API-Key", adminApiKey.toUtf8());

    manager->post(request, data);
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
            }
            else if(url.contains("/registerAdmin")){
                emit adminRegistrationSuccess(message);
            }
            else if(url.contains("/deleteMovie")){
                emit movieDeleteSuccess(message);
            }
            else if(url.contains("/addSession")){
                emit sessionAddSuccess(message);
            }
            else if(url.contains("/addMovie")){
                emit movieAddSuccess(message);
            }
            else if(url.contains("/loginAdmin")){
                emit adminLoginSuccess(message);
            }
            else if(url.contains("/login")){
                emit loginSuccess(message);
            }else if(url.contains("/addHall")){
                emit hallSuccess(message);
            }
        }else{
            if(url.contains("/register")){
                emit registrationError(message);
            }else if(url.contains("/registerAdmin")){
                emit adminRegistrationError(message);
            }else if(url.contains("/deleteMovie")){
                emit movieDeleteError(message);
            }else if(url.contains("/addSession")){
                emit sessionAddError(message);
            }else if(url.contains("/addMovie")){
                emit movieAddError(message);
            }else if(url.contains("/loginAdmin")){
                emit adminLoginError(message);
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
