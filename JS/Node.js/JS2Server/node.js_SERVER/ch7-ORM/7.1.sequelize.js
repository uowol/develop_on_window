// why we are using ORM for manage DB,
// we can call database by using methods, not query.
// ⚠ BUT when definition of DB changed, we have to change models that be made with tables.

const Sequelize = require('sequelize');

const db = 'boards';
const user = 'root';
const password = '';
const options = {
    host: '127.0.0.1',
    dialect: 'mysql'    // type what DB will be used
};

let sequelize = new Sequelize(db, user, password, options);

// BEFORE,
// const mysql = require('mysql');
// let db = mysql.createConnection({
//     host: '127.0.0.1',
//     port: '3306',
//     user: 'root',
//     password: '',
//     database: 'boards'
// })

