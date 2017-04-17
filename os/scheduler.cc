#include "scheduler.h"

Scheduler::Scheduler(int s_size, int init_cap) {
    size_t stack_bytes_size = sizeof(char) * s_size;

    this->capaity = init_cap;
    this->size = 0;
    this->stack_size = stack_bytes_size;

    try {
        this->stack = (char *) malloc(stack_bytes_size);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    memset(this->stack, 0, stack_bytes_size);

    this->cur_id = DUMMY_YOROUTINE_ID;
}

Scheduler::~Scheduler() {
    for(Yoroutine * yc: this->yc_list) {
        free(yc->stack);
        free(yc);
    }

    free(this->stack);
}