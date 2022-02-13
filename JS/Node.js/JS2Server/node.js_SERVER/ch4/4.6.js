// add middleware working on every requests

const express = require('express');
let app = express();

const http = require('http');

app.use((req, res, next) => {
    console.log('first middleware');
    next();
});

app.get('/', (req, res, next) => {
    res.send('hello world');
});

http.createServer(app).listen(3000, () => {
    console.log("server on 3000 port")
})