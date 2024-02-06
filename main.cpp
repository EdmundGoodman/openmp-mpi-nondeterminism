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

    if (argc != 2) {
        std::cerr << "Provide the array sizes as an input!" << std::endl;
        exit(1);
    }

    // Set the size of the arrays to computer
    int n = atoi(argv[1]);

    // Construct the arrays of doubles to dot product
    double *x = new double[n];
    double *y = new double[n];
    for (int i=0; i<n; i++) {
        x[i] = (double) i / 3;
    }
    for (int i=0; i<n; i++) {
        y[i] = (double) (n-i) / 3;
    }

    // Calculate the dot product with and without OpenMP
    double result_serial = 0.0;
    ddot_serial(n, x, y, &result_serial);

    double result_openmp = 0.0;
    ddot_openmp(n, x, y, &result_openmp);

    // Print the result of the dot product at full precision
    if (rank == 0) {
        std::cout << std::setprecision (15) << result_serial << std::endl;
        std::cout << std::setprecision (15) << result_openmp << std::endl;
    }

#ifdef USING_MPI
    MPI_Finalize();
#endif
    return 0;
}
