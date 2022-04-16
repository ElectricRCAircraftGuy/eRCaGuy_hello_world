/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Demonstrate creating a javascript function and running it in Chrome, displaying an alert popup box
with the result.

To run this in Chrome, see the readme in "eRCaGuy_hello_world/javascript/README.md".

*/

function multiply(a, b) 
{
    return a * b;
}

var a = 1.4108;
var b = 3.7654;
var result = multiply(a, b);
alert('The result of ' + a + ' x ' + b + ' = ' + result.toFixed(4));
