
target := wolfram

objs :=	main.o \
		Display.o

SUBDIR_CFLAGS := $(CFLAGS) -I..
SUBDIR_NVCFLAGS := $(NVCFLAGS) -I..
SUBDIR_LDFLAGS := $(LDFLAGS)
SUBDIR_NVLDFLAGS := $(NVLDFLAGS)

CFLAGS += -I.
NVCFLAGS += -I.

LDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./ElementaryCells -lelementarycells
NVLDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./ElementaryCells/install -lelementarycells

all: elementary_cells $(target) install

elementary_cells:
	$(MAKE) CFLAGS="$(SUBDIR_CFLAGS)" \
	LDFLAGS="$(SUBDIR_LDFLAGS)" \
	NVCFLAGS="$(SUBDIR_NVCFLAGS)" \
	NVLDFLAGS="$(SUBDIR_NVLDFLAGS)" \
	-C ElementaryCells

install: elementary_cells $(target)
	cp -r ./ElementaryCells/install .
	cp $(target) ./install

clean : clean_build
	$(MAKE) -C ElementaryCells clean
	rm -rf ./install

include $(TOPDIR)/build/prog.mk
