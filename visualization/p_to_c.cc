#include <vector>
#include <stdlib.h>
#include <time.h>
#include <node.h>
#include <v8.h>

#include "../os/yoroutine.h"

using namespace v8;

struct Args {
    int n;
};

Scheduler *root = Scheduler::getInstance();

static std::vector<double> resource;

int random(int max, int min = 0) {
    return min + rand() % (max - min);
}

void safe_resume(Yoroutine *cryc) {
    if (cryc->get_status())
        cryc->resume();
}


void write(void *) {

    for (int x = 0; x < 3; x++) {
        int num = random(9, 1);
        for (int y = 0; y < num; y++) {
            int result = random(300);
            resource.push_back(result);
        }
        YIELD;
    }
}

void read(void *arg) {
    while (1) {
        if (!resource.empty()) {
            resource.pop_back();
            YIELD;
        } else break;
    }
}

void test(const FunctionCallbackInfo <Value> &args) {
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local <Function> callback = Local<Function>::Cast(args[0]);

    Yoroutine *reader = new Yoroutine(read, nullptr);
    Yoroutine *writer = new Yoroutine(write, nullptr);

    srand((unsigned int) time(0));

    while (writer->get_status() || reader->get_status()) {
        int rand_num = rand() % 10;
        if (rand_num <= 4)
            safe_resume(writer);
        else
            safe_resume(reader);

        Local <Value> argv[1] = {[=]() {
            Local <Array> result = Array::New(isolate);
            for (unsigned long i = 0; i < resource.size(); i++) {
                result->Set(i, Number::New(isolate, resource[i]));
            }
            return result;
        }()};

        callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);
    }
}

void init(Handle <Object> exports) {
    NODE_SET_METHOD(exports, "test", test);
}

NODE_MODULE(test, init);