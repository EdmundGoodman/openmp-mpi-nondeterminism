#include <iomanip>
#include <iostream>
#include "ddot.hpp"

int main(int argc, char *argv[]) {

#ifdef USING_MPI
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#else
    int size = 1;  // Serial case (not using MPI)
    int rank = 0;
#endif

    // Set the size of the arrays to compute
    if (argc != 2) {
        std::cerr << "Provide the array sizes as an input!" << std::endl;
        exit(1);
    }
    int length = atoi(argv[1]);


    // Construct the arrays of doubles to dot product
    double *x = new double[length];
    double *y = new double[length];
    for (int i=0; i<length; i++) {
        x[i] = (double) i / 3;
        y[i] = (double) (length-i) / 3;
    }

    // Calculate the dot product without OpenMP or MPI
    double result_serial = 0.0;
    if (rank == 0) {
        ddot_serial(length, x, y, &result_serial);
        std::cout << "Serial: " << std::setprecision (15) << result_serial << std::endl;
    }

    // Calculate the dot product with OpenMP only
    double result_openmp = 0.0;
    if (rank == 0) {
        ddot_openmp(length, x, y, &result_openmp);
        std::cout << "OpenMP: " << std::setprecision (15) << result_openmp << std::endl;
    }


    // ====================================================================== //
    // MPI_Barrier(MPI_COMM_WORLD);

    // Calculate values for MPI rank splitting
    int offset = ((length / size) * rank);
    int split_length;
    if (rank != size - 1) {
        split_length = length / size;
    } else {
        split_length = length - offset;
    }
    double *split_x = new double[split_length];
    double *split_y = new double[split_length];
    for (int i=0; i<split_length; i++) {
        split_x[i] = (double) (i + offset) / 3;
        split_y[i] = (double) (length - (i + offset)) / 3;
    }
    // std::cout << rank << ": offset=" << offset << ", split length=" << split_length << std::endl;

    // Calculate the dot product with MPI only
    double result_mpi = 0.0;
    ddot_mpi(split_length, split_x, split_y, &result_mpi);
    if (rank == 0) {
        std::cout << "MPI: " << std::setprecision (15) << result_mpi << std::endl;
    }

    // Calculate the dot product with both OpenMP and MPI
    double result_hybrid = 0.0;
    ddot_hybrid(split_length, split_x, split_y, &result_hybrid);
    if (rank == 0) {
        std::cout << "Hybrid: " << std::setprecision (15) << result_hybrid << std::endl;
    }


#ifdef USING_MPI
    MPI_Finalize();
#endif
    return 0;
}
