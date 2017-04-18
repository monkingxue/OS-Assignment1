#ifndef OS_YOROUTINE_H
#define OS_YOROUTINE_H

#include <stdint.h>
#include <stdlib.h>

#include "define.h"
#include "scheduler.h"

typedef void (*yc_fn)(void *arg);

class Yoroutine {
public:
    yc_fn func;
    void *arg;
    char *stack;
    int status;
    int id;

    Yoroutine(yc_fn func, void * arg);

    ~Yoroutine();

    int get_status();

    bool set_status();

private:
    ucontext_t ctx;
    Scheduler *scheduler;
    size_t stack_size;

    static void pause(int to_status);
    static int save_stack();

    void resume(int id);

    void yield() {pause(YOROUTINE_SUSPENDED);}

    void block() {pause(YOROUTINE_BLOCKED);}
};

#endif //OS_YOROUTINE_H
