export MAKE="make"

export CC="gcc"
export CXX="g++"
export AR="ar"

export CFLAGS="-Werror"
export LDFLAGS="-lcuda `pkg-config cudart-10.2 --cflags --libs`"


export NVCC="nvcc"

export NVCFLAGS="--Werror all-warnings"
export NVLDFLAGS=""

