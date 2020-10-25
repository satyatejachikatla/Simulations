# https://unix.stackexchange.com/questions/235223/makefile-include-env-file

target ?=  
objs ?=

#deps := $(patsubst %.o,%.d,$(objs))
#-include $(deps) 
#DEPFLAGS = -MMD -MF $(@:,.o=.d)

$(target): $(objs)
	$(NVCC) $(NVCFLAGS) $(NVLDFLAGS) -shared -o $@ $(notdir $^)
%.o: %.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) -fPIC -c $< $(DEPFLAGS)
%.o: %.cu
	$(NVCC) $(NVCFLAGS) $(NVLDFLAGS) --compiler-options '-fPIC' -c $< $(DEPFLAGS)

.PHONY: clean

clean:
	rm -f $(target) $(notdir $(objs)) $(deps)
