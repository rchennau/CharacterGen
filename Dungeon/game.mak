!INCLUDE <ataricc65.mak>

target = AtariTemplate.xex
# objects = atari4.o ataristd.o 

$(target) : $(objects)
	$(CL) -l as.s -v -t $(SYS) -O -Or -Cl -Os -o $@ $(objects)  main.c
	$(MV) $@ .\$(BUILD)\$@
 
all: $(target)
	
clean:
	$(RM) -f *.tgi
	$(RM) -f *.s
	$(RM) -f *.joy
	$(RM) -f *.o
	$(RM) -f .\$(BUILD)\$@
	
	
	