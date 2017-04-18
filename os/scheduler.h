#ifndef OS_SCHEDULER_H
#define OS_SCHEDULER_H

#include <exception>
#include <iostream>
#include <string>

#include <stdlib.h>
#include <stdint.h>

#include "define.h"
#include "yoroutine.h"

class Scheduler {
public:
    int capaity;
    char *stack;
    size_t stack_size;
    ucontext_t main;

    Scheduler(int s_size, int init_cap);

    ~Scheduler();

    void enlarge_yc_list();

    int get_cur_id() {
        return this->cur_id;
    }

    int get_size() {
        return this->size;
    }

private:
    int size;
    int cur_id;

    Yoroutine **yc_list;

};

static Scheduler scheduler = Scheduler(STACK_SIZE, INIT_CAPACITY);

#endif //OS_SCHEDULER_H
