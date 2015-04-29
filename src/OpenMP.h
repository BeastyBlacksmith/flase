
#ifndef _OPENMP_H
#define _OPENMP_H

#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_thread_num();
int omp_get_num_threads();
int omp_get_max_threads();
void omp_set_num_threads();
void omp_set_dynamic( int );
void omp_set_nested( int );
#endif // _OPENMP

#endif // _OPENMP_H
