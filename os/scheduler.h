#ifndef OS_SCHEDULER_H
#define OS_SCHEDULER_H

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

    static Scheduler *getInstance();

    ~Scheduler();

    void enlarge_yc_list();

    int get_cur_id() { return this->cur_id; }

    void set_cur_id(int id) { this->cur_id = id; }

    int get_size() { return this->size; }

    void set_size(int num) { this->size += num; }

    int assign_size();

    void push_yc(Yoroutine *yc);

    void set_yc(int pos, Yoroutine *yc);

    Yoroutine *get_yc(int id) { return this->yc_list[id]; }

private:
    int size;
    int cur_id;

    Yoroutine **yc_list;

    Scheduler(int s_size, int init_cap);

    static Scheduler *root;
};

#endif //OS_SCHEDULER_H
