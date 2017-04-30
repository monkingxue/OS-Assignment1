#include "wrapper.h"

Persistent <Function> Wrapper::constructor;
Scheduler *root = Scheduler::getInstance();

Wrapper::Wrapper(yc_fn func, Args *args) {
    this->cyr = new Yoroutine(func, args);
}

Wrapper::~Wrapper() {}

void Wrapper::Init(Handle <Object> exports) {
    Isolate *isolate = Isolate::GetCurrent();

    Local <FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "Wrapper"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "getStatus", Get_Status);
    NODE_SET_PROTOTYPE_METHOD(tpl, "resume", Resume);
    NODE_SET_PROTOTYPE_METHOD(tpl, "yield", Yield);

    constructor.Reset(isolate, tpl->GetFunction());
    exports->Set(String::NewFromUtf8(isolate, "Wrapper"),
                 tpl->GetFunction());
}

void Wrapper::New(const jsArgs args) {

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    if (args.IsConstructCall()) {
        if (!args[0]->IsFunction() || !args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong type of arguments!")));
            return;
        }

        Local <Function> cb = Local<Function>::Cast(args[0]);

        Args *_args = new Args(Local<Number>::Cast(args[1])->NumberValue());

        yc_fn _func = [cb, isolate](void *ud) {
            Local <Value> argv[1] = {Number::New(isolate, ((Args *) ud)->num)};
            cb->Call(isolate->GetCurrentContext()->Global(), 1, argv);
        };

        Wrapper *wrapper = new Wrapper(_func, _args);

        wrapper->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    } else {
        const int argc = 2;
        Local <Value> argv[argc] = {args[0], args[1]};

        Local <Function> cons = Local<Function>::New(isolate, constructor);
        args.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

void Wrapper::Get_Status(const jsArgs args) {

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Wrapper *wp = ObjectWrap::Unwrap<Wrapper>(args.Holder());

    args.GetReturnValue().Set(Number::New(isolate, wp->cyr->get_status()));
}

void Wrapper::Resume(const jsArgs args) {

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Wrapper *wp = ObjectWrap::Unwrap<Wrapper>(args.Holder());
    printf("ok");
    if (wp->cyr->get_status())
        wp->cyr->resume();
}

void Wrapper::Yield(const jsArgs args) {

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    YIELD;
}

