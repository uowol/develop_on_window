// use request factors and body data

'use strict'

const express = require('express');
let app = express();

const http = require('http');

// without these, cannot read body data
const bodyParser = require('body-parser'); 
app.use(bodyParser.urlencoded({extended: true}))

app.get('/users/:id', (req, res, next) => {
    let { params, query } = req;
    console.log(params, query);
    res.send('hello world!!!');
});

app.post('/', (req, res, next) => {
    let body = req.body;
    console.log(body);
    res.send('/ POST 요청');
});

http.createServer(app).listen(3000, () => {
    console.log('server on : 3000 port');
});