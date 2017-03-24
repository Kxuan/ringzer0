const fs = require("fs");
var HTMLParser = require('fast-html-parser');

var filename = process.argv[2];
if (process.argv[2] === undefined) {
    s = process.stdin;
} else {
    s = fs.createReadStream(process.argv[2]);
}

s.resume();
var content = "";
s.on("data", function (data) {
    content += data.toString();
});
s.on("end", function () {
    var root = HTMLParser.parse(content);
    var el = root.querySelector(".challenge-wrapper");

    console.log(el.structuredText);

});
