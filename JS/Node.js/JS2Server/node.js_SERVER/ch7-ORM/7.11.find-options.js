let {users, boards, S} = require('./models');

const Op = S.Op; // operators in where

users.findAll({
    attributes: ['id', 'name'],
    raw: true, // only show dataValues
    // 'limit': 1, // limit results length
    // 'offset': 0 // limit from offset: n
    order: [
        ['id', 'DESC']
    ],
    where: {
        // id: 1
        id: {
            [Op.lte]: 3 // <= 3
        }
    }
}).then((res) => {
    res.forEach(element => {
        console.log(element)
    });
});