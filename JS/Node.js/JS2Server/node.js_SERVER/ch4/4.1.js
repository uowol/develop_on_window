// use express for express routing(*) more intuitive
// routing: executing logic with URL and methods 

const express = require('express');
let app = express();

const http = require('http');

app.get('/', (req, res, next) => {
    res.send('hello world!!!');
});

http.createServer(app).listen(3000, () => {
    console.log('server on : 3000 port')
})