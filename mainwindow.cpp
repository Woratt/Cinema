#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit_8->setEchoMode(QLineEdit::Password);
    ui->logoutButton->setVisible(false);

    m_placesButtons = {ui->pushButton_9, ui->pushButton_10, ui->pushButton_11,
                        ui->pushButton_12, ui->pushButton_13, ui->pushButton_14,
                        ui->pushButton_15, ui->pushButton_16, ui->pushButton_17,
                        ui->pushButton_18, ui->pushButton_19, ui->pushButton_20,
                        ui->pushButton_21, ui->pushButton_22, ui->pushButton_23,
                        ui->pushButton_24, ui->pushButton_25, ui->pushButton_26,
                        ui->pushButton_27, ui->pushButton_28,
                        };
    m_windowSessions = new WindowSessions(this);
    m_apiManager = new ApiManager();
    m_loadPoster = new LoadPoster(this);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnCount(7);
    ui->stackedWidget->addWidget(m_windowSessions);
    setupTable();
    setUpConnections();
    setMovies();
    m_apiManager->getAllMovies();
    m_apiManager->getAllHalls();
}

void MainWindow::setupTable() {
    ui->tableWidget->setMinimumSize(1050, 250);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ui->tableWidget->setShowGrid(false);

    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    adjustTableSize();
}

void MainWindow::adjustTableSize() {
    if (!ui->tableWidget->rowCount() || !ui->tableWidget->columnCount()) return;

    int tableWidth = ui->tableWidget->width();
    int tableHeight = ui->tableWidget->height();

    int columnWidth = tableWidth / ui->tableWidget->columnCount();
    int rowHeight = tableHeight / ui->tableWidget->rowCount();

    int numColumns = ui->tableWidget->columnCount();

    for (int col = 0; col < numColumns; ++col) {
        ui->tableWidget->setColumnWidth(col, 150);
    }
    ui->tableWidget->setFixedWidth(numColumns * 150 + 2);
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        ui->tableWidget->setRowHeight(row, 250);
    }

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QWidget *widget = ui->tableWidget->cellWidget(row, col);
            if (widget) {
                widget->setFixedSize(150, 250);
            }
        }
    }
}

