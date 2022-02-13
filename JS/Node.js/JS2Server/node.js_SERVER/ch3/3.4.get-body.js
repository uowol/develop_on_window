const http = require('http')

http.createServer((req, res) => {
    let {url, method, headers} = req
    let body = {}
    req.on('data', (data) => {
        console.log(data)
        console.log(data.toString())
        data.toString().split('&').map(item => {
            let [key, value] = item.split('=')
            body[key] = value
        })
    }).on('end', () => {
        console.log(body)
    }).on('error', (err) => console.log(err))
    res.writeHead(200)
    res.end('hello')
}).listen(3000, () => {
    console.log('server on 3000 port')
})