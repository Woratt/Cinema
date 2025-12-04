#ifndef WINDOWSESSIONS_H
#define WINDOWSESSIONS_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QScrollArea>

#include "apimanager.h"
#include "sessionwidget.h"

class WindowSessions : public QWidget
{
    Q_OBJECT
public:
    WindowSessions(QWidget* parent = nullptr);

    void setSessions(const QVector<Session>&, int);
private slots:
    //void onBookButtonClicked(int sessionId);
    //void clearAllSessions();
    //void addRandomSession();
signals:
    void sessionSelected(int);
    void backRequested();
private:
    void setupUI();
    void updateLayout();
    int m_movieId;
    QWidget *centralWidget_;
    QVBoxLayout *mainLayout_;
    QScrollArea *scrollArea_;
    QGridLayout *gridLayout_;
    QWidget *sessionsContainer_;
    QString parseTime(int);

    QVBoxLayout *sessionsLayout_;
    QVector<SessionWidget*> sessionWidgets_;
    int nextSessionId_ = 1;

    int sessionsPerRow_ = 3;
};

#endif // WINDOWSESSIONS_H
