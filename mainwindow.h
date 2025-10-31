#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QMessageBox>

#include "apimanager.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int m_rez = 0;
    int m_session = 0;
    int m_movies;
    QVector<int> m_numOfPlaces;
    QVector<QPushButton*> m_placesButtons;
    QVector<QPushButton*> m_sessionButtons;
    QVector<QPushButton*> m_registButtons;

    // set connections
    void setUpConnections();

    //Api
    ApiManager *m_apiManager;

    //User
    User *m_user;
signals:
    void reservedPlaces();

private slots:
    void colourSeat();
    void onCalculateRemainder();
    void newWindow();
    void backWindow();
    void selectSession(int);
    void selectPlaces(int);
    void logIn();
    void goToPageRegIn();
    void regIn();
    void regDone();
    void onReservePlaces();

    void markReservePlaces();

    void errorLogIn(const QString&);
    void errorRegIn(const QString&);

};

#endif // MAINWINDOW_H
