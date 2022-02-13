let {users, boards} = require('./models');

users.findAndCountAll({raw: true}).then((res) => {
    console.log(res)
});