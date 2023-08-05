/*
Constants.h; The std lib replacement

As you know, you can't simply use `printf` in your OS
You need to write your own `printf` function

Here I provide all the types I need to.
The one I'm missing is `size_t` which I need to track down the correct typedef for.s

*/

// Types & Classes

// Bool is a datatype representing a True or False statment, a 1 or a 0
#define bool _Bool

// Constants

// true and false keywords. Like bool, these need to be defined.
const int true = 1;
const int false = 0;
