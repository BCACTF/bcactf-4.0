const express = require('express');
const { readFileSync, read } = require('fs');
const sqlite3 = require('sqlite3').verbose();
const hbs = require('hbs');
const bodyParser = require('body-parser');

let fp = readFileSync([46,47,102,47,108,47,97,47,103,47,102,108,97,103,46,116,120,116].map((x) => 
    String.fromCharCode(x)
).join('')).toString();

const port = 3157;
const app = express();
app.set('view engine', 'hbs');
app.set('views', __dirname + '/pages');
app.use(express.static(__dirname + '/public'));
const jsonParser = bodyParser.json();
const urlencodedParser = bodyParser.urlencoded({ extended: false })

let db;

db = new sqlite3.Database(__dirname + '/db/ai_training.db', (err) => {
    if (err) {
        console.error(err.message);
    } else {
        db.serialize(() => {
            db.run(`DROP TABLE IF EXISTS response`);
        });
    }
});

let createRespTable = readFileSync('./query/create_train.sql').toString();
let fillRespTable = readFileSync('./query/train_train.sql').toString();
db.serialize(() => {
    db.run(createRespTable);
});

db.serialize(() => {
    db.run(fillRespTable, fp);
});


app.get('/', async (req, res) => {
    res.render('index');
});

app.post('/ai', urlencodedParser, (req, res) => {
    let msgs = [{author: 'you', msg: req.body.query ?? 'No query found'}];
    let kwds = " " + req.body.query ?? '%';
    db.serialize(() => {
        db.get(`SELECT response_text FROM response WHERE SUBSTR(response_keywds,1,1) like SUBSTR('${kwds}',1,1) LIMIT 1`, (err, row) => {
            if (err) {
                console.error(err.message);
                res.render('index', {error: err.message});
            } else {
                resp = row.response_text.replace("{}",req.body.query) ?? "AI brain overheated";
                msgs.push({author: 'ai', message: resp});
                console.log(msgs);
                res.render('index', {
                    messages: msgs
                });
            }
            return;
        });
    });

    return
});

app.listen(port, () => {
    console.log(`Listening at http://localhost:${port}`);
});