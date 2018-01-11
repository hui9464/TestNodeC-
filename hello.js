// hello.js
const addon = require('./build/Release/addon');

console.log(addon.hello());
console.log(addon.test());

console.log(addon.test().arg5[0]+addon.test().arg5[1]);
// Prints: 'world'