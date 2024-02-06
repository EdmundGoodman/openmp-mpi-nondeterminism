#include "ddot.hpp"


int ddot_serial(const int n, const double* const x, const double* const y, double* const result) {
    double local_result = 0.0;
    for (int i = 0; i < n; i++) {
        local_result += x[i] * y[i];
    };

    *result = local_result;

    return (0);
}

int ddot_openmp(const int n, const double* const x, const double* const y, double* const result) {
    double local_result = 0.0;
    #pragma omp parallel for reduction(+ : local_result)
    for (int i = 0; i < n; i++) {
        local_result += x[i] * y[i];
    };

    *result = local_result;

    return (0);
}

int ddot_mpi(const int n, const double* const x, const double* const y, double* const result) {
    double local_result = 0.0;
    for (int i = 0; i < n; i++) {
        local_result += x[i] * y[i];
    };

    double global_result = 0.0;
    MPI_Allreduce(&local_result, &global_result, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    *result = global_result;

    return (0);
}

int ddot_hybrid(const int n, const double* const x, const double* const y, double* const result) {
    double local_result = 0.0;
    #pragma omp parallel for reduction(+ : local_result)
    for (int i = 0; i < n; i++) {
        local_result += x[i] * y[i];
    };

    double global_result = 0.0;
    MPI_Allreduce(&local_result, &global_result, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    *result = global_result;

    return (0);
}
