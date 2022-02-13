// manage middlewares with variables

const express = require('express');
let app = express();

const http = require('http');

let firstMiddleware = (req, res, next) => {
    console.log('first middleware');
    next();
};
let secondMiddleware = (req, res, next) => {
    console.log('second middleware');
    next();
};

app.use(firstMiddleware)
app.use(secondMiddleware)

app.get('/', (req, res, next) => {
    res.send('hello world');
});

http.createServer(app).listen(3000, () => {
    console.log("server on 3000 port");
});