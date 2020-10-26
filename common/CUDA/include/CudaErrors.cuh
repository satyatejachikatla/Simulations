#ifndef _CUDA_ERRORS_H_
#define _CUDA_ERRORS_H_

#include <stdio.h>

// Handy Macros //
////////////////////////////////////////////////////////
#define checkCudaErrors(call)                                 \
  do {                                                        \
    cudaError_t err = call;                                   \
    if (err != cudaSuccess) {                                 \
      printf("CUDA error at %s %d: %s\n", __FILE__, __LINE__, \
             cudaGetErrorString(err));                        \
      cudaDeviceReset();                                      \
      exit(EXIT_FAILURE);                                     \
    }                                                         \
  } while (0)
////////////////////////////////////////////////////////
#endif /* _CUDA_ERRORS_H_ */