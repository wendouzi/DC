#include "cancel_flag.h"
#include <stddef.h>
#include <QDebug>
cancelFlag * cancelFlag::cf = NULL;
cancelFlag::cancelFlag() {
    m_bcancelFlag = false;
}
cancelFlag * cancelFlag::getInstance() {
    if(cf == NULL) {
        cf = new cancelFlag();
        return cf;
    }
    else {
        return cf;
    }
}

bool cancelFlag::getCancelFlag() {
        return m_bcancelFlag;
}
void cancelFlag::setCancelFlag(bool s) {
    if(m_bcancelFlag != s) {
        m_bcancelFlag = s;
    }
}

cancelFlag::~cancelFlag() {
    m_bcancelFlag = false;
    qDebug("cancelFlag::~cancelFlag()");
}
