const Sequelize = require('sequelize');

const db = 'boards';
const user = 'root';
const password = '';
const options = {
    host: '127.0.0.1',
    dialect: 'mysql'    // type what DB will be used
};

let sql = new Sequelize(db, user, password, options);

const users = sql.define('users', {
    id: {
        type: Sequelize.DataTypes.INTEGER(11),
        primaryKey: true,
        autoIncrement: true,
        allowNull: false
    },
    name: {
        type: Sequelize.DataTypes.STRING(255),
        allowNull: false
    },
    age: {
        type: Sequelize.DataTypes.INTEGER(11),
        defaultValue: 25
    }
}, {
    tableName: 'users', // real name in database
    freezeTableName: false, // if false, using first factor change tableName
    timestamps: false // define if sql creates 'createdAt / updatedAt'
});

users.findAll({raw: true}).then(res => {
    console.log(res)
})