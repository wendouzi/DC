#ifndef CANCEL_FLAG_H
#define CANCEL_FLAG_H

class cancelFlag {
private:
    cancelFlag();
private:
    static cancelFlag * cf;
    volatile bool m_bcancelFlag;
public:
    static cancelFlag * getInstance() ;

    bool getCancelFlag() ;
    ~cancelFlag();
    void setCancelFlag(bool s) ;
};

#endif
