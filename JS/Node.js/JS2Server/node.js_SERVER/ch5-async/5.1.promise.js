const fs = require('fs');

const _p = () => {
    return new Promise((resolve, reject) => {
        fs.readFile('./test.txt', (err, data) => {
            if(err) reject(err);
            resolve(data.toString());
        });
    });
};

_p().then((res) => {
    console.log(1);
    console.log(res);
    return _p();
}).then((res) => {
    console.log(2);
    console.log(res);
    return _p();
}).then((res) => {
    console.log(3);
    console.log(res);
    return _p();
}).catch(err => {
    console.log(err)
});