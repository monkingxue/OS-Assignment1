#include "p_to_c.h"

void write_front(void * arg) {
    while (1) {
        if (resource.size() <= maxLen) {
            resource.push_back(random(range));
        }
        YIELD;
    }
}

void write_back(void * arg) {
    while (1) {
        if (resource.size() <= maxLen) {
            resource.push_front(random(range));
        }
        YIELD;
    }
}

void read_front(void *arg) {
    while (1) {
        if (!resource.empty()) {
            resource.pop_front();
        }
        YIELD;
    }
}

void read_back(void *arg) {
    while (1) {
        if (!resource.empty()) {
            resource.pop_back();
        }
        YIELD;
    }
}

void test(const FunctionCallbackInfo <Value> &args) {

    const unsigned long delay = 1500;
    srand((unsigned int) time(0));

    for(int i = 0; i < 10; i++)
        resource.push_back(random(range));

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local <Function> callback = Local<Function>::Cast(args[0]);

    Yoroutine *reader1 = new Yoroutine(read_front, nullptr);
    Yoroutine *reader2 = new Yoroutine(read_back, nullptr);

    Yoroutine *writer1 = new Yoroutine(write_front, nullptr);
    Yoroutine *writer2 = new Yoroutine(write_back, nullptr);

    while (1) {

        int rand_num = rand() % 4;
        switch(rand_num) {
            case 0: safe_resume(writer1);break;
            case 1: safe_resume(writer2);break;
            case 2: safe_resume(reader1);break;
            case 3: safe_resume(reader2);break;
        }

        Local <Value> argv[1] = {[=]() {
            Local <Array> result = Array::New(isolate);
            itor = resource.begin();
            for (unsigned long i = 0; i < resource.size(); i++) {
                result->Set(i, Number::New(isolate, *itor++));
            }
            return result;
        }()};

        callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void init(Handle <Object> exports) {
    NODE_SET_METHOD(exports, "test", test);
}

NODE_MODULE(test, init);