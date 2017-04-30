//
// Created by 薛英琛 on 2017/4/19.
//

#ifndef OS_TEST_H
#define OS_TEST_H

#include <stdio.h>
#include "../yoroutine.h"

struct Args {
    int n;
};

void safe_resume(Yoroutine *cryc) {
    if (cryc->get_status())
        cryc->resume();
}

Scheduler *root = Scheduler::getInstance();

#endif //OS_TEST_H
