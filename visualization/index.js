let addon = require("bindings")("addon");
console.log(addon);

// function foo(item) {
//     for(let i = 0; i< 5; i++) {
//         console.log(item + i);
//         JSYoroutine.yield();
//     }
// }
//
// let yoroutine_1 = new addon.JSYoroutine(foo, 10);
// let yoroutine_2 = new addon.JSYoroutine(foo, 100);
