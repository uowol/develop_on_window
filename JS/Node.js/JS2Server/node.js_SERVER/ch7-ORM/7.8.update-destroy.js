let {users, boards} = require('./models');

// users.update({
//     name: 'pjt'
// }, {
//     where: { id: 2 }
// }).then((res) => {
//     console.log("LOG: " + res);
// });

users.destroy({
    where: { id: [6, 7] }
}).then((res) => {
    console.log("LOG: " + res);
});