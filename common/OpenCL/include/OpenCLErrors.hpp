#ifndef _OPENCL_ERRORS_H_
#define _OPENCL_ERRORS_H_

#include <stdio.h>
#include <CL/cl.h>

const char *getOpenCLErrorString(int error);

// Handy Macros //
#define checkOpenCLErrors(call)                                 \
  do {                                                          \
    int err = (call);                                           \
    if (err != CL_SUCCESS) {                                    \
      printf("OpenCL error at %s %d: %s\n", __FILE__, __LINE__, \
             getOpenCLErrorString(err));                        \
      exit(EXIT_FAILURE);                                       \
    }                                                           \
  } while (0)



#endif /* _OPENCL_ERRORS_H_ */