#include "scheduler.h"

struct Args {
    int n;
};

void foo(void *ud) {
    Args *arg = (Args *) ud;
    int start = arg->n;
    int i;
    int id = root->get_cur_id();
    for (i = 0; i < 5; i++) {
        printf("yoroutine %d : %d\n", id, start + i);
        root->get_yc(id)->yield();
    }
}

void test() {
    Args arg1 = {0};
    Args arg2 = {100};

    Yoroutine *yo1 = new Yoroutine(foo, &arg1);
    Yoroutine *yo2 = new Yoroutine(foo, &arg2);
    printf("main start\n");

    while (yo1->get_status() && yo2->get_status()) {
        yo1->resume();
        yo2->resume();
    }
    printf("main end\n");
}

int main(int argc, char *argv[]) {
    test();
}