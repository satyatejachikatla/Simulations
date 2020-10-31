
target := wolfram

objs :=	main.o 

CFLAGS +=	-I. 

NVCFLAGS +=	-I.

LDFLAGS += -lm $(shell pkg-config opencv --cflags --libs)
NVLDFLAGS += -lm $(shell pkg-config opencv --cflags --libs)

all: $(target) install

install: $(target)
	mkdir ./install
	cp $(target) ./install

clean : clean_build
	rm -rf ./install

include $(TOPDIR)/build/prog.mk
