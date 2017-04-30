# OS-Assignment1

**Yoroutine** 是一个在 CPP 上的 **协程**（coroutine）实现，其中`os`文件夹内是 Yoroutine 的实现代码，而`visualization`文件夹中是使用 Yoroutine 实现的一个 **读者-写者模型**，其中可视化是由 **JavaScript** 实现，使用 `node-gyp` 作为middle-layer，把 CPP 代码编译成可供 JS 调用的第三方 library。

**TIPS**：**由于项目使用的 uncontext.h 的头文件兼容性问题，该项目只能在 Linux 下运行，在 Windows 和 MacOS 上都会出现无法运行的情况**

## 使用方式

进入`visualization`文件夹，在该文件下打开 `terminal`， 输入

```bash
$ npm install
```

待依赖安装完成以后，再输入

```bash
$ npm run build
```

在浏览器中打开文件夹中的 `index.html`, 即可看到相应的效果

## 开发初衷

**ES7** 中引入了 `await/async` 机制来实现协程，而在 Go/Erlang/Elixir/C#/Python 等主流语言中都有协程的相关实现。对于这种特殊的流程控制方式，我很好奇：协程的背后是什么？为什么他被称为“用户态线程”？他和线程的区别在哪里？单线程上的协程实现的目的是什么？带着这些问题，我决定要实现一个 coroutine。

## 数据结构

**Scheduler**：

```c++
class Scheduler {
public:
    int capaity;			//调度器容量
    char *stack;			//协程栈
    size_t stack_size;		//栈大小
    ucontext_t main;		//调度器上下文
	
  	//单例模式的实现
    static Scheduler *getInstance();

    ~Scheduler();

    void enlarge_yc_list();

    int get_cur_id() { return this->cur_id; }

    void set_cur_id(int id) { this->cur_id = id; }

    int get_size() { return this->size; }

    void set_size(int num) { this->size += num; }

    int assign_size();

    void push_yc(Yoroutine *yc);

    void set_yc(int pos, Yoroutine *yc);

    Yoroutine *get_yc(int id) { return this->yc_list[id]; }

private:
    int size;				//协程数目
    int cur_id;				//当前协程的ID

    Yoroutine **yc_list;	//协程存储表

    Scheduler(int s_size, int init_cap);
	
    static Scheduler *root;	//调度器单例实体
};
```

**Yoroutine**：

```c++
class Yoroutine {
public:
    yc_fn func;				//协程上的执行函数
    void *arg;				//协程函数的调用参数
    char *stack;			//协程的调用栈，用于上下文切换
    int status;				//协程的状态
    int id;					//协程的ID

    Yoroutine(yc_fn func, void *arg);

    ~Yoroutine();

    int get_status();

    void resume();

    void yield() { _pause(YOROUTINE_SUSPENDED); }

    void block() { _pause(YOROUTINE_BLOCKED); }

private:
    ucontext_t ctx;			//协程的上下文
    Scheduler *scheduler;	//调度器
    size_t stack_size;		//协程的栈大小

    void _pause(int to_status);

    bool _save_stack();

    void _compress_yclist(int idx);

    static void _wrap_fn(uint32_t low_bits, uint32_t high_bits);
};
```

## 项目的缺陷

1. 协程的实现不够完善，目前只能算能用状态
2. 代码整体耦合度略高
3. 没有统一的错误处理机制
4. 目前代码无法实现跨平台运行
5. 还未对协程进行多线程化，对于性能的提升主要集中在 I/O 上

## 项目中的坑

1. `uncontext.h` 这个 library 有很严重的兼容性问题（这是一个 **POSIX** 的 **C library**），但是在 **MacOS** 中并没有被完全废弃，导致函数行为出现异常，却很难被发现。
2. 由于 **JavaScript** 和 **CPP** 在语言层面上存在巨大差异，所以在进行上下文切换的过程中出现了大量的**未定义行为**，为了消除这些行为，我不得不写了很多转化代码。
3. 为了兼顾开发体验和可测试性，我不得不在 **Ubuntu** 和 **MacOS** 之间进行不停地切换，期间使用 **Git** 进行代码的管理和迁移，无形中加大开发的工作量。

## 总结

这个项目整体的难度不太大，但是还是花了比较多的时间在做前期的准备和 debug 上，主要的原因就是👆说到的那些“坑”。当然这个项目做完还是有点遗憾，因为时间限制，上下文的切换是调用 library 而不是手动写，希望之后可以从更深的层面去实现一个协程。