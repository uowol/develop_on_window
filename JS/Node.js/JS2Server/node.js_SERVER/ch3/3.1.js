const http = require('http')

http.createServer(function(req, res){
    res.writeHead(200)
    res.end('hello world')
}).listen(3000, function(){
    console.log('server on: 3000port')
})