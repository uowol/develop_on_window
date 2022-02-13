// response with variable forms

'use strict'

const express = require('express');
let app = express();
const http = require('http');

// without these, cannot read body data
// const bodyParser = require('body-parser'); 
// app.use(bodyParser.urlencoded({extended: true}))

app.get('/send', (req, res, next) => {
    // res.send('hello world!!!'); // send data in text form
    res.send('<h1> Hello World </h1>'); // send data in html form
});

app.get('/download', (req, res, next) => {
    res.download('./test.txt');
});

app.get('/redirect', (req, res, next) => {
    res.redirect('/send');
});

app.get('/json', (req, res, next) => {
    res.json({msg: "success", code: 0});
});

app.get('/modify', (req, res, next) => {
    res.status(201).json({msg: "success"}); // modify status code and send json data(chaining)
});

http.createServer(app).listen(3000, () => {
    console.log('server on : 3000 port');
});