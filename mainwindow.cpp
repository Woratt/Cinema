#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //m_sessionButtons = {ui->pushButton, ui->pushButton_3, ui->pushButton_4,
    //                   ui->pushButton_5, ui->pushButton_6, ui->pushButton_7
    //};

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
    ui->tableWidget->setRowCount(10);
    ui->stackedWidget->addWidget(m_windowSessions);
    setupTable();
    setUpConnections();
    setMovies();
    ui->lineEdit_2->setText("Andrii4");
    ui->lineEdit_3->setText("12345678");
    m_apiManager->addSession(1, 1, 0);
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

    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->setColumnWidth(col, 150);
    }
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
    parseMoviesArr(m_apiManager->getAllMovies());
    int row = 0;
    int col = 0;
    for(int i = 0; i < m_moviesList.size(); ++i){
        MovieWidget *movieWidget = new MovieWidget(this);
        LoadPoster *loadPoster = new LoadPoster(this);
        loadPoster->loadImage(m_moviesList[i].posterUrl);
        connect(loadPoster, &LoadPoster::imageLoaded, this, [=](const QPixmap& map){
            movieWidget->setMovieData(m_moviesList[i].id, m_moviesList[i].title, map);
            ui->tableWidget->setCellWidget(row, col, movieWidget);
        });
        connect(movieWidget, &MovieWidget::doubleClicked, this, [=](){
            m_windowSessions->setSessions(m_apiManager->getSessionsForMovie(movieWidget->movieId()), movieWidget->movieId());
            ui->stackedWidget->setCurrentWidget(m_windowSessions);
        });

        if((i + 1) % 7 == 0){
            ++row;
            col = 0;
        }else{
            ++col;
        }
    }
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        ui->tableWidget->setRowHeight(row, 250);
    }
}

void MainWindow::setUpConnections(){
    int numOfSession = 1;
    int numOfPlace = 1;
    /*for(auto sessionBt : m_sessionButtons){
        connect(sessionBt, &QPushButton::clicked, this, [=](){
            selectSession(numOfSession);
        });
        connect(sessionBt, &QPushButton::clicked, this, &MainWindow::markReservePlaces);
        connect(sessionBt, &QPushButton::clicked, this, &MainWindow::newWindow);

        ++numOfSession;
    }*/
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
    connect(ui->pushButton_30, &QPushButton::clicked, this, &MainWindow::goToPageRegIn);
    connect(ui->pushButton_31, &QPushButton::clicked, this, &MainWindow::regIn);


    connect(m_apiManager, &ApiManager::loginSuccess, this, &MainWindow::regDone);
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
    //connect(m_windowSessions, &WindowSessions::sessionSelected, this, &MainWindow::markReservePlaces);
    //onnect(m_windowSessions, &WindowSessions::sessionSelected, this, &MainWindow::newWindow);
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
void MainWindow::goToPageRegIn(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::regIn(){
    m_apiManager->registerUser(ui->lineEdit_4->text(), ui->lineEdit_5->text(), ui->lineEdit_6->text());
}

void MainWindow::regDone(){
    ui->stackedWidget->setCurrentIndex(2);

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

        m_moviesList.append(movie);
    }
}

void MainWindow::errorLogIn(const QString& message){
    QMessageBox::information(this, "Login Error", message);
}

void MainWindow::errorRegIn(const QString& message){
    QMessageBox::information(this, "Registration Error", message);
}