void MainWindow::setMovies(){
    //parseMoviesArr(m_apiManager->getAllMovies());
    QVector<Movie> movies = m_apiManager->getAllMovies();
    int totalMovies = movies.size();
    const int MAX_COLUMNS = 7;
    int requiredRows = (totalMovies + MAX_COLUMNS - 1) / MAX_COLUMNS;
    int requiredColumns;
    if (totalMovies == 0) {
        requiredColumns = 0;
    } else if (totalMovies < MAX_COLUMNS) {
        requiredColumns = totalMovies;
    } else {
        requiredColumns = MAX_COLUMNS;
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(requiredRows);
    ui->tableWidget->setColumnCount(requiredColumns);
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
    }
    ui->tableWidget->horizontalHeader()->setStretchLastSection(false);
    int row = 0;
    int col = 0;

    for(int i = 0; i < movies.size(); ++i){
        MovieWidget *movieWidget = new MovieWidget(this);
        LoadPoster *loadPoster = new LoadPoster(this);
        loadPoster->loadImage(movies[i].posterUrl);
        connect(loadPoster, &LoadPoster::imageLoaded, this, [=](const QPixmap& map){
            movieWidget->setMovieData(movies[i].id, movies[i].title, map);
            ui->tableWidget->setCellWidget(row, col, movieWidget);
        });
        connect(movieWidget, &MovieWidget::doubleClicked, this, [=](){
            m_windowSessions->setSessions(m_apiManager->getSessionsForMovie(movieWidget->movieId()), movieWidget->movieId());
            ui->stackedWidget->setCurrentWidget(m_windowSessions);
        });

        if((i + 1) % MAX_COLUMNS == 0){
            ++row;
            col = 0;
        }else{
            ++col;
        }
    }
    adjustTableSize();
}
void MainWindow::setUpConnections(){
    int numOfSession = 1;
    int numOfPlace = 1;
    for(auto placeBt : m_placesButtons){
        connect(placeBt, &QPushButton::clicked, this, [=](){
            selectPlaces(numOfPlace);
        });
        connect(placeBt, &QPushButton::clicked, this, &MainWindow::colourSeat);
        ++numOfPlace;
    }

    connect(this, &MainWindow::reservedPlaces, this, &MainWindow::onReservePlaces);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::onCalculateRemainder);


    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::backWindow);
    connect(ui->pushButton_29, &QPushButton::clicked, this, &MainWindow::logIn);
    connect(ui->pushButton_34, &QPushButton::clicked, this, &MainWindow::adminlogIn);
    connect(ui->pushButton_30, &QPushButton::clicked, this, &MainWindow::goToPageRegIn);
    connect(ui->pushButton_31, &QPushButton::clicked, this, &MainWindow::regIn);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::goToAdmin);
    connect(ui->pushButton_33, &QPushButton::clicked, this, &MainWindow::backPage);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::backPage);
    connect(ui->logoutButton, &QPushButton::clicked, this, &MainWindow::backPage);

    connect(m_apiManager, &ApiManager::loginSuccess, this, &MainWindow::regDone);
    connect(m_apiManager, &ApiManager::adminLoginSuccess, this, &MainWindow::regDone);

    connect(m_apiManager, &ApiManager::loginError, this, &MainWindow::errorLogIn);
    connect(m_apiManager, &ApiManager::registrationSuccess, this, &MainWindow::regDone);
    connect(m_apiManager, &ApiManager::registrationError, this, &MainWindow::errorRegIn);

    connect(ui->addHallButton, &QPushButton::clicked, this, &MainWindow::on_addHallButton_clicked);

    connect(m_apiManager, &ApiManager::loginError, this, &MainWindow::errorLogIn);

    connect(m_windowSessions, &WindowSessions::sessionSelected, this, [=](int sessionId){
        selectSession(sessionId);
        newWindow();
    });
    connect(m_windowSessions, &WindowSessions::backRequested, this, [=](){
         ui->stackedWidget->setCurrentWidget(ui->page);
    });
    connect(ui->addSessionButton, &QPushButton::clicked,  this, &MainWindow::on_addSessionButton_clicked);
    connect(m_apiManager, &ApiManager::sessionAddSuccess, this, &MainWindow::handleSessionAddSuccess);
    connect(m_apiManager, &ApiManager::sessionAddError, this, &MainWindow::handleSessionAddError);
    connect(ui->checkBox, &QCheckBox::toggled, this, &MainWindow::showPassword);
    connect(ui->checkBox_2, &QCheckBox::toggled, this, &MainWindow::showPasswordAdmin);

    //connect(ui->registerAdminButton, &QPushButton::clicked, this, &MainWindow::on_registerAdminButton_clicked);
    connect(m_apiManager, &ApiManager::adminRegistrationSuccess, this, &MainWindow::handleAdminRegistrationSuccess);
    connect(m_apiManager, &ApiManager::adminRegistrationError, this, &MainWindow::handleAdminRegistrationError);

    connect(m_apiManager, &ApiManager::movieDeleteSuccess, this, &MainWindow::loadAdminMovieList);
    connect(m_apiManager, &ApiManager::movieDeleteSuccess, this, &MainWindow::loadSessionCreationData);
    connect(m_apiManager, &ApiManager::adminDeleteSucess, this, &MainWindow::loadAdminList);
    connect(m_apiManager, &ApiManager::sessionDeleteSucess, this, &MainWindow::loadSessionCreationData);
    connect(m_apiManager, &ApiManager::userDeleteSucess, this, &MainWindow::loadUserList);
}


MainWindow::~MainWindow()
{
    delete m_apiManager;
    delete ui;
}

void MainWindow::newWindow(){
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}
void MainWindow::backPage(){
    m_isAdmin = false;
    ui->logoutButton->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
}

