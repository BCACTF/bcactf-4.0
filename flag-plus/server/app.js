const express = require('express');
const app = express();
const port = 48275;

app.get("/", (req, res) => res.sendFile(__dirname + "/views/index.html"));
app.get("/free.html", (req, res) => res.sendFile(__dirname + "/views/free.html"));
app.get("/flag.html", (req, res) => {
  if (req.headers.referer?.indexOf(req.headers.host + "/paid.html") > -1) {
    res.sendFile(__dirname + "/views/flag-good.html");
  } else {
    res.sendFile(__dirname + "/views/flag-bad.html");
  }
});
app.get("/403.html", (req, res) => res.status(403).send("403"));
app.get("/paid.html", (req, res) => res.redirect("/403.html"));

app.listen( port, () => {
  console.log(`App server listening on ${ port }. (Go to http://localhost:${ port })` );
} );