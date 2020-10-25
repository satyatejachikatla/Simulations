
target := libcellmap.so

objs :=	CellMap.o \
		CellMapFactory.o \
		GPU/CellMapCuda.o \
		CPU/CellMapCPU.o

CFLAGS += -I..
NVCFLAGS += -I.. -I../../include/

LDFLAGS += -lm
NVLDFLAGS += -lm

# LDFLAGS += -Wl,--no-as-needed \
# 			$(shell pkg-config opencv --cflags --libs)

all: $(target)

include ../../build/lib.mk
