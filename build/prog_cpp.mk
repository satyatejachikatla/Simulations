# https://unix.stackexchange.com/questions/235223/makefile-include-env-file

object-files ?= 
prog-name ?= run

object-files-cpp := $(shell echo $(object-files) | sed 's/\.o/\.cpp/g')

$(info Files getting built : $(object-files-cpp))

.PHONY: clean build all

all : clean build

build:
	$(CXX) $(CFLAGS) $(LDFLAGS) $(LIBS) -c $(object-files-cpp)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(LIBS) *.o -o $(prog-name)

clean:
	rm -f *.o
	rm -f $(prog-name)
