const Sequelize = require('sequelize');
const fs = require('fs');
const path = require('path');

const dbName = 'boards';
const user = 'root';
const password = '';
const options = {
    host: '127.0.0.1',
    dialect: 'mysql'    // type what DB will be used
};

let sequelize = new Sequelize(dbName, user, password, options);
let db = {};
fs.readdirSync(__dirname)
    .filter(file => (file.indexOf('.') !== 0) && (file !== 'index.js'))
    .forEach(file => {
        // let model = sequelize['import'](path.join(__dirname, file)); // deprecated
        let model = require(path.join(__dirname, file))(sequelize, Sequelize.DataTypes)
        db[model.name] = model;
    });
    
// define associations
Object.keys(db).forEach(modelName => {
    if("associate" in db[modelName]){
        db[modelName].associate(db);
    }
});

db.sql = sequelize;
db.S = Sequelize;

sequelize.sync(); // sync between model and database. if there's no table in db, make it!

// db.users.findAll({raw: true}).then(res => {
//     console.log(res)
// })

module.exports = db;
