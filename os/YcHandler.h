#ifndef OS_YCHANDLER_H
#define OS_YCHANDLER_H

#include "define.h"


class YcHandler {
public:
    YcHandler() {}

    ~YcHandler() {}

    static void resume(int idx);

    static void yield(int idx) { _pause(YOROUTINE_SUSPENDED, idx); }

    static void block(int idx) { _pause(YOROUTINE_BLOCKED, idx); }

private:
    static void _pause(int to_status, int idx);

    static bool _save_stack(int);

    static void _compress_yclist(int);

    static void _wrap_fn(uint32_t low_bits, uint32_t high_bits);
};


#endif //OS_YCHANDLER_H
