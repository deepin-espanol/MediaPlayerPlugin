#include "mediaapplet.h"

#include "defs.h"

#include <QIcon>
#include <QApplication>
#include <QPainter>

#define PLUGIN_STATE_KEY "enable"

MediaApplet::MediaApplet(QWidget *parent) : QWidget(parent), m_settings("deepin", NAME) {}

bool MediaApplet::enabled()
{
    return m_settings.value(PLUGIN_STATE_KEY, true).toBool();
}

void MediaApplet::setEnabled(const bool b)
{
    m_settings.setValue(PLUGIN_STATE_KEY, b);
}

QSize MediaApplet::sizeHint() const
{
    return SIZE;
}

void MediaApplet::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void MediaApplet::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(rect().adjusted(2,0,0,0), QIcon(":/icons/icon.png").pixmap(rect().adjusted(2,0,0,0).size()), rect().adjusted(2,0,0,0));
}
