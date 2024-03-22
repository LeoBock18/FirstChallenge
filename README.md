# GRADIENT METHOD FOR MINIMIZATION OF 2D FUCNTION

The code provides the gradient method for solving a multi-dimensional minimization problem with three different strategies for choosing the learning rate.

## ALPHA METHOD CHOICE
This choice is made at compile with a template function parametrized with an enumerator, whose value can be modified in the main.cpp file (line 20). Choose:
- 1 for exponential decay
- 2 for inverse decay
- 3 for Armijo rule

## PARAMETERS
The parameters are all stored in a struct with a default initialization, which can be modified with the 'grad_param.json' file

## FUNCTION
The function and its gradient are passed to the gradmet function with two function wrappers. They are defined as lambda functions inside the 'main.cpp' file, where they can be modified (I am aware this is not the most flexible choice, I struggled a lot with MuParserX and I did not managed to use it).

## MAKEFILE
The code can be compiled just by typing 'make', but the path for the 'json.hpp' template library has to be modified in the CPPFLAGS variable.

## OTHER REMARKS
I decided not to use the Eigen library, nor define classes of any type, and for this reason I had to implement some external function for vector operations (subtraction, multiplication by a scalar, euclidean norm computation). In order not to have overloading problems of any type, I used a namespace for all the functions I have implemented.