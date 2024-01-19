#include "pptbutton.h"

PPTButton::PPTButton(QObject *parent) : QObject(parent)
{
    _fileDesc = open(DEVICE.toUtf8().data(), O_RDWR | O_NONBLOCK);
    if (_fileDesc > -1){
        QSocketNotifier* m_notifier = new QSocketNotifier(_fileDesc, QSocketNotifier::Read, this);
        connect(m_notifier, &QSocketNotifier::activated, this, &PPTButton::readButtonState);
    }else{
        qDebug() << "ERROR open:  " << _fileDesc;
    }
}

void PPTButton::readButtonState(int socket)
{
    unsigned char data[32];
    int bytes = read(_fileDesc, data, sizeof(data));
    if (bytes > 0){
        InputEvent keyInpStruct;
        memcpy(&keyInpStruct, data, sizeof(keyInpStruct));
        if (keyInpStruct.code == 60 ){
            emit togglePptState(keyInpStruct.value);
        }
    }
}
