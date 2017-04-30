#include "wrapper.h"

void initAll(Handle<Object> exports) {
    Wrapper::Init(exports);
}

NODE_MODULE(addon, initAll);



