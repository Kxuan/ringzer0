const fs = require("fs");
var HTMLParser = require('fast-html-parser');

var filename = process.argv[2];
if (filename === undefined) {
    s = process.stdin;
} else {
    s = fs.createReadStream(filename);
}

s.resume();
var content = "";
s.on("data", function (data) {
    content += data.toString();
});
s.on("end", function () {
    var root = HTMLParser.parse(content);
    var el = root.querySelector(".challenge-wrapper");
    process.stdout.end(el.structuredText, () => {
        process.exit(0);
    });
});
