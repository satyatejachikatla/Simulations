
target := game-of-life

objs :=	main.o \
		CellMap/CellMap.o \
		CellMap/CellMapFactory.o \
		CellMap/GPU/CellMapCuda.o \
		CellMap/CPU/CellMapCPU.o

CFLAGS += -I.
NVCFLAGS += -I. -I../include/

LDFLAGS += -lm
NVLDFLAGS += -lm

# LDFLAGS += -Wl,--no-as-needed \
# 			$(shell pkg-config opencv --cflags --libs)

all: $(target)

include ../build/prog.mk
