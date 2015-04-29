
#include "OpenMP.h"

#ifndef _OPENMP
int omp_get_thread_num() { return 0; }
int omp_get_num_threads() { return 1; }
int omp_get_max_threads() { return 1; }
void omp_set_num_threads() {}
void omp_set_dynamic( int ) {}
void omp_set_nested( int ) {}
#endif //  _OPENMP
