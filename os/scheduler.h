#ifndef OS_SCHEDULER_H
#define OS_SCHEDULER_H

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <sys/ucontext.h>
#include <stdlib.h>
#include <stdint.h>

#include "define.h"
#include "yoroutine.h"

class Scheduler {
public:
    int capaity;
    char *stack;
    size_t stack_size;

    Scheduler(int s_size, int init_cap);

    ~Scheduler();

    int get_cur_id() {
        return this->cur_id;
    }

    int get_size() {
        return this->size;
    }

private:
    int size;
    int cur_id;
    ucontext_t ctx;
    std::vector<Yoroutine*> yc_list;
};

#endif //OS_SCHEDULER_H
