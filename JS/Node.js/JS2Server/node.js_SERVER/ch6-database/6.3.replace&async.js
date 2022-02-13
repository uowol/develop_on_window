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

const userFindById = id => new Promise((resolve, reject) => {
    let sql = 'SELECT *FROM users WHERE id=?';
    db.query(sql, [id], (err, data) => {
        if(err) reject(err);
        resolve(data);
    });
});

app.get('/users', async (req, res) => {
    let userId = req.query.id;
    try{
        let data = await userFindById(userId);
        res.json(data);    
    }catch(e){
        console.log(e);
        res.status(500).json({message: 'error 발생'});
    }

});

http.createServer(app).listen(3000, () => {
    console.log('server on : port 3000');
});