void MainWindow::backWindow(){
    for (QPushButton *button : m_placesButtons) {
        button->setStyleSheet("background-color: green; color: white;font-weight: bold;border: none;border-radius: 8px;");
        button->setChecked(false);
    }
    m_numOfPlaces.clear();
    m_rez = 0;
    ui->suma->setText("Сума квитка: 0 грн");
    ui->label_2->setText("Здача :");
    ui->lineEdit->clear();
    ui->stackedWidget->setCurrentWidget(m_windowSessions);
}
void MainWindow::colourSeat(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    int sumaBillet = 200;

    if(clickedButton->isChecked()){
        clickedButton->setStyleSheet("background-color: yellow; color: black;font-weight: bold;border: none;border-radius: 8px;");
        m_rez += sumaBillet;
    }
    else {
        clickedButton->setStyleSheet("background-color: green; color: white;font-weight: bold;border: none;border-radius: 8px;");
        m_rez -= sumaBillet;

    }
    ui->suma->setText("Сума квитка: " + QString::number(m_rez) + " грн");
}

void MainWindow::onCalculateRemainder(){
    int cash = ui->lineEdit->text().toInt();
    int change = cash - m_rez;
    if(change >= 0){
        ui->label_2->setText("Здача: " + QString::number(change) + " грн");
        emit reservedPlaces();
    }
    else{
        ui->label_2->setText("Упсс...Бракує коштів або ви ввели щось інше");
    }

}

void MainWindow::selectSession(int numOfSession){
    m_session = numOfSession;
    markReservePlaces();
    //markReserveUnPlaces();
}

