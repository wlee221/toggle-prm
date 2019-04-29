# Toggle PRM
**Author**: William Lee  
**Class**: Comp 781

## Introduction
This repository contains implementation of toggle PRM and its usage for solving 2d holonomic problems given in png files. It requires a single library: [libpng](http://www.libpng.org/pub/png/libpng.html).

### Structure
This repository is divided into following directories:

* `toggle-prm/`: contains c++ source file for 2d holonomic planning.
    * Also contains shell files to submit benchmark request to a slurm based cluster.
* `toggle-prm/classes`: contains class header files used to implement Toggle PRM.
* `toggle-prm/algorithm`: contains TogglePRM and PRM implementation. 
* `segment-intersection/test_data`: contains inputs and configuration data. 
    * prob.png is the image of the workspace, where white is free space and others are obstacle space.
    * prob.cfg contains start and goal state coordinates.

### Compilation and Execution
#### Compilation
C++17 Compiler is required to compile the source files. For most commercial compilers, you need to add `-std=c++17` flag.  
  

#### Execution 
Executable takes the following flags: 
* `f`: prefix of the input file. (e.g. test_data/narrow_05).
* `n`: number of configurations sampled each iteration.
* `k`: k-nearest neighbor search for each node.
* `m`: maximum number of witness points each iteration.
* `N`: number of times to run the algorithm (intended for benchmarking purposes)

#### Example
For example, 
```
g++ holonomic_2d_planning.cpp -std=c++17 -o holonomic_2d_planning 
./holonomic_2d_planning -f test_data/redblue_200.txt -n 20 -k 5 -m 40 -N 100
```
compiles with g++ and runs `holonomic_2d_planning.cpp` on input `test_data/narrow` with parameters `n = 20`, `k = 5`, `m = 40` 100 times.

#### Output
Program outputs solve time, number of nodes, and roadmap balance per iteration on each row.
