let {users, boards} = require('./models');

let name = '장영환';
let age = 22;

users.findOrCreate({
    where: {name: name},
    defaults: {
        name: name,
        age: age    
    }
}).then(([user, created]) => {
    console.log("LOG: " + user);
    console.log("LOG: " + created);
});