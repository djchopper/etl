# C++ implementation of Approximate String Matching using Suffix Trees 

Thesis Project from the Advanced Algorithms & Parallel Programming course at Politecnico di Milano

## Scope
This project is aimed at implementing the suffix tree for approximate string matching.
It is implemented using the McCreight algorithm.
http://libeccio.di.unisa.it/TdP/suffix.pdf
Pseudocode available in docs.

## Build
Go to the root of the project and create a 'build' directory:
`mkdir build`

Go to the build directory:
`cd build`

Generate a build system in the current directory:
`cmake ..`

Build target 'aapp':
`cmake --build .`

## Run
Once built, go to the root of the project and launch the executable with a parameter:
`./build/aapp pi_10K.txt`

## Benchmarking

### Datasets
Datasets are taken from http://pizzachili.dcc.uchile.cl/, an extensive collection from Navarro, Ferragina et al. which have select some common domains of application of Approximate String Matches.
