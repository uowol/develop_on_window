const http = require('http')
const fs = require('fs')

http.createServer((req, res) => {
    let {url} = req
    fs.readFile('../../vue.js_CSR' + url + '.html', (err, data) => {
        console.log(err)
        if(!err){
            res.writeHead(200, {'Content-Type': 'text/html'})
            res.end(data)
            return
        }else if(err && err['errno'] === -4058){
            res.writeHead(404, {'Content-Type': 'text/plain'})
            res.end('404 Not Found!!!')
            return
        }
        res.writeHead(500)
        res.end('server error')    
    })
    
}).listen(3000, () => {
    console.log('server on 3000 port')
})