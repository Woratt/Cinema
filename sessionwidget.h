#ifndef SESSIONWIDGET_H
#define SESSIONWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QObject>
#include <QEvent>


class SessionWidget : public QGroupBox
{
    Q_OBJECT
public:
    SessionWidget(int, const QString&, const QString&, const QString&, QWidget *parent = nullptr);
    ~SessionWidget() override = default;
    int getSessionId() const { return sessionId_; }
    QString getTime() const { return m_timeLabel->text().mid(3); }
    QString getHall() const { return m_hallLabel->text().mid(3); }
    void setCompactMode(bool compact);
signals:
    void bookButtonClicked(int sessionId);
    void sessionClicked(int);
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void onBookButtonClicked();
private:
    void initUI();
    void setupStyle();
    void setupLayouts();
    void setupConnections();

    int sessionId_;
    bool isSelected_;

    QLabel *m_timeLabel;
    QLabel *m_hallLabel;
    QLabel *m_dateLabel;
    QPushButton *m_bookButton;


    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_topLayout;
    QHBoxLayout *m_bottomLayout;
    QHBoxLayout *m_dateLayout;
};

#endif // SESSIONWIDGET_H
