const http = require('http')

http.createServer((req, res) => {
    let {url, method, headers} = req
    let body = {}

    req.on('data', (data) => {
        data.toString().split('&').map(item => {
            let [key, value] = item.split('=')
            body[key] = value
        })
    }).on('end', () => {
        for(let i=0; i< 10; i++) console.log(i)
        if(method === 'POST'){
            res.writeHead(200)
            if(url === '/user'){
                console.log('tt')
                res.end('/user 정보추가')
            }else if(url === '/board'){
                res.end('/board 게시글추가')    
            }else if(url === '/cloth'){
                res.end('/cloth 옷 추가')    
            }        
        }else{
            res.writeHead(404)
            res.end('Page Not Found!')
        }
    }).on('error', (err) => {
        res.writeHead(500)
        console.log('Server Error!')
    })

}).listen(3000, () => {
    console.log('server on 3000 port')
})