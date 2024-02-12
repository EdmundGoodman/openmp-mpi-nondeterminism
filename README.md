# Duplicating MPI/OpenMP non-deterministic interactions

This is an effort to duplicate non-deterministic interactions between MPI and OpenMP observed in the HPCCG benchmark `ddot` routine, when local reductions are used in combination with MPI all reduces.
