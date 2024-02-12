#!/bin/bash
set -e

## Initialisation ##
export OMP_NUM_THREADS=5

## Build ##
make clean
make -j 8

## Run ##
# echo "Running on one cluster node:"
# time ./test_openmp_mpi 123456
# echo; echo

echo "Running on four cluster nodes:"
time mpirun -n 4 ./test_openmp_mpi 123456
