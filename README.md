# OS-Assignment1

**Yoroutine** 是一个在 CPP 上的 **协程**（coroutine）实现，其中`os`文件夹内是 Yoroutine 的实现代码，而`visualization`文件夹中是使用 Yoroutine 实现的一个 **读者-写者模型**，其中可视化是由 **JavaScript** 实现，使用 `node-gyp` 作为middle-layer，把 CPP 代码编译成可供 JS 调用的第三方 library。

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

**ES2017** 中引入了 `await/async` 机制来实现协程，而在 Go/Erlang/Elixir/C#/Python 等主流语言中都有相关的实现，对于这种特殊的流程控制方式