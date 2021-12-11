CFLAGS = -std=c++17 -I. `pkg-config --static --cflags opencv4`
LDFLAGS = `pkg-config --static --libs opencv4`

# create list of all spv files and set as dependency
cppFiles = $(shell find . | grep -E ".cpp$$")
hppFiles = $(shell find . | grep -E ".hpp$$")

TARGET = stitchPattern

all: $(TARGET)
	echo Done

$(TARGET): $(vertObjFiles) $(fragObjFiles)
$(TARGET): $(cppFiles) $(hppFiles)
	g++ $(CFLAGS) -o $(TARGET) $(cppFiles) $(LDFLAGS)

# make shader targets
%.spv: %
	${GLSLC} $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
	rm -f $(vertObjFiles) $(fragObjFiles)