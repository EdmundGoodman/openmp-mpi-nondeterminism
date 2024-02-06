#ifndef DDOT_H
#define DDOT_H
#include <mpi.h>

int ddot_serial(const int n, const double* const x, const double* const y, double* const result);
int ddot_openmp(const int n, const double* const x, const double* const y, double* const result);
#endif
