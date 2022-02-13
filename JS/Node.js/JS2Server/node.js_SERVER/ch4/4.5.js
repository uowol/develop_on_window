// complicated API - use Router: manage APIs with same end-point

'use strict';

const express = require('express');
let app = express();

const http = require('http');

const users = require('./users.js');
const boards = require('./boards.js');

app.use('/users', users);   // app.use('/', module): /request가 들어오면 module을 실행하라.
app.use('/boards', boards);

http.createServer(app).listen(3000, () => {
    console.log('server on 3000 port')
});