#include "yoroutine.h"

Yoroutine::Yoroutine(yc_fn func, void *arg) {
    int new_id = scheduler->assign_size();

    this->scheduler = scheduler;
    this->stack = nullptr;
    this->stack_size = 0;
    this->func = func;
    this->arg = arg;
    this->status = YOROUTINE_READY;

    this->id = new_id;
    scheduler->push_yc(new_id, this);
}