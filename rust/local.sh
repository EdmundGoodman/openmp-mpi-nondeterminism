#!/bin/bash
set -e

## Initialisation ##
export RAYON_NUM_THREADS=5

## Build ##
# cargo clean
cargo build --release

## Run ##
# echo "Running on one cluster node:"
# time ./target/release/rust-openmp-mpi-poc 123456
# echo; echo

echo "Running on four cluster nodes:"
time mpirun -n 4 ./target/release/rust-openmp-mpi-poc 123456
