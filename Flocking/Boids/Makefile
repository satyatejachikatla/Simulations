
target := libboids.so

objs :=	Flock.o Boid.o

all: $(target) install

install: $(target)
	mkdir -p ./install/
	cp $(target) ./install/

clean: clean_build
	rm -rf ./install/

include $(TOPDIR)/build/lib.mk