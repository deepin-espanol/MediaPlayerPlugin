#ifndef DDE_BASICDOCK_H
#define DDE_BASICDOCK_H

#include <QWidget>
#include <QSettings>

class MediaApplet : public QWidget
{
    Q_OBJECT
public:
    explicit MediaApplet(QWidget *parent = nullptr);

    bool enabled();
    void setEnabled(const bool b);

private:
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    QSettings m_settings;
};

#endif // DDE_BASICDOCK_H
