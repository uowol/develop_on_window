let {users, boards} = require('./models');

let data = [
    {
        name: '김찬우',
        age: 22
    },{
        name: '김수한무',
        age: 99
    }
];

users.bulkCreate(data).then((res) => {
    console.log("LOG: " + res);
});