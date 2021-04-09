#ifndef CURRENTMEDIAS_H
#define CURRENTMEDIAS_H

#include "mpris/dmprismonitor.h"

#include <QMap>
#include <QListWidget>

class CurrentMedias : public QListWidget
{
    Q_OBJECT
public:
    explicit CurrentMedias(QWidget *p = nullptr);
    int countMedias();

    DMPRISMonitor *monitor;
    QString firstMedia();

Q_SIGNALS:
    void selectionHasChanged(QString name);

public Q_SLOTS:
    void addMPRIS(QString s);
    void removeMPRIS(QString s);

private:
    QStringList MPRISList;
    QMap<QString, QString> apis;
};

#endif // CURRENTMEDIAS_H
