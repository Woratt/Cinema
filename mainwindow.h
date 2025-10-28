#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>

#include "apimanager.h"

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

    // set connections
    void setUpConnections();

private slots:
    void colourSeat();
    void onCalculateRemainder();
    void newWindow();
    void backWindow();
    void selectSession(int);
    void selectPlaces(int);

};

#endif // MAINWINDOW_H
