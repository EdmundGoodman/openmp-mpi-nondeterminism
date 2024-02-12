#!/bin/bash

## Initialisation ##
export OMP_NUM_THREADS=10

## Build ##
make clean
make -j 8

## Run ##
echo "Running on one cluster node:"
./test_openmp_mpi 123456

echo; echo
echo "Running on four cluster nodes:"
mpirun -n 4 ./test_openmp_mpi 123456
