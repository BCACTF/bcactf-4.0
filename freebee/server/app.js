const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);

app.use(express.static(__dirname + '/public'));

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/src/index.html');
});

app.get("/data", (req, res) => {
  res.send("This is a test")
});

server.listen(3000, () => {
  console.log('listening on *:3000');
});