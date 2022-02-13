// manage errors using middlewares

const express = require('express');
let app = express();

const http = require('http');

// 각종 미들웨어 등록
const logger = require('morgan');   // show clients' request logs: 200-green 404-yellow 500-red

// 각종 라우터 등록
app.use(logger('dev'));

app.get('/:id', (req, res, next) => {
    let id = req.params.id;
    if(id == 1){
        next('error 발생');
    }else{
        res.send('hello world: ' + id);
    }
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