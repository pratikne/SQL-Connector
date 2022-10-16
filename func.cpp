#include "common_header.h"

char *get_time_stamp()
{
    char stamp[12];
    struct timeval tv;
    static char _gtime[20];
    gettimeofday(&tv, NULL);
    time_t temp = tv.tv_sec;
    strftime(stamp, 20, "%p %I.%M.%S", localtime(&temp));
    //strftime(stamp, 20, "%p %I.%M.%S", localtime(&tv.tv_sec));
    sprintf(_gtime, "%s.%06ld", stamp, tv.tv_usec);
    return _gtime;
}