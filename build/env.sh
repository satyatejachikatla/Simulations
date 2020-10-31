#!/bin/bash

#======================================
# Environment setup
cd $(dirname "$0")/..
export TOPDIR="`pwd`"
cd -
#======================================

#======================================
# Common Compile Flags
export MAKE="make"

#opencl defaults
export OPENCL_VERSION="120"
export OPENCL_DEFINES="-DCL_HPP_TARGET_OPENCL_VERSION=$OPENCL_VERSION -DCL_HPP_MINIMUM_OPENCL_VERSION=$OPENCL_VERSION" 
export OPENCL_UTILS_INCLUDE="$OPENCL_DEFINES -I$TOPDIR/common/OpenCL/include -L$TOPDIR/common/OpenCL/include -lOpenCLUtils"
#export OPENCL_INCLUDE="$OPENCL_DEFINES -I/usr/include/"
#export OPENCL_LIBRARY="-L/usr/lib/x86_64-linux-gnu/ -lOpenCL"

export OPENCL_CFLGAS="-Wno-ignored-attributes"
export OPENCL_INCLUDE="$OPENCL_DEFINES -I/usr/local/cuda-10.2/targets/x86_64-linux/include/ -I$TOPDIR/vendor/"
export OPENCL_LIBRARY="-L/usr/local/cuda-10.2/targets/x86_64-linux/lib -lOpenCL"


#cuda defaults
export CUDA_UTILS_INCLUDE="-I$TOPDIR/common/CUDA/include"

# gcc,g++
export CC="gcc"
export CXX="g++ -std=c++11"
export AR="ar"

export CFLAGS="-Wl,--no-as-needed $OPENCL_CFLGAS"
export LDFLAGS="-lcuda `pkg-config cudart-10.2 --cflags --libs`"

#nvcc
export NVCC="nvcc"

export NVCFLAGS="-Werror all-warnings"
export NVLDFLAGS="$OPENCL_LIBRARY"

#======================================

echo "-------------------------------------------"
echo TOPDIR : $TOPDIR
echo OPENCL_LIBRARY : $OPENCL_LIBRARY
echo OPENCL_INCLUDE : $OPENCL_INCLUDE
echo OPENCL_UTILS_INCLUDE : $OPENCL_UTILS_INCLUDE
echo OPENCL_DEFINES : $OPENCL_DEFINES
echo CUDA_UTILS_INCLUDE : $CUDA_UTILS_INCLUDE
echo "-------------------------------------------"

#======================================

echo "Making Common Code"
$MAKE -C $TOPDIR/common/OpenCL/include
echo "-------------------------------------------"

#======================================
echo "Starting working Shell"
bash