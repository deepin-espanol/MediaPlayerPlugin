#ifndef DDE_BASICDOCKPOPUP_H
#define DDE_BASICDOCKPOPUP_H

#include "mpris/dmprismonitor.h"
#include "mpris/dbusmpris.h"

#include <QWidget>
#include <QLabel>
#include <QSettings>
#include <QScrollArea>
#include <DSlider>
#include <DButtonBox>
#include <dtickeffect.h>
#include <QTimer>
#include <DIconButton>

class QDoubleSpinBox;

DWIDGET_USE_NAMESPACE

class MediaPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaPlayerWidget(QWidget *parent = nullptr);
    ~MediaPlayerWidget();

    void init();
    bool isWorking() const;


    bool m_playStatus = false;
    bool m_clickedStatus = false;
    bool m_pictureVisible;

    QString     m_lastPath;
    QStringList m_mprisPaths;

Q_SIGNALS:
    void mprisAcquired() const;
    void mprisChanged() const;
    void mprisLosted() const;

public Q_SLOTS:
    void setPictureVisible(bool visible);
    void setPictureSize(const QSize &size);
    void _q_onPrevClicked();
    void _q_onPlayClicked();
    void _q_onNextClicked();
    void _q_onMetaDataChanged();
    void _q_onPlaybackStatusChanged();
    void _q_loadMPRISPath(const QString &path);
    void _q_removeMPRISPath(const QString &path);
    void _q_onCanControlChanged(bool canControl);

    void checkPlayPauseHandling();
    void connectTo(QString name);
    void updatePos();

protected:
    void showEvent(QShowEvent *event);
    QTimer posReloader;

    DMPRISMonitor *m_mprisMonitor;
    DBusMPRIS *    m_mprisInter;

    QScrollArea *m_titleScrollArea;
    QLabel *     m_title;
    QLabel *     m_picture;
    QLabel *     m_artist;
    QLabel *     m_maxPos;
    QLabel *     m_currPos;
    QLabel *     m_album;
    QLabel *     m_duration;
    QLabel *     m_currentDuration;

    DButtonBoxButton *m_prevBtn;
    DButtonBoxButton *m_playBtn;
    DButtonBoxButton *m_nextBtn;
    DButtonBoxButton *m_forwardBtn;
    DButtonBoxButton *m_backwardBtn;

    DSlider *musicSlider;
    QDoubleSpinBox *rateBox;

    DButtonBox *buttons;
};

#endif // DDE_BASICDOCKPOPUP_H
