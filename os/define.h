#ifndef OS_DEFINE_H_
#define OS_DEFINE_H_

// contants for yoroutines
#define STACK_SIZE (1024 * 1024)
#define INIT_CAPACITY 16

#define YOROUTINE_IDLE 0
#define YOROUTINE_READY 1
#define YOROUTINE_RUNNING 2
#define YOROUTINE_SUSPENDED 3
#define YOROUTINE_BLOCKED 4

#define DUMMY_YOROUTINE_ID -1

#endif

