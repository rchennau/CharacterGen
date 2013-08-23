!INCLUDE <ataricc65.mak>

target = AtariTemplate.xex

# objects = atari4.o ataristd.o 

$(target) : $(objects)
	$(CL) -t $(SYS) -o $@ $(objects) --ld-args -D,__RESERVED_MEMORY__=15339 main.c
	$(MV) $@ "$(BUILDDIR)\$@"
	@echo $(BUILDDIR)
 
all: $(target)
	
clean:
	$(RM) -f *.tgi
	$(RM) -f *.s
	$(RM) -f *.joy
	$(RM) -f *.o
	$(RM) $(target)
	$(RMDIR) -v "$(ODIR)\*"
	$(RMDIR) -v "$(BUILDDIR)"

win32: 
	
	
	