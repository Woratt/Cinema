#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>

#include "apimanager.h"
#include "loadposter.h"
#include "moviewidget.h"
#include "windowsessions.h"

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
    bool m_isAdmin{false};
    int m_rez = 0;
    int m_session = 0;
    int m_movies;
    QVector<int> m_numOfPlaces;
    QVector<QPushButton*> m_placesButtons;
    QVector<QPushButton*> m_sessionButtons;
    QVector<QPushButton*> m_registButtons;
    //QList<Movie> m_moviesList;

    QTabletEvent *m_table;
    LoadPoster *m_loadPoster;

    WindowSessions *m_windowSessions;

    // set connections
    void setUpConnections();
    void setMovies();
    void adjustTableSize();
    void setupTable();
    void resizeEvent(QResizeEvent *event) override;

    //Api
    ApiManager *m_apiManager;

    void parseMoviesArr(const QJsonArray&);

    //User
    User *m_user;
signals:
    void reservedPlaces();
    void unreservedPlaces();

private slots:
    void colourSeat();
    void onCalculateRemainder();
    void newWindow();
    void backWindow();
    void selectSession(int);
    void selectPlaces(int);
    void logIn();
    void adminlogIn();
    void goToPageRegIn();
    void regIn();
    void regDone();
    void onReservePlaces();
    void onUnReservePlaces();
    void goToAdmin();
    void loadUserList();
    void loadAdminList();
    void markReservePlaces();
    void markUnReservePlaces();
    void adminPage();
    void showPassword();
    void backPage();
    void showPasswordAdmin();
    //void markUnReservePlaces();

    void errorLogIn(const QString&);
    void errorRegIn(const QString&);

    void deleteUserClicked(int userID);
    void deleteAdminClicked(int adminId);

    void on_addMovieButton_clicked();
    void handleMovieAddSuccess(const QString& message);
    void handleMovieAddError(const QString& error);

    void on_addSessionButton_clicked();
    void handleSessionAddSuccess(const QString& message);
    void handleSessionAddError(const QString& error);
    void loadSessionCreationData();

    void deleteMovieButtonClicked();
    void handleMovieDeleteSuccess(const QString& message);
    void handleMovieDeleteError(const QString& error);
    void loadAdminMovieList();

    void on_registerAdminButton_clicked();
    void handleAdminRegistrationSuccess(const QString& message);
    void handleAdminRegistrationError(const QString& error);

   // void deleteSessionButtonClicked();
   // void handleSessionDeleteSuccess(const QString& message);
   // void handleSessionDeleteError(const QString& error);

};

#endif // MAINWINDOW_H
