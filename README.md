# How to run
1. Create a file ending in .cpp
2. `#include "nn.h"` somewhere in the global scope
3. Perform the right function calls
4. Compile with g++ or clang and run the executable

# How it works

With the included `main.cpp` file, I used the XOR problem as an example. Big thanks to the youtube channel [The Coding Train](https://www.youtube.com/@TheCodingTrain) for his video series on the topic. 

### The Matrix library
It starts with the matrix library. In this header file, contains method to do complex matrix math. It includes normal methods and static methods for the most common operations to do to a matrix such as add, subtract, multiply, and divide. It also contains methods for transposing a matrix and a complex map function. 

The map function takes a function as a parameter and applies that function to every element of a matrix. This was the most complex part and it introduced me to using lambda functions. Combining the lambda functions with the `functional` standard library, I was able to achieve what I wanted for the map function. Someday I plan to refactor the function so I would not have to include the standard library.

### The Neural Network library





