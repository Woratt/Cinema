#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QLineEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

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
    connect(ui->pushButton_32, &QPushButton::clicked, this, &MainWindow::onUnReservePlaces);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::backWindow);
    connect(ui->pushButton_29, &QPushButton::clicked, this, &MainWindow::logIn);
    connect(ui->pushButton_34, &QPushButton::clicked, this, &MainWindow::adminlogIn);
    connect(ui->pushButton_30, &QPushButton::clicked, this, &MainWindow::goToPageRegIn);
    connect(ui->pushButton_31, &QPushButton::clicked, this, &MainWindow::regIn);

    connect(m_apiManager, &ApiManager::loginSuccess, this, &MainWindow::regDone);
    connect(m_apiManager, &ApiManager::adminLoginSuccess, this, &MainWindow::regDone);

    connect(m_apiManager, &ApiManager::loginError, this, &MainWindow::errorLogIn);
    connect(m_apiManager, &ApiManager::registrationSuccess, this, &MainWindow::regDone);
    connect(m_apiManager, &ApiManager::registrationError, this, &MainWindow::errorRegIn);

    connect(m_apiManager, &ApiManager::loginError, this, &MainWindow::errorLogIn);

    connect(m_windowSessions, &WindowSessions::sessionSelected, this, [=](int sessionId){
        selectSession(sessionId);
        newWindow();
    });
    connect(m_windowSessions, &WindowSessions::backRequested, this, [=](){
         ui->stackedWidget->setCurrentWidget(ui->page);
    });
    connect(ui->checkBox, &QCheckBox::toggled, this, &MainWindow::showPassword);
}


MainWindow::~MainWindow()
{
    delete m_apiManager;
    delete ui;
}

void MainWindow::newWindow(){
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::backWindow(){
    for (QPushButton *button : m_placesButtons) {
        button->setStyleSheet("background-color: green;;color: white;font-weight: bold;border: none;border-radius: 8px;");
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
        clickedButton->setStyleSheet("background-color: yellow;color: black;font-weight: bold;border: none;border-radius: 8px;");
        m_rez += sumaBillet;
    }
    else {
        clickedButton->setStyleSheet("background-color: green;;color: white;font-weight: bold;border: none;border-radius: 8px;");
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
    if(m_isAdmin){
        ui->stackedWidget->setCurrentIndex(5);
        loadUserList();
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
            buttonToReserve->setStyleSheet("background-color: grey;color: black;font-weight: bold;border: none;border-radius: 8px;");
            buttonToReserve->setEnabled(false);
        }
    }
    m_numOfPlaces.clear();
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

void MainWindow::parseMoviesArr(const QJsonArray& moviesArr){
    for (int i = 0; i < moviesArr.size(); ++i) {
        QJsonObject movieObj = moviesArr[i].toObject();

        Movie movie;
        movie.id = movieObj["id"].toInt();
        movie.title = movieObj["title"].toString();
        movie.genre = movieObj["genre"].toString();
        movie.posterUrl = movieObj["linkPoster"].toString();

        //m_moviesList.append(movie);
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
    loadUserList();
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
        table->setCellWidget(i, 3, deleteButton);
        connect(deleteButton, &QPushButton::clicked, [this, userId = user.id]() {
            this->deleteUserClicked(userId);
        });
    }
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
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
    loadUserList();
    QMessageBox::information(this, "Успіх", "Користувач з ID " + QString::number(userId) + " успішно видалений.");
}
void MainWindow::showPassword(){
    if (ui->checkBox->isChecked()) {
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}
