#ifndef MOVIEWIDGET_H
#define MOVIEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QResizeEvent>
#include <QLabel>
#include <QProgressBar>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>


class MovieWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MovieWidget(QWidget *parent = nullptr);
    ~MovieWidget();

    void setMovieData(int id, const QString &title, const QPixmap &poster);
    void setPoster(const QPixmap &pixmap);
    void setTitle(const QString &title);
    void setMovieId(int id);

    int movieId() const { return m_movieId; }
    QString title() const { return m_title; }
    QPixmap poster() const { return m_originalPixmap; }

    static QStringList tableHeaders();
    QList<QTableWidgetItem*> tableItems() const;
public slots:
    void clear();

signals:
    void clicked(int movieId);
    void doubleClicked(int movieId);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void onImageLoaded(const QPixmap &pixmap);

private:
    void updateScaledPixmap();
    void setupUI();

    int m_movieId;
    QString m_title;

    QPixmap m_originalPixmap;
    QPixmap m_scaledPixmap;
    Qt::AspectRatioMode m_aspectRatioMode;
    bool m_pixmapChanged;

    QLabel *m_posterLabel;
    QLabel *m_titleLabel;
    QProgressBar *m_progressBar;
    QLabel *m_loadingLabel;
    QWidget *m_contentWidget;
};

#endif // MOVIEWIDGET_H
