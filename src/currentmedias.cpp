#include "currentmedias.h"

#include "defs.h"

#include <QListWidgetItem>
#include <QDBusInterface>
#include <QDBusPendingCall>

CurrentMedias::CurrentMedias(QWidget *p) : QListWidget(p)
{
    monitor = Dtk::Core::DSingleton<DMPRISMonitor>::instance();

    connect(monitor, &DMPRISMonitor::mprisAcquired, this, &CurrentMedias::addMPRIS);
    connect(monitor, &DMPRISMonitor::mprisLost, this, &CurrentMedias::removeMPRIS);
    connect(this, &QListWidget::itemClicked, this, [this](QListWidgetItem *it) {
        Q_EMIT this->selectionHasChanged(apis[it->text()]);
    });
}

int CurrentMedias::countMedias()
{
    return apis.keys().count();
}

QString CurrentMedias::firstMedia()
{
    return apis.values().first();
}

void CurrentMedias::addMPRIS(QString s)
{
    QListWidgetItem *it = new QListWidgetItem();

    QDBusInterface interfacing(s, MP2P, FDProp);
    QString name = QDBusReply<QString>(interfacing.call("Get", MP2O, "Identity")).value();
    it->setText(name);
    it->setIcon(QIcon::fromTheme(QDBusReply<QString>(interfacing.call("Get", MP2O, "DesktopEntry")).value()));

    apis[name] = s;

    addItem(it);
}

void CurrentMedias::removeMPRIS(QString s)
{
    int i = 0;
    while (i<QListWidget::count()) {
        if (apis[item(i)->text()] == s) {
            apis.remove(item(i)->text());
            delete takeItem(i);
            i--;
        }
        i++;
    }
}
