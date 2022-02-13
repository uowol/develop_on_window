const fs = require('fs')

fs.readFile('./test.txt', (err, data) => {
    if(!err){
        console.log('test.txt 파일 읽기 성공')
        console.log(data)
        console.log(data.toString())
        return
    }
    console.log(err)
})

fs.readFile('../../vue.js_CSR/1.1.html', (err, data) => {
    if(!err){
        console.log('1.1.html 파일 읽기 성공')
        console.log(data)
        console.log(data.toString())
        return
    }
    console.log(err)
})