void MainWindow::selectPlaces(int numOfPlace){
    m_numOfPlaces.push_back(numOfPlace);
}
void MainWindow::logIn(){

    m_apiManager->loginUser(ui->lineEdit_2->text(), ui->lineEdit_3->text());

}
void MainWindow::adminlogIn(){

    m_apiManager->loginAdmin(ui->lineEdit_7->text(), ui->lineEdit_8->text());

}
void MainWindow::goToPageRegIn(){
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::goToAdmin(){
    m_isAdmin = true;
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::regIn(){
    m_apiManager->registerUser(ui->lineEdit_4->text(), ui->lineEdit_5->text(), ui->lineEdit_6->text());
}

void MainWindow::regDone(){
    ui->logoutButton->setVisible(true);
    if(m_isAdmin){
        ui->stackedWidget->setCurrentIndex(5);
        loadUserList();
        loadAdminList();
        loadSessionCreationData();
        loadAdminMovieList();
        loadAdminSessionList();
    }else{
        ui->stackedWidget->setCurrentIndex(3);
    }

    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();

}

void MainWindow::onReservePlaces(){
    for(int numOfPlace : m_numOfPlaces){
        qDebug() << m_session << " " << numOfPlace << "/n";
        m_apiManager->reservePlace(m_session, numOfPlace);
        if (numOfPlace > 0 && numOfPlace <= m_placesButtons.size()) {
            QPushButton *buttonToReserve = m_placesButtons[numOfPlace - 1];
            buttonToReserve->setStyleSheet("background-color: grey; color: black;font-weight: bold;border: none;border-radius: 8px;");
            buttonToReserve->setEnabled(false);
        }
    }
    m_numOfPlaces.clear();
}

void MainWindow::onUnReservePlaces(){
    qDebug();
    for (int i = 0; i < m_placesButtons.size(); ++i) {
        QPushButton *button = m_placesButtons[i];
        if (!button->isEnabled()) {
            int numOfPlace = i + 1;
            qDebug() << m_session << numOfPlace;
            m_apiManager->unreservePlace(m_session, numOfPlace);
            button->setChecked(true);
            m_placesButtons[i]->setStyleSheet("background-color: green; color: white;font-weight: bold;border: none;border-radius: 8px;");
        }
    }
}


void MainWindow::markReservePlaces(){
    QVector<int> reservePlaces = m_apiManager->getReservePlaces(m_session);
    qDebug() << reservePlaces.size() << "\n";
    for(int i  = 0; i < reservePlaces.size(); ++i){
        qDebug() << reservePlaces[i] << "\n";
        if(reservePlaces[i] == 1){
            m_placesButtons[i]->setEnabled(false);
            m_placesButtons[i]->setStyleSheet("background-color: grey; color: black;font-weight: bold;border: none;border-radius: 8px;");
        }else{
            m_placesButtons[i]->setEnabled(true);
        }
    }
}

void MainWindow::markUnReservePlaces(){
    QVector<int> reservePlaces = m_apiManager->getReservePlaces(m_session);
    qDebug() << reservePlaces.size() << "\n";
    for(int i  = 0; i < reservePlaces.size(); ++i){
        qDebug() << reservePlaces[i] << "\n";
        if(reservePlaces[i] == 0){
            m_placesButtons[i]->setEnabled(false);
            m_placesButtons[i]->setStyleSheet("background-color: grey; color: black;font-weight: bold;border: none;border-radius: 8px;");
        }else{
            m_placesButtons[i]->setEnabled(true);
        }
    }
}

void MainWindow::parseMoviesArr(const QJsonArray& moviesArr){
    for (int i = 0; i < moviesArr.size(); ++i) {
        QJsonObject movieObj = moviesArr[i].toObject();

        Movie movie;
        movie.id = movieObj["id"].toInt();
        movie.title = movieObj["title"].toString();
        movie.genre = movieObj["genre"].toString();
        movie.posterUrl = movieObj["linkPoster"].toString();
    }
}

void MainWindow::errorLogIn(const QString& message){
    QMessageBox::information(this, "Login Error", message);
}

void MainWindow::errorRegIn(const QString& message){
    QMessageBox::information(this, "Registration Error", message);
}
void MainWindow::adminPage(){

    ui->stackedWidget->setCurrentIndex(5);
    loadSessionCreationData();
    loadUserList();
    loadAdminList();
    loadAdminMovieList();
    loadAdminSessionList();
}
void MainWindow::loadUserList()
{
    QVector<User> users = m_apiManager->getAllUsers();
    QTableWidget* table = ui->usersTableWidget;
    table->clearContents();
    table->setRowCount(users.size());
    table->setColumnCount(4);
    QStringList headers;
    headers << "ID" << "Логін" << "Email" << "Дія";
    table->setHorizontalHeaderLabels(headers);
    table->verticalHeader()->setVisible(false);
    for (int i = 0; i < users.size(); ++i) {
        const User& user = users.at(i);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(user.id));
        QTableWidgetItem* loginItem = new QTableWidgetItem(user.login);
        QTableWidgetItem* emailItem = new QTableWidgetItem(user.email);
        table->setItem(i, 0, idItem);
        table->setItem(i, 1, loginItem);
        table->setItem(i, 2, emailItem);
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        loginItem->setFlags(loginItem->flags() & ~Qt::ItemIsEditable);
        emailItem->setFlags(emailItem->flags() & ~Qt::ItemIsEditable);
        QPushButton* deleteButton = new QPushButton("Видалити");
        deleteButton->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border: 1px solid #dc3545; padding: 5px; }");
        table->setCellWidget(i, 3, deleteButton);
        table->horizontalHeader()->setStretchLastSection(true);
        table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
        connect(deleteButton, &QPushButton::clicked, [this, userId = user.id]() {
            this->deleteUserClicked(userId);
        });
    }
    for (int col = 0; col < 4; ++col) {
        table->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Fixed);
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);

}
void MainWindow::loadAdminList(){
    QTableWidget* table = ui->adminsTableWidget;
    QVector<Admin> admins = m_apiManager->getAllAdmins();
    table->clearContents();
    table->setRowCount(admins.size());
    table->setColumnCount(4);
    QStringList headers;
    headers << "ID" << "Логін" << "IP-адреса" << "Дія";
    table->setHorizontalHeaderLabels(headers);
    table->verticalHeader()->setVisible(false);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
    for (int i = 0; i < admins.size(); ++i) {
        const Admin& admin = admins.at(i);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(admin.id));
        QTableWidgetItem* loginItem = new QTableWidgetItem(admin.login);
        QTableWidgetItem* ipItem = new QTableWidgetItem(admin.ip);
        table->setItem(i, 0, idItem);
        table->setItem(i, 1, loginItem);
        table->setItem(i, 2, ipItem);
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        loginItem->setFlags(loginItem->flags() & ~Qt::ItemIsEditable);
        ipItem->setFlags(ipItem->flags() & ~Qt::ItemIsEditable);
        QPushButton* deleteButton = new QPushButton("Видалити");
        table->setCellWidget(i, 3, deleteButton);
        deleteButton->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border: 1px solid #dc3545; padding: 5px; }");
        connect(deleteButton, &QPushButton::clicked, [this, adminId = admin.id]() {
            this->deleteAdminClicked(adminId);
        });
    }
}

