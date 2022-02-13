let {users, boards} = require('./models');

users.findAll({raw: true}).then(res => {
    console.log(res);
    return boards.findAll({raw: true});
}).then(res => {
    console.log(res);
});
