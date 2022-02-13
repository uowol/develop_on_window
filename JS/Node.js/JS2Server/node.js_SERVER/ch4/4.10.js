// register middlewares

const express = require('express');
let app = express();


const http = require('http');


const logger = require('morgan');   // show clients' request logs: 200-green 404-yellow 500-red
const bodyParser = require('body-parser'); // for parsing data in body
const cookieParser = require('cookie-parser'); // cookies in header to JSON


app.use(logger('dev'));
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json({limit: 5000000})); // in Node.js, there is a 100KB limit on body data. 
app.use(cookieParser());


app.use('/', (req, res, next) => {
    let values = Object.values(req.body)
    let _res = ! (values == false) ? req.body : 'hello world';
    res.send(_res);
});

app.use((req, res, next) => {   // 등록한 라우터에 일치하는 method와 url이 있었다면 next가 없으므로 404가 실행되지 않음.
    console.log('404');
    res.status(404).send("<h1>404 Not Found</h1>");
});

app.use((err, req, res, next) => {
    console.log(err);
    res.status(500).send(err);
});

http.createServer(app).listen(3000, () => {
    console.log("server on 3000 port");
});