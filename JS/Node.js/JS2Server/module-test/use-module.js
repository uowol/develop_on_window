// ES5

const a = require('./')
const b = require('./index.js')

let area1 = a.area(10)
let area2 = b.area(10)

console.log(area1) // 314.1592653589793
console.log(area2) // 314.1592653589793


// ES6 not Yet

// import { area } from '.'
// import { area as _area } from './index.mjs'

// // let area1 = area(10)
// let area2 = _area(10)

// // console.log(area1) // 314.1592653589793
// console.log(area2) // 314.1592653589793
