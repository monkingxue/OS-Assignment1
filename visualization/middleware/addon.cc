#include <node.h>
#include "wrapper.h"

using namespace v8;

void initAll(Handle<Object> exports) {
    Wrapper::Init(exports);
}

NODE_MODULE(addon, initAll);



