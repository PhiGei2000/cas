# CAS
## Overview
A simple computer algebra system similar to mathematica written in C++.
### Features
- [ ] Differential calculus
- [x] Store expressions into variables
- [ ] Equation solving
- [ ] ...

## Getting started
### Check the requirements
Requirements:
- CMake 3.20
- C++ 23
### Clone the repository
    git clone https://github.com/PhiGei2000/cas.git && cd ./cas
### Run CMake and build the project
    cmake --build ./build
### Run the application
    ./build/cas

## Commands
All commands have the form ``commandName[arg1,arg2,...]`` and must terminated by a semicolon. If no variables are needed, the parentheses are optional.

### Engine functions
| Command | Description | Example |
| --- | --- | --- |
| set[var, expr] | Assigns the expression expr to the specified variable for later use | ``set[x,12]`` or ``x=12``|
| get[var] | Gets the expression stored in the specified variable | ``get[x]`` or ``x`` |
| ans[] | Returns the result of the last stored calculation | |
| listVars[] | Lists the currently stored variables and their values | |
| exit[] | Shuts down the engine | |

### Differential calculus

| Command | Description | Example |
| --- | --- | --- |
| D[function, variable] | Calculates the derivative of the given function with respect to the given variable | ``D[2*x,x]`` gives ``2`` |
| Df[function] | Calculates the exterior differential of the given function | ``Df[2*x*y]`` gives ``2*y*dx+2*x*dy`` |

### Term manipulation and term matching

| Command | Description | Example |
| --- | --- | --- |
| simplify[expression] | Simplifies the given expression by using replace rules | ``simplify[0*x+2*1]`` gives ``2`` |
| match[expression, pattern] | Determines, if the given expression matches the pattern and lists the values of the variables in the pattern found in the expression | ``match[(a+b)^2,x^2]`` gives ``x=a+b`` |
| matchRecurse[expression, pattern] | Does the same thing like match but only recursive on the expression | ``matchRecurse[a+(b+c)^2,x^2]`` gives ``x=b+c`` |
| matchAll[expression, pattern] | Does the same thing like matchRecurse but gives all matches back | ``matchAll[a^2+(b+c)^2,x^2]`` gives ``x=a`` and ``x=b+c`` |
| substitute[expression, pattern, newValue] | Substitutes all occurences of the pattern with the new value. The variables in the new value are going to be replaced by the values of the variables found in the expression | ``substitute[(a+b)^2,(x+y)^2,x^2+2*x*y+y^2]`` gives ``a^2+2*a*b+b^2`` |

## Issues
Feel free to report issues to the [issue section](https://github.com/PhiGei2000/cas/issues)

## License
This code is licensed under the [GPL-3.0 license](https://github.com/PhiGei2000/cas/blob/master/LICENSE)