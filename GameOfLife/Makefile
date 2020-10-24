
object-files := main.o CellMap/CellMap.o CellMap/CellMapFactory.o CellMap/CPU/CellMapCPU.o
prog-name    := game-of-life

CFLAGS += -I.

LDFLAGS += -Wl,--no-as-needed \
			$(shell pkg-config opencv --cflags --libs)

include ../build/prog_cpp.mk
