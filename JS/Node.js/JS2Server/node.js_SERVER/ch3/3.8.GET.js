const http = require('http')

http.createServer((req, res) => {
    let {url, method, headers} = req

    if(method === 'GET'){
        res.writeHead(200)
        if(url === '/users'){
            res.end('/users 접속')
        }else if(url === '/boards'){
            res.end('/boards 접속')    
        }else if(url === '/clothes'){
            res.end('/clothes 접속')    
        }
    }

    res.writeHead(404)
    res.end('Page Not Found!')
}).listen(3000, () => {
    console.log('server on 3000 port')
})