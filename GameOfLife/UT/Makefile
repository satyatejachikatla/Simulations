
target := game-of-life

objs :=	main.o \
		ShellDisplay/ShellDisplay.o \
		OpenCVWindow/OpenCVWindow.o

CFLAGS += -I. -I..
NVCFLAGS += -I. -I.. -I../../include/

LDFLAGS += -lm -L../CellMap/ -lcellmap
NVLDFLAGS += -lm -L../CellMap/ -lcellmap

LDFLAGS += -Wl,--no-as-needed \
			$(shell pkg-config opencv --cflags --libs)
NVLDFLAGS += $(shell pkg-config opencv --cflags --libs)

all: cellmap $(target)

cellmap:
	$(MAKE) LDFLAGS= \
	NVLDFLAGS= -C ../CellMap

clean : clean_build
	$(MAKE) -C ../CellMap clean 

include ../../build/prog.mk
