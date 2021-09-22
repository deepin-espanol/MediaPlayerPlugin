#include "mediaplayerwidget.h"

#include "defs.h"

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDoubleSpinBox>

MediaPlayerWidget::MediaPlayerWidget(QWidget *parent)
    : QWidget(parent),
      m_mprisInter(nullptr)
{
    setFixedSize(500, 200);
    init();
}

MediaPlayerWidget::~MediaPlayerWidget()
{
    m_mprisMonitor->~DMPRISMonitor();
    m_mprisInter->~DBusMPRIS();

    m_titleScrollArea->~QScrollArea();
    m_title->~QLabel();
    m_picture->~QLabel();
    m_artist->~QLabel();
    m_maxPos->~QLabel();
    m_currPos->~QLabel();
    m_album->~QLabel();
    m_duration->~QLabel();
    m_currentDuration->~QLabel();

    m_prevBtn->~DButtonBoxButton();
    m_playBtn->~DButtonBoxButton();
    m_nextBtn->~DButtonBoxButton();
    m_forwardBtn->~DButtonBoxButton();
    m_backwardBtn->~DButtonBoxButton();

    musicSlider->~DSlider();
    rateBox->~QDoubleSpinBox();

    buttons->~DButtonBox();
}

bool MediaPlayerWidget::isWorking() const
{
    return m_mprisInter;
}

void MediaPlayerWidget::setPictureVisible(bool visible)
{
    m_pictureVisible = visible;
    m_picture->setVisible(visible);
}

void MediaPlayerWidget::setPictureSize(const QSize &size)
{
    m_picture->setFixedSize(size);
}

void MediaPlayerWidget::showEvent(QShowEvent *event)
{
    _q_onPlaybackStatusChanged();
    QWidget::showEvent(event);
}

DCORE_USE_NAMESPACE

