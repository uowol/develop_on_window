const mysql = require('mysql');

let db = mysql.createConnection({
    host: '127.0.0.1',
    port: '3306',
    user: 'root',
    password: '',
    database: 'boards'
})

db.query('select *from users', (err, data) => {
    if(err) console.log('err 발생 : ' + err);
    else console.log(data);
})