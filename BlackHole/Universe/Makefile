
target := libuniverse.so

objs :=	Universe.o \
		Uniforms.o \
		FrameBuffer.o \
		Camera.o \
		Renderer.o \
		Bodies/Body.o \
		Bodies/BlackHole.o

CFLAGS += -I..
NVCFLAGS += -I.. $(CUDA_UTILS_INCLUDE)

LDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./Bodies/install
NVLDFLAGS += -lm $(shell pkg-config opencv --cflags --libs) \
			-L./Bodies/install

all: $(target) install

install: $(target)
	mkdir -p ./install/
	cp $(target) ./install/

clean: clean_build
	rm -rf ./install/

include $(TOPDIR)/build/lib.mk