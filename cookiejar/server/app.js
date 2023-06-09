const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const session = require("express-session");
const cookieParser = require('cookie-parser');

app.set('view engine', 'ejs');

app.use(express.static(__dirname + '/public'));
app.use(cookieParser());

app.use(session({
    secret: "AWNjdnajkwnsdjknasjkdnjaksn",
    saveUninitialized: true,
    resave: true
}));

function createSession(req) {
    req.session.view = 1;
    req.session.orders = []
    req.session.badThing = ""
}

app.get('/', (req, res) => {
    if (!req.session.view) {
        createSession(req)
        res.cookie("name", "Qm9iIEJyb29rcw==")
    }
    

    res.render("index", {orders: req.session.orders, badThing:req.session.badThing})
});

app.get('/order', (req, res) => {
    try {
        let order = JSON.parse(req.cookies["order"])
        req.session.orders.push(order)
    }
    catch {
        console.log("ERROR")
    }
    res.redirect("/")
})

app.get('/takecookie', (req, res) => {
    try {
        if (req.cookies["name"] == "Sm9obiBKb2huc29ucw==" && req.cookies["role"] == "") {
            res.redirect("/success")
        }
    }
    catch {}
    res.redirect("/failed")
});

app.get('/accept/:id', (req, res) => {
    if (req.cookies["name"] == "Sm9obiBKb2huc29ucw==") {
        if (req.params.id < req.session.orders.length && req.params.id >= 0) {
            let order = req.session.orders[req.params.id];
            if (order.types.length == 2 && order.amounts.length == 2) {
                if (order.types.indexOf("Chocolate Chip") != -1 && order.types.indexOf("Oatmeal") != -1) {
                    res.render("cookie")
                } 
                else {
                    req.session.badThing = "Types did not follow order"
                }
            }
            else {
                req.session.badThing = "You did not order 2 things"
            }
        }
        else {
            req.session.badThing = "Invalid ID"
        }
    }
    else {
        req.session.badThing = "Only the owner can accept requests"
    }
    res.redirect("/")
})

server.listen(3000, () => {
  console.log('listening on *:3000');
});