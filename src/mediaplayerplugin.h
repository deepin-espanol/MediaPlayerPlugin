#ifndef DDE_BASICDOCKPLUGIN_H
#define DDE_BASICDOCKPLUGIN_H

#include "mediaapplet.h"
#include "popupcontainer.h"

#include <dde-dock/pluginsiteminterface.h>
#include <QLabel>

class MediaPlayerPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "mediaplayer.json")
public:
    explicit MediaPlayerPlugin(QObject *parent = nullptr);

    const QString pluginName() const override;
    const QString pluginDisplayName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    void pluginStateSwitched() override;
    bool pluginIsAllowDisable() override { return true; }
    bool pluginIsDisable() override;

    int itemSortKey(const QString &itemKey) override;
    void setSortKey(const QString &itemKey, const int order) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;
    const QString itemContextMenu(const QString &itemKey) override;

    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;

private:
    QPointer<PopupContainer> m_applet;
    QPointer<QLabel> m_tipsLabel;
    QPointer<MediaApplet> pluginItem;
    QSettings m_settings;
    void about();
    void helloWorld();
};

#endif // DDE_BASICDOCKPLUGIN_H
