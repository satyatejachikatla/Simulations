
target := game-of-life

objs :=	main.o \
		ShellDisplay/ShellDisplay.o \
		OpenCVWindow/OpenCVWindow.o

CFLAGS +=	-I. \
			-I..
NVCFLAGS +=	-I. \
			-I.. \
			$(CUDA_UTILS_INCLUDE)

LDFLAGS += -lm -L../CellMap/ -lcellmap
NVLDFLAGS += -lm -L../CellMap/ -lcellmap

LDFLAGS +=  $(shell pkg-config opencv --cflags --libs)
NVLDFLAGS += $(shell pkg-config opencv --cflags --libs)

all: cellmap $(target)

cellmap:
	$(MAKE) LDFLAGS= \
	NVLDFLAGS= -C ../CellMap

clean : clean_build
	$(MAKE) -C ../CellMap clean 

include $(TOPDIR)/build/prog.mk
