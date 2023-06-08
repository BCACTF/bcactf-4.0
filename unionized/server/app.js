const express = require('express');
const sqlite3 = require('sqlite3').verbose()
const app = express();
const port = 3000;

app.set("views", __dirname + "/views");
app.set("view engine", "ejs");
app.use(express.static(__dirname + '/public'));

app.use( express.urlencoded({ extended: false }) );

// data for tables
const schoolnames = ["Bergen County Academies", "Bergen Tech", "Ridgefield Park High School", "Teaneck High School", "Wyckoff High School", "Moonachie High"];

function createDB() {

  // create in-memory database
  const db = new sqlite3.Database(':memory:')
  
  db.serialize(() => {
    // create tables
    db.run('CREATE TABLE school_data(name TEXT)')
    db.run('CREATE TABLE mystery(unkn0wn TEXT)')
  
    // insert data into tables
    const stmt = db.prepare('INSERT INTO school_data (name) VALUES (?)')
    const hiddentable = db.prepare('INSERT INTO mystery (unkn0wn) VALUES (?)')
  
    for (let i = 0; i < 6; i++) {
      stmt.run(`${schoolnames[i]}`)
    }
    const flag = 'bcactf{1_L0v3_sQl_UN10n_QU3r13S}'
    hiddentable.run(`${flag}`)
  
    stmt.finalize()
    hiddentable.finalize()
  })
  return db;
}


app.get('/', (req, res) => {
  const db = createDB();
  const get_all_query = `SELECT name FROM school_data`;
  db.all(get_all_query, [], (error, result) => {
    if (error) { res.status(500).send(error); }
    res.render("index", {results: result});
  });
  db.close();
});

app.post('/', (req, res) => {
  const db = createDB();
  const search_query = `SELECT name FROM school_data WHERE name LIKE '%${req.body.keyword}%'`;
  db.all(search_query,[],(error, result) => {
    if (error) {
      res.redirect('/');
    }
    else {
      res.render("index", {results: result});
    }
  });
  db.close();
} );

app.listen(port, () => {
  console.log(`Listening at http://localhost:${port}`);
});
