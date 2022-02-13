const http = require('http')

http.createServer((req, res) => {
    let {url, method, headers} = req
    
    res.writeHead(200, {'Content-Type': 'text/plain'})
    // res.statusCode = 200 // choice!
    // res.setHeader({'Content-Type': 'text/plain'})

    res.end('hello')
}).listen(3000, () => {
    console.log('server on 3000 port')
})