const http = require('http');
const express = require('express');
let app = express();

const mysql = require('mysql');
let db = mysql.createConnection({
    host: '127.0.0.1',
    port: '3306',
    user: 'root',
    password: '',
    database: 'boards'
});

app.get('/users', (req, res) => {
    let sql = 'select *from users';
    db.query(sql, (err, data) => {
        res.json(data);
    });
});

app.get('/boards', (req, res) => {
    let sql = 'select *from boards';
    db.query(sql, (err, data) => {
        res.json(data);
    });
});

http.createServer(app).listen(3000, () => {
    console.log('server on : port 3000');
});

