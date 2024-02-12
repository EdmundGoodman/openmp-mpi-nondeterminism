#!/bin/bash

#SBATCH --job-name=multicore-cpu # Job name for tracking
#SBATCH --partition=cpu-batch  # Partition you wish to use (see above for list)
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=12     # Number of CPU threads used by your job
#SBATCH --time=2-00:00:00      # Job time limit set to 2 days (48 hours)
#SBATCH --output=cpp_joboutput_%j.out # Standard out from your job

## Initialisation ##
module purge
module load cs402-mpi
export OMP_NUM_THREADS=10

## Build ##
cargo build --release

## Run ##
# echo "Running on one cluster node:"
# srun time ./target/release/rust-openmp-mpi-poc 123456
# echo; echo

echo "Running on four cluster nodes:"
srun time mpirun -n 4 ./target/release/rust-openmp-mpi-poc 123456
