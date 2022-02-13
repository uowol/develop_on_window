let express = require('express');
let {Nuxt, Builder} = require('nuxt');

let config = require('../nuxt.config.js');

const app = express();

const nuxt = new Nuxt(config);

const builder = new Builder(nuxt);
builder.build();

app.use(nuxt.render);

let port = 3000;

app.listen(port, () => {
    console.log('server on : ' + port);
});