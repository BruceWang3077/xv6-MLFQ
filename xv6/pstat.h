#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
    int pid;
    int priority;
    int tick;
};

#endif // _PSTAT_H_