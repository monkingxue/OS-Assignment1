#ifndef OS_P_TO_C_H
#define OS_P_TO_C_H

#include <vector>
#include <stdlib.h>
#include <time.h>

#include "test.h"

using namespace std;

vector<int> resource;

int random(int max, int min = 0) {
    return min + rand() % (max - min);
}

void write(void *) {
    srand((unsigned int) time(0));

    for (int x = 0; x < 3; x++) {
        int num = random(9, 1);
        for (int y = 0; y < num; y++) {
            int result = random(300);
            resource.push_back(result);
            printf("product a number is %d\n", result);
        }
        YIELD;
    }
}

void read(void *arg) {
    Args *num = (Args *) arg;
    while (1) {
        if (!resource.empty()) {
            printf("custom%d the number %d\n", num->n, resource.back());
            resource.pop_back();
            YIELD;
        } else break;
    }
}

void test() {
    Args one = {1};
    Args two = {2};
    Yoroutine *reader1 = new Yoroutine(read, &one);
    Yoroutine *reader2 = new Yoroutine(read, &two);
    Yoroutine *writer = new Yoroutine(write, nullptr);
    printf("start!\n");
    while (reader1->get_status() || writer->get_status()) {
        safe_resume(writer);
        safe_resume(reader1);
        safe_resume(reader2);
    }
    printf("end\n");
}

#endif //OS_P_TO_C_H
