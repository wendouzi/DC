#ifndef CCLOG_H
#define CCLOG_H


#include <stdio.h>
#include <stdlib.h>


class CCLog
{
    enum DLogType
    {
        Normal = 0,
        Warning,
        Error,
        SuperError
    };
public:
    void static DLog(const char * msg)
    {
        printf("%s\n",msg);
    }
    void static DLog(DLogType dt, const char * msg)
    {
        DLog(msg);
    }
};
#endif // CCLOG_H
