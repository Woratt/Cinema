#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    m_sessionButtons = {ui->pushButton, ui->pushButton_3, ui->pushButton_4,
                       ui->pushButton_5, ui->pushButton_6, ui->pushButton_7
    };

    m_placesButtons = {ui->pushButton_9, ui->pushButton_10, ui->pushButton_11,
                        ui->pushButton_12, ui->pushButton_13, ui->pushButton_14,
                        ui->pushButton_15, ui->pushButton_16, ui->pushButton_17,
                        ui->pushButton_18, ui->pushButton_19, ui->pushButton_20,
                        ui->pushButton_21, ui->pushButton_22, ui->pushButton_23,
                        ui->pushButton_24, ui->pushButton_25, ui->pushButton_26,
                        ui->pushButton_27, ui->pushButton_28,
                        };

    m_apiManager = new ApiManager();
    setUpConnections();
}

void MainWindow::setUpConnections(){
    int numOfSession = 1;
    int numOfPlace = 1;
    for(auto sessionBt : m_sessionButtons){
        connect(sessionBt, &QPushButton::clicked, this, [=](){
            selectSession(numOfSession);
        });
        connect(sessionBt, &QPushButton::clicked, this, &MainWindow::newWindow);
        ++numOfSession;
    }
    for(auto placeBt : m_placesButtons){
        connect(placeBt, &QPushButton::clicked, this, [=](){
            selectPlaces(numOfPlace);
        });
        connect(placeBt, &QPushButton::clicked, this, &MainWindow::colourSeat);
        ++numOfPlace;
    }

    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::reservePlaces);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::onCalculateRemainder);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::backWindow);
    connect(ui->pushButton_29, &QPushButton::clicked, this, &MainWindow::logIn);
    connect(ui->pushButton_30, &QPushButton::clicked, this, &MainWindow::goToPageRegIn);
    connect(ui->pushButton_31, &QPushButton::clicked, this, &MainWindow::regIn);


    connect(m_apiManager, &ApiManager::loginSuccess, this, &MainWindow::regDone);
    connect(m_apiManager, &ApiManager::loginError, this, &MainWindow::errorLogIn);
    connect(m_apiManager, &ApiManager::registrationSuccess, this, &MainWindow::regDone);
    connect(m_apiManager, &ApiManager::registrationError, this, &MainWindow::errorRegIn);

    connect(m_apiManager, &ApiManager::loginError, this, &MainWindow::errorLogIn);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newWindow(){
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::backWindow(){
    for (QPushButton *button : m_placesButtons) {
        button->setStyleSheet("background-color: green;;color: white;font-weight: bold;border: none;border-radius: 8px;");
        button->setChecked(false);
    }
    m_rez = 0;
    ui->suma->setText("Сума квитка: 0 грн");
    ui->label_2->setText("Здача :");
    ui->lineEdit->clear();
    ui->stackedWidget->setCurrentIndex(2);
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
    }
    else{
        ui->label_2->setText("Упсс...Бракує коштів або ви ввели щось інше");
    }
}

void MainWindow::selectSession(int numOfSession){
    m_session = numOfSession;
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

void MainWindow::reservePlaces(){
    for(int numOfPlace : m_numOfPlaces){
        qDebug() << m_session << " " << numOfPlace << "/n";
        m_apiManager->reservePlace(m_session, numOfPlace);
    }
    m_numOfPlaces.clear();
}

void MainWindow::errorLogIn(const QString& message){
    QMessageBox::information(this, "Login Error", message);
}

void MainWindow::errorRegIn(const QString& message){
    QMessageBox::information(this, "Registration Error", message);
}
