
target := flocking

objs :=	main.o \
		Display.o

SUBDIR_CFLAGS := $(CFLAGS) -I. -I.. -I$(TOPDIR)/vendor/glm
SUBDIR_NVCFLAGS := $(NVCFLAGS) -I. -I.. -I$(TOPDIR)/vendor/glm
SUBDIR_LDFLAGS := $(LDFLAGS)
SUBDIR_NVLDFLAGS := $(NVLDFLAGS)

CFLAGS += -I. -I$(TOPDIR)/vendor/glm
NVCFLAGS += -I. -I$(TOPDIR)/vendor/glm

LDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./Boids/install -lboids
NVLDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./Boids/install -lboids

all: boids $(target) install

boids:
	$(MAKE) CFLAGS="$(SUBDIR_CFLAGS)" \
	LDFLAGS="$(SUBDIR_LDFLAGS)" \
	NVCFLAGS="$(SUBDIR_NVCFLAGS)" \
	NVLDFLAGS="$(SUBDIR_NVLDFLAGS)" \
	-C Boids

install: boids $(target)
	cp -r ./Boids/install .
	cp $(target) ./install

clean : clean_build
	$(MAKE) -C Boids clean
	rm -rf ./install

include $(TOPDIR)/build/prog.mk
