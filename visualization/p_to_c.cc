#include "p_to_c.h"

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

    const unsigned long delay = 1000;
    srand((unsigned int) time(0));

    for(int i = 0; i < 5; i++)
        resource.push_back(random(range));

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local <Function> callback = Local<Function>::Cast(args[0]);

    Yoroutine *reader = new Yoroutine(read, nullptr);
    Yoroutine *writer = new Yoroutine(write, nullptr);

    while (writer->get_status() || reader->get_status()) {

        int rand_num = rand() % 10;
        if (rand_num < 5)
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

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void init(Handle <Object> exports) {
    NODE_SET_METHOD(exports, "test", test);
}

NODE_MODULE(test, init);