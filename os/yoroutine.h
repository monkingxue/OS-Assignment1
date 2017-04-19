#ifndef OS_YOROUTINE_H
#define OS_YOROUTINE_H

#include <stdint.h>
#include <stdlib.h>

#include "define.h"
#include "scheduler.h"
#include "tool.h"

typedef void (*yc_fn)(void *arg);

class Yoroutine {
public:
    yc_fn func;
    void *arg;
    char *stack;
    int status;
    int id;

    Yoroutine(yc_fn func, void *arg);

    ~Yoroutine();

    int get_status();

    void resume();

    void yield() { _pause(YOROUTINE_SUSPENDED); }

    void block() { _pause(YOROUTINE_BLOCKED); }

private:
    ucontext_t ctx;
    Scheduler *scheduler;
    size_t stack_size;

    void _pause(int to_status);

    bool _save_stack();

    void _compress_yclist(int idx);

    void _wrap_fn(uint32_t low_bits, uint32_t high_bits);

};

#endif //OS_YOROUTINE_H
