let addon = require("bindings")("addon");
console.log(addon);

function foo(item) {
  for (let i = 0; i < 5; i++) {
    console.log(item + i);
    Wrapper.yield();
  }
}

let yoroutine_1 = new addon.Wrapper(foo, 10);
let yoroutine_2 = new addon.Wrapper(foo, 100);

console.log("start");

while(yoroutine_1.getStatus() && yoroutine_2.getStatus()) {
  yoroutine_1.resume();
  yoroutine_2.resume();
}

console.log("end");
