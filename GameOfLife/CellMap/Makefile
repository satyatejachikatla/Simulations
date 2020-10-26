
target := libcellmap.so

objs :=	CellMap.o \
		CellMapFactory.o \
		GPU/CellMapCuda.o \
		GPU/CellMapOpenCL.o \
		CPU/CellMapCPU.o

CFLAGS +=	-I.. \
			$(OPENCL_DEFINES) \
			$(OPENCL_INCLUDE) \
			$(OPENCL_UTILS_INCLUDE) \


NVCFLAGS +=	-I.. \
			$(OPENCL_DEFINES) \
			$(OPENCL_INCLUDE) \
			$(OPENCL_UTILS_INCLUDE) \
			$(CUDA_UTILS_INCLUDE)

LDFLAGS += -lm $(OPENCL_LIBRARY)
NVLDFLAGS += -lm $(OPENCL_LIBRARY)

all: $(target) install

install: $(target)
	mkdir -p ./install/kernels
	cp $(target) ./install/
	cp ./GPU/CellMapOpenCL.cl ./install/kernels/

include $(TOPDIR)/build/lib.mk

clean: clean_build
	rm -f ./install/*.so
	rm -f ./install/kernels/*