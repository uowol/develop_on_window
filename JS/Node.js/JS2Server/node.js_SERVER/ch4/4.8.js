// register middleware to router

const express = require('express');
let app = express();

const http = require('http');

let firstMiddleware = (req, res, next) => {
    console.log('first middleware');
    next();
};

// app.get('/', middleware1, middleware2, middleware3, ...)
app.get('/', firstMiddleware, (req, res, next) => {
    res.send('hello world 1');
});

// usage examples
// app.use('/admin', adminCheck, adminRouter)
// app.use('/', normalUserRouter)

app.get('/user', (req, res, next) => {
    res.send('hello world 2');
});

http.createServer(app).listen(3000, () => {
    console.log("server on 3000 port");
});