const fs = require('fs')
const express = require('express')
const multer = require('multer')


let upload = multer({
    storage: multer.diskStorage({
        destination: function (req, file, cb) {
            cb(null, './storage/');
        },
        filename: function (req, file, cb) {
            cb(null, file.originalname);
        }
    }),
})
let app = express();
app.use(express.urlencoded({extended: false}));
app.use(express.json());


app.get('/', (req, res) => {
    fs.readFile('./pages/index.html', 'utf8', (err, data) => {
        res.writeHead(200, {'Content-Type' : 'text/html'})
        res.end(data)
    })
})

app.get('/files', (req, res) => {
    let result = fs.readdirSync(__dirname + '/storage', 'utf8')
    res.send(result)
})

app.get('/files/:file', (req, res) => {
    let file = req.params.file
    fs.readFile(`./cache/datastore.json`, 'utf-8', (err, data) => {
        let datastore = JSON.parse(data);
        
        fs.readFile(`./storage/${file}`, 'utf-8', (err, data) => {
            if(!Object.keys(datastore).includes(file)) 
            datastore[file] = {
                scrollTop: 0,
                bookmarkId: null
            };
            res.set('Content-Type', 'text/json');
            res.send({
                data: data,
                scrollTop: datastore[file].scrollTop,
                bookmarkId: datastore[file].bookmarkId
            })
        })
    })
    
})

app.post('/uploadbookmark', (req, res) => {
    let {title, scrollTop, bookmarkId} = req.body;
    fs.readFile('./cache/datastore.json', 'utf-8', (err, data) => {
        let datastore = JSON.parse(data);
        if(!Object.keys(datastore).includes(title)) 
            datastore[title] = {
                scrollTop: scrollTop,
                bookmarkId: bookmarkId
            };
        else{
            datastore[title].scrollTop = scrollTop
            datastore[title].bookmarkId = bookmarkId
        }
        fs.writeFileSync('./cache/datastore.json', JSON.stringify(datastore, null, 4), 'utf-8');
        // res.set('Content-Type', 'text/json');
        res.end()
    })
})

app.post('/uploadfile', upload.single('file'), (req, res) => {
    console.log(req.body)
    console.log(req.file)
    res.status(204).redirect('/')
})

app.listen(3000, () => {
    console.log('server on 3000 port')
})