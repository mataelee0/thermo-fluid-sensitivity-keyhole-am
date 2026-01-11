# thermo-fluid-sensitivity-keyhole-am
Repository containing code and data accompanying the paper "Thermo-Fluid Simulation-Based Sensitivity Analysis of Thermophysical Properties Affecting Keyhole Depth in Metal Additive Manufacturing".

This code is based on the OpenFOAM solver laserbeamFoam.
The original laserbeamFoam implementation is available at:
(https://github.com/laserbeamfoam/LaserbeamFoam.git)

This repository contains modified and extended versions of laserbeamFoam
developed for thermo-fluid simulations and sensitivity analysis of
keyhole depth in metal additive manufacturing.


## Requirements
1. OpenFOAM Foundation version 10 is required.
   The OpenFOAM-10 source code is available at:
   https://openfoam.org/download/10/
2. The laserbeamFoam solver developed by Flint et al. must be installed.


## Solver compilation
The solver directory contains source code for compiling the
laserbeamFoam-based solver.

Before compilation, the include path to the `laserHeatSource` library
installed with laserbeamFoam must be specified in the solver build options.

Specifically, the path to `laserHeatSource/lnInclude` should be added
to the `EXE_INC` entry in the `Make/options` file.
The correct path can be identified from the local laserbeamFoam installation.

1. Navigate to the solver directory:
```bash
cd solver
```
2. Compile the solver:
```bash
./Allwmake
```

After successful compilation, the solver can be executed using:
```bash
   laserbeamFoam
```


## Case setup and execution
Simulation cases are provided in the following directories:
- run_stationary
- run_scanning

Before running the simulations, appropriate thermophysical properties
must be specified for each case.


### Running a simulation
From within either the run_stationary or run_scanning directory,
execute the following commands:
1. Generate the computational mesh:
```bash
blockMesh
```
2. Initialize fields:
```bash
cp -r initial/ 0/
setFields
```
3. Decompose the domain for parallel execution:
```bash
decomposePar
```

### Solver execution
Serial execution:
   laserbeamFoam
Parallel execution (example using 32 processors):
```bash
mpirun -np 32 laserbeamFoam -parallel >& log
```
