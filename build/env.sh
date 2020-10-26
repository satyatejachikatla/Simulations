#!/bin/bash

#======================================
# Environment setup
cd $(dirname "$0")/..
export TOPDIR="`pwd`"
#======================================

#======================================
# Common Compile Flags
export MAKE="make"

#opencl defaults
export OPENCL_UTILS_INCLUDE="-I$TOPDIR/common/OpenCL/include"
export OPENCL_INCLUDE="-I/usr/include/"
export OPENCL_LIBRARY="-L/usr/lib/x86_64-linux-gnu/ -lOpenCL"

#cuda defaults
export CUDA_UTILS_INCLUDE="-I$TOPDIR/common/CUDA/include"

# gcc,g++
export CC="gcc"
export CXX="g++"
export AR="ar"

export CFLAGS="-Wl,--no-as-needed -Werror"
export LDFLAGS="-lcuda `pkg-config cudart-10.2 --cflags --libs`"

#nvcc
export NVCC="nvcc"

export NVCFLAGS="--Werror all-warnings"
export NVLDFLAGS="$OPENCL_LIBRARY"

#======================================

echo "-------------------------------------------"
echo TOPDIR : $TOPDIR
echo OPENCL_LIBRARY : $OPENCL_LIBRARY
echo OPENCL_INCLUDE : $OPENCL_INCLUDE
echo OPENCL_UTILS_INCLUDE : $OPENCL_UTILS_INCLUDE
echo CUDA_UTILS_INCLUDE : $CUDA_UTILS_INCLUDE
echo "-------------------------------------------"

bash