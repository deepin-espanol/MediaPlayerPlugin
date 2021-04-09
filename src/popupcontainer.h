#ifndef APPLETCONTAINER_H
#define APPLETCONTAINER_H

#include "currentmedias.h"
#include "mediaplayerwidget.h"

#include <QLabel>

class PopupContainer : public QWidget
{
    Q_OBJECT
public:
    explicit PopupContainer(QWidget *parent = nullptr);
    void reset();

private:
    CurrentMedias medias;
    MediaPlayerWidget popup;
    QLabel label;
};

#endif // APPLETCONTAINER_H
