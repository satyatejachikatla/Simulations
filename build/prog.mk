target ?=  
objs ?=

#deps := $(patsubst %.o,%.d,$(objs))
#-include $(deps) 
#DEPFLAGS = -MMD -MF $(@:,.o=.d)

$(target): $(objs)
	$(NVCC) $(NVCFLAGS) $(NVLDFLAGS) -o $@ $(notdir $^)
%.o: %.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) -c $< $(DEPFLAGS)
%.o: %.cu
	$(NVCC) $(NVCFLAGS) $(NVLDFLAGS) -c $< $(DEPFLAGS)

.PHONY: clean_build

clean_build:
	rm -f $(target) $(notdir $(objs)) $(deps)
