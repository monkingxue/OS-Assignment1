let addon = require("bindings")("addon");

addon.test(function (item) {
    console.log(item)
});