void MediaPlayerWidget::init()
{
    m_mprisMonitor    = DSingleton<DMPRISMonitor>::instance();
    m_titleScrollArea = new QScrollArea(this);
    m_title           = new QLabel(this);
    m_picture         = new QLabel(this);
    m_artist          = new QLabel(this);
    m_currPos         = new QLabel(this);
    m_album           = new QLabel(this);
    m_maxPos          = new QLabel(this);
    m_artist          = new QLabel(this);
    m_duration        = new QLabel(this);
    m_currentDuration = new QLabel(this);
    musicSlider       = new DSlider;
    m_pictureVisible  = true;
    m_prevBtn         = new DButtonBoxButton("");
    m_playBtn         = new DButtonBoxButton("");
    m_nextBtn         = new DButtonBoxButton("");
    m_forwardBtn      = new DButtonBoxButton("");
    m_backwardBtn      = new DButtonBoxButton("");
    buttons           = new DButtonBox(this);
    rateBox           = new QDoubleSpinBox(this);
    buttons->setButtonList({m_prevBtn, m_backwardBtn, m_playBtn, m_forwardBtn, m_nextBtn}, true);

    m_prevBtn->setIcon(QIcon::fromTheme(":/assets/images/play_previous.svg"));
    m_prevBtn->setAccessibleName("MPRISControllerPrevFloatingButton");
    m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/play_start.svg"));
    m_playBtn->setAccessibleName("MPRISControllerPlayFloatingButton");
    m_nextBtn->setIcon(QIcon::fromTheme(":/assets/images/play_next.svg"));
    m_nextBtn->setAccessibleName("MPRISControllerNextFloatingButton");
    m_prevBtn->setBackgroundRole(DPalette::Button);
    m_playBtn->setBackgroundRole(DPalette::Button);
    m_nextBtn->setBackgroundRole(DPalette::Button);
    m_prevBtn->setAutoExclusive(true);
    m_playBtn->setAutoExclusive(true);
    m_nextBtn->setAutoExclusive(true);

    m_title->setAlignment(Qt::AlignCenter);
    m_title->setAccessibleName("MPRISControllerTitleLabel");
    m_picture->setFixedSize(200, 200);
    m_picture->setAccessibleName("MPRISControllerPictureLabel");
    m_prevBtn->setObjectName("PrevBtn");
    m_playBtn->setObjectName("PlayBtn");
    m_nextBtn->setObjectName("NextBtn");
    m_title->setFixedWidth(this->width() - m_picture->width());

    musicSlider->setMinimum(0);

    m_titleScrollArea->setObjectName("scrollarea");
    m_titleScrollArea->setWidgetResizable(true);
    m_titleScrollArea->setFocusPolicy(Qt::NoFocus);
    m_titleScrollArea->setFrameStyle(QFrame::NoFrame);
    m_titleScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_titleScrollArea->setContentsMargins(0, 0, 0, 0);
    m_titleScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_titleScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_titleScrollArea->setStyleSheet("background-color:transparent;");
    m_titleScrollArea->setAccessibleName("MPRISControllerScrollArea");
    m_titleScrollArea->viewport()->setAccessibleName("MPRISControllerScrollAreaViewPort");

    m_nextBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_right_normal.png"));
    m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_right_white.png"));
    m_prevBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_left_normal.png"));
    m_forwardBtn->setIcon(QIcon::fromTheme("media-seek-forward"));
    m_backwardBtn->setIcon(QIcon::fromTheme("media-seek-backward"));

    QVBoxLayout *controlLayout = new QVBoxLayout;
    controlLayout->addWidget(m_title);
    controlLayout->addWidget(m_artist);
    controlLayout->addWidget(m_album);

    QHBoxLayout *durationLayout = new QHBoxLayout;
    durationLayout->addWidget(m_currentDuration);
    durationLayout->addWidget(musicSlider);
    durationLayout->addWidget(m_duration);

    controlLayout->addLayout(durationLayout);
    controlLayout->addWidget(buttons);

    controlLayout->setContentsMargins(0, 5, 0, 0);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlLayout);
    centralLayout->setMargin(5);

    m_picture->setVisible(true);

    rateBox->setMaximum(3);
    rateBox->setMinimum(0.1);

    QVBoxLayout *imageLayout = new QVBoxLayout;
    imageLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding));
    imageLayout->addWidget(rateBox);
    imageLayout->setContentsMargins(5, 5, 5, 5);

    rateBox->setFixedHeight(35);
    buttons->setFixedHeight(35);

    m_picture->setLayout(imageLayout);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_picture);
    topLayout->addLayout(centralLayout);
    topLayout->setMargin(0);
    setLayout(topLayout);

    connect(m_prevBtn, SIGNAL(clicked()), this, SLOT(_q_onPrevClicked()));

    connect(m_playBtn, &DButtonBoxButton::clicked, this, [this] {
        if (m_clickedStatus)
            return;
        m_clickedStatus = true;
        QTimer::singleShot(100, this, SLOT(_q_onPlayClicked()));
    });

    connect(m_mprisInter, &DBusMPRIS::PositionChanged, this, [this](qlonglong val) {
        musicSlider->setValue((int)val);
        m_currentDuration->setText(QString::number((val/1024/60)));
    });

    connect(musicSlider, &DSlider::valueChanged, this, [this](int val) {
        m_mprisInter->SetPosition(QDBusObjectPath(m_mprisInter->path()), val);
    });

    connect(m_forwardBtn, &DButtonBoxButton::clicked, this, [this]() {
        m_mprisInter->Seek(200);
    });
    connect(m_backwardBtn, &DButtonBoxButton::clicked, this, [this]() {
        m_mprisInter->Seek(-200);
    });

    connect(m_mprisInter, &DBusMPRIS::MinimumRateChanged, rateBox, &QDoubleSpinBox::setMinimum);
    connect(m_mprisInter, &DBusMPRIS::MaximumRateChanged, rateBox, &QDoubleSpinBox::setMaximum);
    connect(rateBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [this](double val) {
        m_mprisInter->setRate(val);
    });

    connect(m_nextBtn, SIGNAL(clicked()), this, SLOT(_q_onNextClicked()));

    connect(m_mprisInter, &DBusMPRIS::CanGoNextChanged, m_nextBtn, &DButtonBoxButton::setEnabled);
    connect(m_mprisInter, &DBusMPRIS::CanGoPreviousChanged, m_prevBtn, &DButtonBoxButton::setEnabled);
    connect(m_mprisInter, &DBusMPRIS::CanPlayChanged, this, &MediaPlayerWidget::checkPlayPauseHandling);
    connect(m_mprisInter, &DBusMPRIS::CanPauseChanged, this, &MediaPlayerWidget::checkPlayPauseHandling);
    connect(m_mprisInter, &DBusMPRIS::CanSeekChanged, m_backwardBtn, &DButtonBoxButton::setEnabled);
    connect(m_mprisInter, &DBusMPRIS::CanSeekChanged, m_forwardBtn, &DButtonBoxButton::setEnabled);

    posReloader.setInterval(250);
    connect(&posReloader, &QTimer::timeout , this, &MediaPlayerWidget::updatePos);
    posReloader.start();

    m_mprisMonitor->init();
}

