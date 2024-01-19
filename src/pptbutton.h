#ifndef PPTBUTTON_H
#define PPTBUTTON_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <QSocketNotifier>

struct InputEvent {
     struct timeval time;
     unsigned short type;
     unsigned short code;
     unsigned int value;
 };

class PPTButton: public QObject
{
    Q_OBJECT
public:
    explicit PPTButton(QObject *parent = nullptr);

public slots:
    void readButtonState(int socket);

signals:
    void togglePptState(const int state);

private:
    const QString DEVICE = "/dev/input/event1";
    int _fileDesc = -1;
};

#endif // PPTBUTTON_H
