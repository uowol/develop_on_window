let {users, boards} = require('./models');

console.log(users, boards);

// users.findAll({raw: true}).then(res => {
//     console.log(res);
//     return boards.findAll({raw: true});
// }).then(res => {
//     console.log(res);
// });
