// < template string >

// let a = 'hello'
// let b = 'world'
// let result = `${a} ${b}`
// console.log(result) // hello world


// < destructuring assignment >

// let c = [1, 2, 3]
// let [one, two, three] = c
// console.log(one, two, three) // 1 2 3
// let [one, ...two] = c
// console.log(one, two) // 1 [2, 3]


// < Array.prototype.filter >

// let a = [10, 11, 20, 21, 30, 31]
// let new_a = a.filter((v, idx, arr) => v % 10 == 0 ? true : false)
// console.log(new_a) // 10, 20, 30


// < Object.hasOwnProperty() >

// let a = {a:109, b: 203}
// console.log(a.hasOwnProperty('a')) // true


// < Spread Operator > 

// const prt = (x, y, z) => console.log(x, y, z)
// let a = [1, 2, 3]
// console.log(...a) // 1 2 3


// < Class >

// class Square{
//     constructor(height, width){
//         this.height = height
//         this.width = width
//     }

//     get area(){
//         return this.calcArea()
//     }

//     calcArea() {
//         return this.height*this.width
//     }
// }

// let a = new Square(3, 4)
// let b = new Square(5, 6)

// console.log(a.area) // 12
// console.log(b.area) // 30


// < Module >

