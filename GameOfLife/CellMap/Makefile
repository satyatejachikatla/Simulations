
target := libcellmap.so

objs :=	CellMap.o \
		CellMapFactory.o \
		GPU/CellMapCuda.o \
		CPU/CellMapCPU.o

CFLAGS += -I..
NVCFLAGS +=	-I.. $(CUDA_UTILS_INCLUDE)

LDFLAGS += -lm
NVLDFLAGS += -lm

# LDFLAGS += -Wl,--no-as-needed \
# 			$(shell pkg-config opencv --cflags --libs)

all: $(target)

include $(TOPDIR)/build/lib.mk
