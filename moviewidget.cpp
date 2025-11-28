#include "moviewidget.h"

MovieWidget::MovieWidget(QWidget *parent)
    : QWidget(parent)
    , m_movieId(-1)
    , m_aspectRatioMode(Qt::KeepAspectRatio)
    , m_pixmapChanged(false)
{
    setupUI();
    setFixedSize(150, 230);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);
}


MovieWidget::~MovieWidget()
{
}

void MovieWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    m_contentWidget = new QWidget(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(m_contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(5);

    m_posterLabel = new QLabel(m_contentWidget);
    m_posterLabel->setAlignment(Qt::AlignCenter);
    m_posterLabel->setMinimumSize(120, 160);
    m_posterLabel->setScaledContents(false);

    m_titleLabel = new QLabel(m_contentWidget);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setMaximumHeight(40);

    contentLayout->addWidget(m_posterLabel);
    contentLayout->addWidget(m_titleLabel);

    mainLayout->addWidget(m_contentWidget);
}

void MovieWidget::setMovieData(int id, const QString &title, const QPixmap &poster)
{
    setMovieId(id);
    setTitle(title);
    setPoster(poster);
}

void MovieWidget::setPoster(const QPixmap &pixmap)
{
    if (pixmap.isNull()) {
        m_posterLabel->setText("Немає\nзображення");
        return;
    }

    m_originalPixmap = pixmap;
    m_pixmapChanged = true;
    updateScaledPixmap();

}

void MovieWidget::setTitle(const QString &title)
{
    m_title = title;
    m_titleLabel->setText(title);
}

void MovieWidget::setMovieId(int id)
{
    m_movieId = id;
}

void MovieWidget::clear()
{
    m_movieId = -1;
    m_title.clear();
    m_originalPixmap = QPixmap();
    m_scaledPixmap = QPixmap();
    m_titleLabel->clear();
    m_posterLabel->clear();
    m_posterLabel->setText("Немає\nзображення");
}

void MovieWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    if (underMouse()) {
        painter.setPen(QPen(QColor(100, 150, 255), 2));
        painter.drawRect(rect().adjusted(1, 1, -1, -1));
    }
}

void MovieWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateScaledPixmap();
}

void MovieWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (m_movieId != -1) {
        emit clicked(m_movieId);
    }
}

void MovieWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (m_movieId != -1) {
        emit doubleClicked(m_movieId);
    }
}

void MovieWidget::updateScaledPixmap()
{
    if (m_originalPixmap.isNull() || m_posterLabel->size().isEmpty())
        return;

    if (m_pixmapChanged || m_scaledPixmap.size() != m_posterLabel->size()) {
        m_scaledPixmap = m_originalPixmap.scaled(m_posterLabel->size(),
                                                 m_aspectRatioMode,
                                                 Qt::SmoothTransformation);
        m_posterLabel->setPixmap(m_scaledPixmap);
        m_pixmapChanged = false;
    }
}

void MovieWidget::onImageLoaded(const QPixmap &pixmap)
{
    setPoster(pixmap);
    sender()->deleteLater();
}


QStringList MovieWidget::tableHeaders()
{
    return {"ID", "Назва", "Постер"};
}

QList<QTableWidgetItem*> MovieWidget::tableItems() const
{
    QList<QTableWidgetItem*> items;

    QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(m_movieId));
    idItem->setData(Qt::UserRole, m_movieId);

    QTableWidgetItem *titleItem = new QTableWidgetItem(m_title);

    QTableWidgetItem *posterItem = new QTableWidgetItem(
        m_originalPixmap.isNull() ? "Немає" : "Є постер"
        );

    items << idItem << titleItem << posterItem;
    return items;
}
