#include "yoroutine.h"

Yoroutine::Yoroutine(yc_fn func, void *arg) {
    Scheduler* root = Scheduler::getInstance();
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

Yoroutine::~Yoroutine() {
    free(this->stack);
    delete (this);
    _compress_yclist(this->id);
}

void Yoroutine::resume() {
    int id = this->id;
    ucontext_t ctx = this->ctx;

    if (id == DUMMY_YOROUTINE_ID) {
        errPrint("Could not resume a dummy yoroutine");
        return;
    }

    Yoroutine *cryc = scheduler->get_yc(id);
    if (cryc == nullptr) {
        errPrint("Could not resume a null yoroutine");
        return;
    }

    switch (status) {
        case YOROUTINE_READY: {
            getcontext(&ctx);
            ctx.uc_stack.ss_size = scheduler->stack_size;
            ctx.uc_stack.ss_sp = scheduler->stack;
            ctx.uc_link = &scheduler->main;
            status = YOROUTINE_RUNNING;
            scheduler->set_cur_id(id);
            uintptr_t arg_ptr = (uintptr_t) this;
            makecontext(
                    &ctx,
                    (void (*)(void))_wrap_fn,
                    2,
                    (uint32_t) arg_ptr,
                    (uint32_t) (arg_ptr >> 32)
            );
            swapcontext(&scheduler->main, &ctx);
            break;
        }

        case YOROUTINE_SUSPENDED: {
            memcpy(
                    scheduler->stack + STACK_SIZE - this->stack_size,
                    this->stack,
                    this->stack_size
            );
            this->status = YOROUTINE_RUNNING;
            scheduler->set_cur_id(this->id);
            swapcontext(&scheduler->main, &ctx);
            break;
        }

        default:
            break;
    }
}

void Yoroutine::_pause(int to_status) {

    if (!_save_stack()) {
        errPrint("Failed to save stack before pausing a yoroutine");
        return;
    }
    this->status = to_status;
    scheduler->set_cur_id(DUMMY_YOROUTINE_ID);
    swapcontext(&this->ctx, &scheduler->main);
}

void Yoroutine::_compress_yclist(int idx) {
    int size = scheduler->get_size();
    scheduler->get_yc(idx)->status = YOROUTINE_IDLE;

    if (size >= 1) {
        if (idx < size - 1) {
            scheduler->set_yc(idx, scheduler->get_yc(size - 1));
            scheduler->get_yc(idx)->id = idx;
        }
        scheduler->set_yc(size - 1, nullptr);
        scheduler->set_size(-1);
    } else {
        scheduler->push_yc(nullptr);
    }

}

void Yoroutine::_wrap_fn(uint32_t low_bits, uint32_t high_bits) {
    uintptr_t arg_ptr = (uintptr_t) low_bits | (uintptr_t) high_bits << 32;
    Yoroutine *cryc = (Yoroutine *) arg_ptr;
    cryc->func(cryc->arg);

    cryc->_compress_yclist(cryc->scheduler->get_cur_id());

    cryc->scheduler->set_cur_id(DUMMY_YOROUTINE_ID);

}

bool Yoroutine::_save_stack() {

    char dummy = 0;

    free(this->stack);
    this->stack_size = scheduler->stack + scheduler->stack_size - &dummy;
    try {
        this->stack = (char *) malloc(sizeof(char) * this->stack_size);
    } catch (std::exception &e) {
        errPrint("Failed to new space to save stack");
        return false;
    }
    memcpy(this->stack, &dummy, sizeof(char) * this->stack_size);

    return true;
}

int Yoroutine::get_status() {
    if (this->id < 0)
        return YOROUTINE_IDLE;

    return this->status;
}