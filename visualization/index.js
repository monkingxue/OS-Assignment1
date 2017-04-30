let addon = require("bindings")("addon");

addon.test(function (arr) {
    console.log(arr.length);
})
