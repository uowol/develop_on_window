const http = require('http')
const fs = require('fs')

http.createServer((req, res) => {
    fs.readFile('../../vue.js_CSR/1.1.html', (err, data) => {
        if(!err){
            res.writeHead(200, {'Content-Type': 'text/html'})
            res.end(data)
            return
        }
        res.writeHead(500)
        res.end('server error')
    })
    
}).listen(3000, () => {
    console.log('server on 3000 port')
})