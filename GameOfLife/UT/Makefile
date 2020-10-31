
target := game-of-life

objs :=	main.o \
		ShellDisplay/ShellDisplay.o \
		OpenCVWindow/OpenCVWindow.o

CFLAGS +=	-I. \
			-I.. \
			$(OPENCL_UTILS_INCLUDE) 

NVCFLAGS +=	-I. \
			-I.. \
			$(CUDA_UTILS_INCLUDE) \
			$(OPENCL_UTILS_INCLUDE) 

SUBDIR_CFLAGS := $(CFLAGS)
SUBDIR_NVCFLAGS := $(NVCFLAGS)
SUBDIR_LDFLAGS := $(LDFLAGS)
SUBDIR_NVLDFLAGS := $(SUBDIR_NVLDFLAGS)

LDFLAGS += -lm -L../CellMap/ -lcellmap
NVLDFLAGS += -lm -L../CellMap/ -lcellmap

LDFLAGS +=  $(shell pkg-config opencv --cflags --libs)
NVLDFLAGS += $(shell pkg-config opencv --cflags --libs)

all: cellmap $(target) install

cellmap:
	$(MAKE) CFLAGS="$(SUBDIR_CFLAGS)" \
	LDFLAGS="$(SUBDIR_LDFLAGS)" \
	NVCFLAGS="$(SUBDIR_NVCFLAGS)" \
	NVLDFLAGS="$(SUBDIR_NVLDFLAGS)" \
	-C ../CellMap
	

install: cellmap $(target)
	cp -r ../CellMap/install .
	cp $(target) ./install/
	cp $(TOPDIR)/common/OpenCL/include/*.so ./install/

clean : clean_build
	$(MAKE) -C ../CellMap clean
	rm -rf ./install

include $(TOPDIR)/build/prog.mk
