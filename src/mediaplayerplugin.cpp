#include "mediaplayerplugin.h"

#include "defs.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>

MediaPlayerPlugin::MediaPlayerPlugin(QObject *parent)
    : QObject(parent),
      m_tipsLabel(new QLabel(tr("Media Player"))),
      m_settings("deepin", NAME)
{
    pluginItem = new MediaApplet;
    m_applet = new PopupContainer;
}

const QString MediaPlayerPlugin::pluginName() const
{
    return NAME;
}

const QString MediaPlayerPlugin::pluginDisplayName() const
{
    return tr("Media Player");
}

void MediaPlayerPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
    if (pluginItem->enabled())
        m_proxyInter->itemAdded(this, pluginName());
}

void MediaPlayerPlugin::pluginStateSwitched()
{
    pluginItem->setEnabled(!pluginItem->enabled());
    if (pluginItem->enabled())
        m_proxyInter->itemAdded(this, pluginName());
    else
        m_proxyInter->itemRemoved(this, pluginName());
}

bool MediaPlayerPlugin::pluginIsDisable()
{
    return !pluginItem->enabled();
}

int MediaPlayerPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    const QString key = QString("pos_%1").arg(displayMode());
    return m_settings.value(key, 0).toInt();
}

void MediaPlayerPlugin::setSortKey(const QString &itemKey, const int order)
{
    Q_UNUSED(itemKey);
    const QString key = QString("pos_%1").arg(displayMode());
    m_settings.setValue(key, order);
}

QWidget *MediaPlayerPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return pluginItem;
}

QWidget *MediaPlayerPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_tipsLabel;
}

QWidget *MediaPlayerPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    if (m_applet != nullptr) {
        m_applet->reset();
    }
    return m_applet;
}

const QString MediaPlayerPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return "";
}

const QString MediaPlayerPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(1);

    // Primer elemento del menú
    QMap<QString, QVariant> mnuAbout;
    mnuAbout["itemId"] = "about";
    mnuAbout["itemText"] = tr("Acerca de");
    mnuAbout["isActive"] = true;
    items.push_back(mnuAbout);

    // Segundo elemento del menú
    QMap<QString, QVariant> mnuHelloWorld;
    mnuHelloWorld["itemId"] = "helloworld";
    mnuHelloWorld["itemText"] = tr("Hola mundo");
    mnuHelloWorld["isActive"] = true;
    items.push_back(mnuHelloWorld);

    // Tercer elemento del menú
    QMap<QString, QVariant> mnuAboutQt;
    mnuAboutQt["itemId"] = "aboutqt";
    mnuAboutQt["itemText"] = tr("Acerca de qt");
    mnuAboutQt["isActive"] = true;
    items.push_back(mnuAboutQt);

    // Encapsular los elementos del menú
    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    return QJsonDocument::fromVariant(menu).toJson();
}

void MediaPlayerPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(checked);

    if(menuId == "about") {
        about();
    } else if(menuId == "helloworld") {
        helloWorld();
    } else if(menuId == "aboutqt") {
        qApp->aboutQt();
    }
}

void MediaPlayerPlugin::about()
{
    QMessageBox aboutMB(QMessageBox::NoIcon, "Plugin básico para el dock",
                        "Aquí hay un ejemplo simple de un desarrollo de un plugin de dde-dock! \nAutor: Deepin en español");
    aboutMB.setIconPixmap(QPixmap(":/icons/Logo-Racoon.png"));
    aboutMB.exec();
}

void MediaPlayerPlugin::helloWorld()
{
    QMessageBox helloWorldMB(QMessageBox::Information, "Hola Mundo!", "Hola, Deepin. DDE Dock！");
    helloWorldMB.exec();
}

