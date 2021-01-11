
target := bh

objs :=	main.o \
		Display.o

SUBDIR_CFLAGS := $(CFLAGS) -I.. 
SUBDIR_NVCFLAGS := $(NVCFLAGS) -I.. $(CUDA_UTILS_INCLUDE)
SUBDIR_LDFLAGS := $(LDFLAGS)
SUBDIR_NVLDFLAGS := $(NVLDFLAGS)

CFLAGS += -I.
NVCFLAGS += -I. $(CUDA_UTILS_INCLUDE)

LDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./Universe/install -luniverse
NVLDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./Universe/install -luniverse

all: universe $(target) install

universe:
	$(MAKE) CFLAGS="$(SUBDIR_CFLAGS)" \
	LDFLAGS="$(SUBDIR_LDFLAGS)" \
	NVCFLAGS="$(SUBDIR_NVCFLAGS)" \
	NVLDFLAGS="$(SUBDIR_NVLDFLAGS)" \
	-C Universe

install: universe $(target)
	cp -r ./Universe/install .
	cp $(target) ./install

clean : clean_build
	$(MAKE) -C Universe clean
	rm -rf ./install

include $(TOPDIR)/build/prog.mk
