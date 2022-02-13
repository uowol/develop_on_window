// complicated API

'use strict';

const express = require('express');
let app = express();

const http = require('http');

// without these, cannot read body data
// const bodyParser = require('body-parser'); 
// app.use(bodyParser.urlencoded({extended: true}))

app.get('/users/:id', (req, res, next) => {
    res.send('유저 정보 가져오기'); 
});

app.post('/users', (req, res, next) => {
    res.send("회원가입");
});

app.put('/users/:id', (req, res, next) => {
    res.send('유저 정보 수정');
});

app.delete('/users/:id', (req, res, next) => {
    res.send("회원탈퇴");
})

app.get('/boards', (req, res, next) => {
    res.send("게시글 가져오기");
});

app.post('/boards', (req, res, next) => {
    res.send("게시글 쓰기");
});

app.put('/boards/:id', (req, res, next) => {
    res.send('게시글 수정');
});

app.delete('/boards/:id', (req, res, next) => {
    res.send("게시글 삭제");
})


http.createServer(app).listen(3000, () => {
    console.log('server on : 3000 port');
});