void MainWindow::deleteAdminClicked(int adminId)
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження видалення",
                                  "Ви впевнені, що хочете видалити адміністратора з ID " + QString::number(adminId) + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_apiManager->deleteAdmin(adminId);
        loadAdminList();
        QMessageBox::information(this, "Успіх", "Адміністратор з ID " + QString::number(adminId) + " успішно видалений.");
    }
}

void MainWindow::deleteUserClicked(int userId)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження видалення",
                                  "Ви впевнені, що хочете видалити користувача з ID " + QString::number(userId) + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }
    m_apiManager->deleteUser(userId);
    //connect(m_apiManager, &ApiManager::)
    loadUserList();
    QMessageBox::information(this, "Успіх", "Користувач з ID " + QString::number(userId) + " успішно видалений.");
}
void MainWindow::on_addMovieButton_clicked()
{
    QString title = ui->movieTitleEdit->text();
    int duration = ui->movieDurationEdit->text().toInt();
    QString genre = ui->movieGenreEdit->text();
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Вибрати постер для фільму",
                                                    QDir::homePath(),
                                                    "Зображення (*.png *.jpg *.jpeg)");

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Попередження", "Вибір файлу постера скасовано.");
        return;
    }
    if (title.isEmpty() || duration <= 0 || genre.isEmpty()) {
        QMessageBox::critical(this, "Помилка", "Будь ласка, заповніть усі поля коректними даними.");
        return;
    }
    m_apiManager->addMovie(title, duration, genre, filePath);

    QMessageBox::information(this, "Завантаження", "Розпочато завантаження постера та додавання фільму. Очікуйте...");
}
void MainWindow::handleMovieAddSuccess(const QString& message)
{
    QMessageBox::information(this, "Успіх", "Фільм успішно додано: " + message);

    setMovies();
    ui->movieTitleEdit->clear();
    ui->movieDurationEdit->clear();
    ui->movieGenreEdit->clear();
}

void MainWindow::handleMovieAddError(const QString& error)
{
    QMessageBox::critical(this, "Помилка", "Помилка додавання фільму: " + error);
}
void MainWindow::loadSessionCreationData()
{
    ui->sessionMovieComboBox->clear();
    ui->sessionHallComboBox->clear();
    QVector<Movie> movies = m_apiManager->getAllMovies();
    for (const Movie& movie : movies) {
        ui->sessionMovieComboBox->addItem(movie.title, movie.id);
    }
    QVector<Hall> halls = m_apiManager->getAllHalls();

    if (halls.isEmpty()) {
        qWarning() << "Помилка завантаження залів або залів не знайдено.";
        ui->sessionHallComboBox->addItem("— Зали не завантажено —", 0);
    } else {
        for (const Hall& hall : halls) {
            QString hallDisplay = QString("%1 (Місць: %2)").arg(hall.name).arg(hall.seatCount);
            ui->sessionHallComboBox->addItem(hallDisplay, hall.id);
        }
    }
    ui->sessionDateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(60));
}
void MainWindow::on_addSessionButton_clicked()
{
    int movie_id = ui->sessionMovieComboBox->currentData().toInt();
    int hall_id = ui->sessionHallComboBox->currentData().toInt();

    QDateTime selectedDateTime = ui->sessionDateTimeEdit->dateTime();
    if (movie_id <= 0 || hall_id <= 0 || selectedDateTime < QDateTime::currentDateTime()) {
        QMessageBox::critical(this, "Помилка", "Будь ласка, оберіть фільм, зал та час у майбутньому.");
        return;
    }
    QString dateTimeString = selectedDateTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->addSessionButton->setEnabled(false);
    m_apiManager->addSession(movie_id, hall_id, dateTimeString);
}
void MainWindow::handleSessionAddSuccess(const QString& message)
{
    QMessageBox::information(this, "Успіх", "Сеанс успішно додано: " + message);
    ui->addSessionButton->setEnabled(true);
}