void MediaPlayerWidget::updatePos()
{
    if (isWorking()) {
        musicSlider->setValue((int)m_mprisInter->position());
    }
    posReloader.start();
}

void MediaPlayerWidget::_q_onPrevClicked()
{
    if (!m_mprisInter)
        return;

    m_mprisInter->Previous();
    m_prevBtn->setFocus();
}

void MediaPlayerWidget::_q_onPlayClicked()
{
    m_clickedStatus = false;
    if (!m_mprisInter)
        return;

    if (m_playStatus) {
        m_mprisInter->Pause();
    } else {
        m_mprisInter->Play();
    }

    m_playBtn->setFocus();
}

void MediaPlayerWidget::_q_onNextClicked()
{
    if (!m_mprisInter)
        return;

    m_mprisInter->Next();
    m_nextBtn->setFocus();
}

QImage blurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly = false)
{
    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
    int alpha = (radius < 1)  ? 16 : (radius > 17) ? 1 : tab[radius-1];

    QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    int r1 = rect.top();
    int r2 = rect.bottom();
    int c1 = rect.left();
    int c2 = rect.right();

    int bpl = result.bytesPerLine();
    int rgba[4];
    unsigned char* p;

    int i1 = 0;
    int i2 = 3;

    if (alphaOnly)
        i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r1) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += bpl;
        for (int j = r1; j < r2; j++, p += bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c1 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += 4;
        for (int j = c1; j < c2; j++, p += 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r2) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= bpl;
        for (int j = r1; j < r2; j++, p -= bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c2 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= 4;
        for (int j = c1; j < c2; j++, p -= 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    return result;
}

void MediaPlayerWidget::_q_onMetaDataChanged()
{
    if (!m_mprisInter)
        return;

    const QVariantMap &   meta        = m_mprisInter->metadata();
    const QString &       title       = meta.value("xesam:title").toString();
    const QString &       album       = meta["xesam:album"].toString();
    const QString &       artist      = meta.value("xesam:artist").toString();
    const QUrl &          pictureUrl  = meta.value("mpris:artUrl").toString();
    const QSize &         pictureSize = m_picture->size();
    QPixmap               picture;

    if (!pictureUrl.isValid() || pictureUrl.isEmpty()) {
        m_picture->setPixmap(QIcon::fromTheme("emblem-music-symbolic").pixmap(QSize(200, 200)));
    } else {
        picture = QPixmap(pictureUrl.toString());
        if (170 > picture.width() or 170 > picture.height()) {
            //Means it'll be pixelized, use blur to "jolify"
            picture = QPixmap::fromImage(blurred(picture.scaled(pictureSize, Qt::IgnoreAspectRatio).toImage(), QRect(0, 0, pictureSize.width(), pictureSize.height()), 2));
        } else if (picture.width() < 200 or picture.height() < 200) {
            //Means it is between 150 and 200 of W nor H. Not enough pixelized to blur it.
            picture = picture.scaled(pictureSize, Qt::IgnoreAspectRatio);
        }
        m_picture->setPixmap(picture);
    }

    m_album->setText(tr("Album: ") + (album.isEmpty() ? album : tr("Unknown album")));
    musicSlider->setMaximum(meta.value(("mpris:length")).toInt());
    m_artist->setText(tr("Artist: ") + (artist.isEmpty() ? artist : tr("Unknown artist")));
    m_duration->setText(QString::number((meta.value("mpris:length").toInt()/1024/60)));
    m_title->setText(tr("Title: ") + (title.isEmpty() ? title : tr("Unknown title")));
}

void MediaPlayerWidget::_q_onPlaybackStatusChanged()
{
    if (!m_mprisInter)
        return;

    const QString stat = m_mprisInter->playbackStatus();
#ifdef QT_DEBUG
    if (stat == "Playing") {
        m_playStatus = true;
        m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_right_white.png"));
    } else {
        m_playStatus = false;
        m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_left_white.png"));
    }
#else
    if (stat == "Playing") {
        m_playStatus = true;
        m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/play_pause.svg"));
    } else {
        m_playStatus = false;
        m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/play_start.svg"));
    }
#endif
}

void MediaPlayerWidget::_q_loadMPRISPath(const QString &path)
{
    const bool hasOld = m_mprisInter;
    m_lastPath = path;

    // save paths
    if (!m_mprisPaths.contains(path))
        m_mprisPaths.append(path);

    if (m_mprisInter)
        m_mprisInter->deleteLater();

    m_mprisInter = new DBusMPRIS(path, MP2P, QDBusConnection::sessionBus(), this);

    bool canControl = m_mprisInter->canControl();
    rateBox->setEnabled(canControl);
    buttons->setEnabled(canControl);

    if (canControl) {
        bool canSeek = m_mprisInter->canSeek();
        m_forwardBtn->setEnabled(canSeek);
        m_backwardBtn->setEnabled(canSeek);

        m_nextBtn->setEnabled(m_mprisInter->canGoNext());
        m_prevBtn->setEnabled(m_mprisInter->canGoPrevious());

        m_playBtn->setEnabled(m_mprisInter->canPlay() && m_mprisInter->canPause());
    }

    connect(m_mprisInter, SIGNAL(MetadataChanged(QVariantMap)), this, SLOT(_q_onMetaDataChanged()));
    connect(m_mprisInter, SIGNAL(PlaybackStatusChanged(QString)), this, SLOT(_q_onPlaybackStatusChanged()));
    connect(m_mprisInter, SIGNAL(CanControlChanged(bool)), this, SLOT(_q_onCanControlChanged(bool)));

    _q_onMetaDataChanged();
    _q_onPlaybackStatusChanged();

    if (hasOld)
        Q_EMIT mprisChanged();
    else
        Q_EMIT mprisAcquired();
}

void MediaPlayerWidget::connectTo(QString s)
{
    _q_loadMPRISPath(s);
}

void MediaPlayerWidget::_q_removeMPRISPath(const QString &path)
{
    m_mprisPaths.removeOne(path);

    if (m_lastPath != path)
        return;

    if (!m_mprisInter)
        return;

    if (!m_mprisPaths.isEmpty())
        return _q_loadMPRISPath(m_mprisPaths.last());

    m_mprisInter->deleteLater();
    m_mprisInter = nullptr;

    Q_EMIT mprisLosted();
}

void MediaPlayerWidget::_q_onCanControlChanged(bool canControl)
{
    rateBox->setEnabled(canControl);
    buttons->setEnabled(canControl);
}

void MediaPlayerWidget::checkPlayPauseHandling()
{
    bool play = m_mprisInter->canPlay();
    bool pause = m_mprisInter->canPause();
    m_playBtn->setEnabled(play && pause);
    if (play && !pause) {
        m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_right_white.png"));
    } else if (pause) {
        m_playBtn->setIcon(QIcon::fromTheme(":/assets/images/arrow_left_white.png"));
    }
}
