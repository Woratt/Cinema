#include "windowsessions.h"

WindowSessions::WindowSessions(QWidget *parent): QWidget(parent) {
    setupUI();
}

void WindowSessions::setupUI()
{
    mainLayout_ = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Вибір сеансу");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    mainLayout_->addWidget(titleLabel);

    scrollArea_ = new QScrollArea();
    scrollArea_->setWidgetResizable(true);

    sessionsContainer_ = new QWidget();
    gridLayout_ = new QGridLayout(sessionsContainer_);
    gridLayout_->setSpacing(10);
    gridLayout_->setHorizontalSpacing(15);
    gridLayout_->setVerticalSpacing(15);

    scrollArea_->setWidget(sessionsContainer_);
    mainLayout_->addWidget(scrollArea_, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *backButton = new QPushButton("Назад");

    connect(backButton, &QPushButton::clicked, this, [=](){
        emit backRequested();
    });

    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    mainLayout_->addLayout(buttonLayout);

    setLayout(mainLayout_);
}


void WindowSessions::setSessions(const QVector<Session>& sessions, int movieId){
    m_movieId = movieId;

    QLayoutItem* item;
    while ((item = gridLayout_->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    qDeleteAll(sessionWidgets_);
    sessionWidgets_.clear();

    for (int i = 0; i < sessions.size(); i++) {
        const Session &session = sessions[i];

        SessionWidget *sessionWidget = new SessionWidget(
                session.id,
                parseTime(session.start_time),
                session.hallName,
                session.date.toString("dd.MM.yyyy")
            );
        int row = i / sessionsPerRow_;
        int col = i % sessionsPerRow_;
        gridLayout_->addWidget(sessionWidget, row, col);

        connect(sessionWidget, &SessionWidget::bookButtonClicked,
                this, [this, sessionId = session.id]() {
                    emit sessionSelected(sessionId);
                });
    }
}

QString WindowSessions::parseTime(int time){
    QString strTime = "";
    if(time / 60 < 10){
        strTime = QString("0" + QString::number(time / 60));
    }else{
        strTime = QString::number(time / 60);
    }
    strTime += ":";
    if(time % 60 < 10){
        strTime += QString("0" + QString::number(time % 60));
    }else{
        strTime += QString::number(time % 60);
    }
    return strTime;
}
