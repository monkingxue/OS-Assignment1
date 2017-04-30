#ifndef VISUALIZATION_P_TO_C_H
#define VISUALIZATION_P_TO_C_H

#include <list>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

#include <node.h>
#include <v8.h>

#include "../os/yoroutine.h"

using namespace v8;

Scheduler *root = Scheduler::getInstance();

int random(int max, int min = 0) {
    return min + rand() % (max - min);
}

void safe_resume(Yoroutine *cryc) {
    if (cryc->get_status())
        cryc->resume();
}

const unsigned int maxLen = 15;
const unsigned int range = 500;

std::list<int> resource;
std::list<int>::iterator itor;

#endif //VISUALIZATION_P_TO_C_H
