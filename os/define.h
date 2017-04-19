#ifndef OS_DEFINE_H_
#define OS_DEFINE_H_

#include <setjmp.h>
#include <cstring>
#include <stdint.h>

#if __APPLE__ && __MACH__

#ifdef __cplusplus

extern "C" {
#include <sys/ucontext.h>
int getcontext(ucontext_t *);
int setcontext(const ucontext_t *);
void makecontext(ucontext_t *, void (*)(), int, ...);
int swapcontext(ucontext_t *, const ucontext_t *);
};

#endif


#else
extern "C" {
#include <ucontext.h>
}
#endif

// constants for yoroutines
#define STACK_SIZE (1024 * 1024)
#define INIT_CAPACITY 16

#define YOROUTINE_IDLE 0
#define YOROUTINE_READY 1
#define YOROUTINE_RUNNING 2
#define YOROUTINE_SUSPENDED 3
#define YOROUTINE_BLOCKED 4

#define DUMMY_YOROUTINE_ID -1

class Scheduler;
class Yoroutine;

#endif

