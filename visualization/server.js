let http = require("http");
let addon = require("bindings")("addon");

http.createServer((req, res) => {
  if (req.url === "/data") {
    res.writeHead(200, {
      "Content-Type": "text/event-stream",
      "Cache-Control": "no-cathe",
      "Connection": "keep-alive",
      "Access-Control-Allow-Origin": "*"
    });

    addon.test((item) => {
      res.write(`data: ${item}\n\n`)
    });
  }
}).listen(3030);
