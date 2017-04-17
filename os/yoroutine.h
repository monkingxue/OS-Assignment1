#ifndef OS_YOROUTINE_H
#define OS_YOROUTINE_H

#include <sys/ucontext.h>
#include <stdint.h>

#include "define.h"
#include "scheduler.h"

typedef void (*yc_fn)(Scheduler *, void *ud);

class Yoroutine {

};

#endif //OS_YOROUTINE_H
