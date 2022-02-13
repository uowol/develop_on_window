let {users, boards} = require('./models');

users.findAll({
    include: [
        {
            model: boards
        }
    ],
    raw: false  // true: show all boards, false: return array of boards
}).then((res) => {
    res.forEach(element => {
        console.log(element)
    });
});