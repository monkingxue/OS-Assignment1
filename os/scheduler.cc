#include "scheduler.h"

Scheduler *Scheduler::root;

Scheduler *Scheduler::getInstance() {
    if (root == nullptr) {
        root = new Scheduler(STACK_SIZE, INIT_CAPACITY);
    }
    return root;
}


Scheduler::Scheduler(int s_size, int init_cap) {
    size_t stack_bytes_size = sizeof(char) * s_size;
    size_t yclist_bytes_size = sizeof(Yoroutine *) * init_cap;

    this->capaity = init_cap;
    this->size = 0;
    this->stack_size = stack_bytes_size;

    try {
        this->stack = (char *) malloc(stack_bytes_size);
    } catch (std::exception &e) {
        throw e;
    }
    memset(this->stack, 0, stack_bytes_size);

    try {
        this->yc_list = (Yoroutine **) malloc(yclist_bytes_size);
    } catch (std::exception e) {
        throw e;
    }
    memset(this->yc_list, 0, yclist_bytes_size);

    this->cur_id = DUMMY_YOROUTINE_ID;
}

Scheduler::~Scheduler() {
    for (int i = 0; i < this->size; i++) {
        Yoroutine *yc = this->yc_list[i];
        if (yc != nullptr) {
            free(yc->stack);
            yc->stack = nullptr;
            delete yc;
        }
    }

    free(this->stack);
}

void Scheduler::enlarge_yc_list() {
    size_t yclist_bytes_size = sizeof(Yoroutine *) * (this->capaity << 1);
    try {
        this->yc_list = (Yoroutine **) realloc(yc_list, yclist_bytes_size);
    } catch (std::exception &e) {
        throw e;
    }
    memset(this->yc_list + this->capaity, 0, yclist_bytes_size / 2);

    this->capaity *= 2;
}

int Scheduler::assign_size() {
    int new_id = get_size();
    set_size(1);
    return new_id;
}

void Scheduler::push_yc(Yoroutine *yc) {
    if (this->size == this->capaity) {
        try {
            this->enlarge_yc_list();
        } catch (std::exception &e) {
            throw e;
        }
    }

    this->yc_list[yc->id] = yc;
}

void Scheduler::set_yc(int pos, Yoroutine *yc) {
    if (pos < 0 && pos >= this->capaity)
        return;
    this->yc_list[pos] = yc;
}