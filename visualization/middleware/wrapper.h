#ifndef VISUALIZATION_WRAPPER_H
#define VISUALIZATION_WRAPPER_H

#include "cpp2js.h"
#include "../../os/yoroutine.h"

class Args {
public:
    double num;
    Args(double _num):num(_num){}
    ~Args(){}
};

class Wrapper : public node::ObjectWrap {
public:
    static void Init(Handle <Object> exports);

private:
    explicit Wrapper(yc_fn func, Args * args);

    ~Wrapper();

    static void New(const jsArgs args);

    static void Get_Status(const jsArgs args);

    static void Resume(const jsArgs args);

    static void Yield(const jsArgs args);

    static Persistent <Function> constructor;

    Yoroutine * cyr;

};

#endif //VISUALIZATION_WRAPPER_H
