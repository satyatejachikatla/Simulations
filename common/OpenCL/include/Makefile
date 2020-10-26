
target := libOpenCLUtils.so

objs :=	OpenCLErrors.o \
		OpenCLCompileUtils.o

CFLAGS += -I. $(OPENCL_DEFINES) $(OPENCL_INCLUDE)
NVCFLAGS +=	-I. $(OPENCL_DEFINES) $(OPENCL_INCLUDE)

LDFLAGS += $(OPENCL_LIBRARY)
NVLDFLAGS += $(OPENCL_LIBRARY)

# LDFLAGS += -Wl,--no-as-needed \
# 			$(shell pkg-config opencv --cflags --libs)

all: $(target)

include $(TOPDIR)/build/lib.mk
