let {users, boards} = require('./models');

users.findAll({
    'raw': true // only show dataValues
}).then((res) => {
    res.forEach(element => {
        console.log(element)
    });
});