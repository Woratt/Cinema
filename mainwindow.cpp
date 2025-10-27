#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rez = 0;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(newWindow()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(newWindow()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(newWindow()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(newWindow()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(newWindow()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(newWindow()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this ,SLOT(backWindow()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(colourSeat()));
    connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(colourSeat()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newWindow(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::backWindow(){
    ui->stackedWidget->setCurrentIndex(0);

}



void MainWindow::colourSeat(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    int sumaBillet = 200;

    if(clickedButton->isChecked()){
        clickedButton->setStyleSheet("background-color: yellow;color: black;font-weight: bold;border: none;border-radius: 8px;");
        rez += sumaBillet;

    }
    else {
        clickedButton->setStyleSheet("background-color: green;;color: white;font-weight: bold;border: none;border-radius: 8px;");
        rez -= sumaBillet;

    }
    ui->suma->setText("Сума квитка: " + QString::number(rez) + " грн");




}

void MainWindow::on_pushButton_8_clicked(){
    int cash=ui->lineEdit->text().toInt();
    int change=cash-rez;
    if(change>=0){
        ui->label_2->setText("Здача :" +QString::number(change) + " грн");
    }
    else{
        ui->label_2->setText("Упсс...Бракує коштів або ви ввели шось інше");
    }
}