void MainWindow::handleSessionAddError(const QString& error)
{
    QMessageBox::critical(this, "Помилка", "Помилка додавання сеансу: " + error);
    ui->addSessionButton->setEnabled(true);
}
void MainWindow::loadAdminMovieList()
{
    QVector<Movie> movies = m_apiManager->getAllMovies();
    QTableWidget* table = ui->adminMoviesTable;
    table->setRowCount(movies.size());
    table->setColumnCount(4);
    QStringList headers;
    headers << "ID" << "Назва" << "Жанр" << "Дії";
    table->setHorizontalHeaderLabels(headers);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    for (int row = 0; row < movies.size(); ++row) {
        const Movie& movie = movies.at(row);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(movie.id));
        table->setItem(row, 0, idItem);
        QTableWidgetItem* titleItem = new QTableWidgetItem(movie.title);
        table->setItem(row, 1, titleItem);
        QTableWidgetItem* genreItem = new QTableWidgetItem(movie.genre);
        table->setItem(row, 2, genreItem);
        QPushButton* deleteBtn = new QPushButton("Видалити");
        deleteBtn->setProperty("movieId", movie.id);
        deleteBtn->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border: 1px solid #dc3545; padding: 5px; }");
        connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteMovieButtonClicked);
        table->setCellWidget(row, 3, deleteBtn);
    }
    table->clearSelection();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void MainWindow::deleteMovieButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    int movieId = button->property("movieId").toInt();
    if (QMessageBox::question(this, "Підтвердження",
                              "Ви впевнені, що хочете видалити цей фільм? Це видалить усі пов'язані сеанси!",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        m_apiManager->deleteMovie(movieId);
    }
    //connect(m_apiManager, &ApiManager::movieDeleteSuccess, this, &MainWindow::loadAdminMovieList);
    //loadAdminMovieList();
}
void MainWindow::handleMovieDeleteSuccess(const QString& message)
{
    QMessageBox::information(this, "Успіх", message);
    loadAdminMovieList();
}

void MainWindow::handleMovieDeleteError(const QString& error)
{
    QMessageBox::critical(this, "Помилка", "Помилка видалення фільму: " + error);
}
void MainWindow::on_registerAdminButton_clicked()
{
    QString login = ui->adminLoginRegisterEdit->text();
    QString password = ui->adminPasswordRegisterEdit->text();
    QString admin_ip = ui->adminIpRegisterEdit->text();

    if (login.isEmpty() || password.isEmpty() || admin_ip.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Всі поля мають бути заповнені.");
        return;
    }
    qDebug() << "registerAdmin1";
    m_apiManager->registerAdmin(login, password, admin_ip);
}

void MainWindow::handleAdminRegistrationSuccess(const QString& message)
{
    QMessageBox::information(this, "Успіх", "Адміністратора успішно зареєстровано: " + message);
    ui->adminLoginRegisterEdit->clear();
    ui->adminPasswordRegisterEdit->clear();
    ui->adminIpRegisterEdit->clear();
    loadAdminList();
}

