/**
 * Copyright 2025 Jim Haslett
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "util.h"
#include <time.h>

double wtime() {
    /**
     * wtime function used to generate a wall time, in seconds, similar to MPI_wtime()
     * 
     * Based entirely on the MPI_wtime implementation:
     * https://github.com/open-mpi/ompi/blob/main/ompi/mpi/c/wtime.c
     */

    double wtime;
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    wtime  = (double)tp.tv_nsec/1.0e+9;
    wtime += tp.tv_sec;
    return wtime;
}