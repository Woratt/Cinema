#include "SessionWidget.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

SessionWidget::SessionWidget(int sessionId,
                             const QString &time,
                             const QString &hall,
                             const QString &date,
                             QWidget *parent)
    : QGroupBox(parent),
    sessionId_(sessionId),
    m_timeLabel(nullptr),
    m_hallLabel(nullptr),
    m_dateLabel(nullptr),
    m_bookButton(nullptr),
    m_mainLayout(nullptr),
    m_topLayout(nullptr),
    m_bottomLayout(nullptr)
{
    initUI();
    setupLayouts();
    setupConnections();

    m_dateLabel->setText(date);
    m_timeLabel->setText(time);
    m_hallLabel->setText(hall);
}

void SessionWidget::initUI()
{
    m_dateLabel = new QLabel(this);
    m_timeLabel = new QLabel(this);
    m_hallLabel = new QLabel(this);
    m_bookButton = new QPushButton("Забронювати", this);

    m_dateLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_hallLabel->setAlignment(Qt::AlignCenter);

    m_bookButton->setCursor(Qt::PointingHandCursor);
}

void SessionWidget::setupLayouts()
{
    m_topLayout = new QHBoxLayout();
    m_topLayout->addWidget(m_timeLabel);
    m_topLayout->addWidget(m_hallLabel);

    m_dateLayout = new QHBoxLayout();
    m_dateLayout->addWidget(m_dateLabel);

    m_bottomLayout = new QHBoxLayout();
    m_bottomLayout->addWidget(m_bookButton);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addLayout(m_dateLayout);
    m_mainLayout->addLayout(m_topLayout);
    m_mainLayout->addLayout(m_bottomLayout);

    setLayout(m_mainLayout);

    setFixedSize(300, 160);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void SessionWidget::setupConnections()
{
    connect(m_bookButton, &QPushButton::clicked,
            this, &SessionWidget::onBookButtonClicked);
}



void SessionWidget::setCompactMode(bool compact)
{
    if (compact) {
        setFixedSize(200, 120);
        m_timeLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
        m_hallLabel->setStyleSheet("font-size: 12px;");
    } else {
        setFixedSize(300, 160);
        m_timeLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
        m_hallLabel->setStyleSheet("font-size: 14px;");
    }
}

void SessionWidget::resizeEvent(QResizeEvent *event)
{
    if (event->size().width() < 250) {
        setCompactMode(true);
    } else {
        setCompactMode(false);
    }
    QGroupBox::resizeEvent(event);
}

void SessionWidget::onBookButtonClicked()
{
    emit bookButtonClicked(sessionId_);
}