void MainWindow::handleAdminRegistrationError(const QString& error)
{
    QMessageBox::critical(this, "Помилка реєстрації", "Не вдалося зареєструвати адміністратора: " + error);
}
void MainWindow::loadAdminSessionList()
{
    QVector<Session> sessions = m_apiManager->getAllSessions();
    QTableWidget* table = ui->adminSessionsTable;
    table->clearContents();
    table->setRowCount(sessions.size());
    table->setColumnCount(6);
    QStringList headers = {"ID", "Фільм", "Зал", "Час початку", "Видалення","Розбронювання"};
    table->setHorizontalHeaderLabels(headers);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    for (int row = 0; row < sessions.size(); ++row) {
        const Session& session = sessions.at(row);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(session.id));
        table->setItem(row, 0, idItem);
        table->setItem(row, 1, new QTableWidgetItem(session.movie_title));
        table->setItem(row, 2, new QTableWidgetItem(session.hallName));
        QString formattedDateTime = QString("%1 %2").arg(session.date).arg(session.time);
        table->setItem(row, 3, new QTableWidgetItem(formattedDateTime));
        QPushButton* deleteButton = new QPushButton("Видалити");
        deleteButton->setProperty("sessionId", session.id);
        deleteButton->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border: 1px solid #dc3545; padding: 5px; }");
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSessionButtonClicked);
        table->setCellWidget(row, 4, deleteButton);
        QPushButton* unreserveBtn = new QPushButton("Очистити");
        unreserveBtn->setStyleSheet("background-color: #f0ad4e; color: white; padding: 5px; border-radius: 4px;");
        connect(unreserveBtn, &QPushButton::clicked, this, [this, sessionId = session.id]() {
            this->handleUnreserveSession(sessionId);
        });
        table->setCellWidget(row, 5, unreserveBtn);
        for (int col = 0; col < table->columnCount() - 1; ++col) {
            if (table->item(row, col)) {
                table->item(row, col)->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    table->clearSelection();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void MainWindow::handleUnreserveSession(int sessionId) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Скасування бронювань",
                                                              QString("Ви дійсно хочете розбронювати ВСІ місця для сеансу №%1?").arg(sessionId),
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int seatsCount = m_placesButtons.size();
        for (int i = 0; i < seatsCount; ++i) {
            int seatNumber = i + 1;
            if(!m_placesButtons[i]->isEnabled()){
                m_apiManager->unreservePlace(sessionId, seatNumber);
            }
        }

        QMessageBox::information(this, "Успіх", "Запити на розбронювання надіслано.");
        if (m_session == sessionId) {
            for (QPushButton *button : m_placesButtons) {
                button->setEnabled(true);
                button->setChecked(false);
                button->setStyleSheet("background-color: green; color: white; font-weight: bold; border: none; border-radius: 8px;");
            }
            m_rez = 0;
            ui->suma->setText("Сума квитка: 0 грн");
        }
    }
}
void MainWindow::deleteSessionButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    int sessionId = button->property("sessionId").toInt();
    if (sessionId <= 0) {
        QMessageBox::critical(this, "Помилка", "Не вдалося визначити ID сеансу.");
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження видалення",
                                  "Ви впевнені, що хочете видалити сеанс з ID " + QString::number(sessionId) + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }
    m_apiManager->deleteSession(sessionId);
    loadAdminSessionList();
    QMessageBox::information(this, "Успіх", "Сеанс з ID " + QString::number(sessionId) + " успішно видалено.");
}
void MainWindow::on_addHallButton_clicked()
{
    QString hallName = ui->hallNameEdit->text().trimmed();
    int seatCount = ui->hallSeatsEdit->text().toInt();
    if (hallName.isEmpty() || seatCount <= 0) {
        QMessageBox::warning(this, "Помилка", "Будь ласка, введіть коректну назву залу та кількість місць.");
        return;
    }
    m_apiManager->addHall(hallName, seatCount);
    QMessageBox::information(this, "Успіх", "Запит на додавання залу надіслано.");
    ui->hallNameEdit->clear();
    ui->hallSeatsEdit->clear();

    loadSessionCreationData();
}
void MainWindow::showPassword(){
    if (ui->checkBox->isChecked()) {
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}
void MainWindow::showPasswordAdmin(){
    if (ui->checkBox_2->isChecked()) {
        ui->lineEdit_8->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_8->setEchoMode(QLineEdit::Password);
    }
}
