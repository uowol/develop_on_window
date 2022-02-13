const http = require('http')

http.createServer((req, res) => {
    let {url, method, headers} = req
    
    // res.statusCode = 200 // choice!
    res.writeHead(200)

    res.end('hello')
}).listen(3000, () => {
    console.log('server on 3000 port')
})