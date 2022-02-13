const fs = require('fs');

const _p = (val) => {
    return new Promise((resolve, reject) => {
        fs.readFile('./test.txt', (err, data) => {
            if(err) reject(err);
            resolve(`${val} : ${data.toString()}`);
        });
    });
};

(async function (){
    try{
        let data1 = await _p(1);
        let data2 = await _p(2);
        let data3 = await _p(3);    
        console.log(data1, data2, data3);
    }catch(e){
        console.log("err")
        console.log(e)
    }
})();

const newMetaPromise = async () => {    // work like the Promise() : like returning the resolve data
    return 'new meta';
};

newMetaPromise().then(res => console.log(res));