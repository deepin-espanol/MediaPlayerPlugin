#include "popupcontainer.h"

#include <QHBoxLayout>

PopupContainer::PopupContainer(QWidget *parent) :
    QWidget(parent),
    medias(),
    popup(),
    label(tr("No media found."))
{
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(&label);
    lay->addWidget(&medias);
    lay->addWidget(&popup);
    lay->setMargin(0);

    connect(&medias, &CurrentMedias::selectionHasChanged, this, [this](QString s) {
        label.setVisible(false);
        medias.setVisible(false);
        popup.setVisible(true);
        popup.connectTo(s);
    });

    medias.setVisible(false);
    popup.setVisible(false);

    this->setLayout(lay);
}

void PopupContainer::reset()
{
    if (medias.countMedias() == 0) {
        label.setVisible(true);
        medias.setVisible(false);
        popup.setVisible(false);
    } else if (medias.countMedias() == 1) {
        label.setVisible(false);
        medias.setVisible(false);
        popup.setVisible(true);
        popup.connectTo(medias.firstMedia());
    } else {
        label.setVisible(false);
        medias.setVisible(true);
        popup.setVisible(false);
    }
}
