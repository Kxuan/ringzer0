const fs = require("fs");
const DomParser = require('dom-parser');
var parser = new DomParser();

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
    var dom = parser.parseFromString(content);
    var el = dom.getElementsByClassName("challenge-wrapper");
    console.log(el[0].textContent);

});
