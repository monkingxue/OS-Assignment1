#include "yoroutine.h"

Yoroutine::Yoroutine(yc_fn func, void *arg) {
    int new_id = root->assign_size();

    this->scheduler = root;
    this->stack = nullptr;
    this->stack_size = 0;
    this->func = func;
    this->arg = arg;
    this->status = YOROUTINE_READY;

    this->id = new_id;
    scheduler->push_yc(this);
}

void Yoroutine::resume() {
    int id = this->id;
    ucontext_t ctx = this->ctx;

    if (id == DUMMY_YOROUTINE_ID) {
        errPrint("Could not resume a dummy yoroutine");
        return;
    }

    Yoroutine *cryc = this->scheduler->get_yc(id);
    if (cryc == nullptr) {
        errPrint(" Could not resume a null yoroutine");
        return;
    }

    switch (this->status) {
        case YOROUTINE_READY:
            getcontext(&ctx);
            ctx.uc_stack.ss_size = this->scheduler->stack_size;
            ctx.uc_stack.ss_sp = this->scheduler->stack;
            ctx.uc_link = &this->scheduler->main;
            this->status = YOROUTINE_RUNNING;
            this->scheduler->set_cur_id(id);
            uintptr_t arg_ptr = (uintptr_t) this;
            makecontext(
                    &ctx,
                    (void (*)(void)) _wrap_fn,
                    2,
                    (uint32_t) arg_ptr,
                    (uint32_t) (arg_ptr >> 32)
            );
            swapcontext(&this->scheduler->main, &ctx);
            break;

        case YOROUTINE_SUSPENDED:

            break;
        default:
            break;
    }
}

void Yoroutine::_pause(int to_status) {

}

void Yoroutine::_wrap_fn(uint32_t low_bits, uint32_t high_bits) {

}