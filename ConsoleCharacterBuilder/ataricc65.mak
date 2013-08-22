CC65="C:\media\cc65-master"
CC65_BIN=$(CC65)\bin
CC65_INC=$(CC65)\include
CC65_ASMINC=$(CC65)\asminc
CC65_TOOLS=$(CC65)\wbin
 
BUILDDIR=$(MAKEDIR)\$(BUILD)
ODIR=$(MAKEDIR)\obj
 


.SUFFIXES : .c .s .o .asm .bmp .pal .spr
.SOURCE : 
 
# Compiling for Atari 8-Bit system
SYS=atari
 
# Names of tools
CO=co65
CC=cc65
AS=ca65
AR=ar65
CL=cl65
SPRPCK=sprpck
CP=copy
RM=rm
ECHO=echo
TOUCH=touch
MV=mv
 
CODE_SEGMENT=CODE
DATA_SEGMENT=DATA
RODATA_SEGMENT=RODATA
BSS_SEGMENT=BSS
 
SEGMENTS=--code-name $(CODE_SEGMENT) \
	--rodata-name $(RODATA_SEGMENT) \
	--bss-name $(BSS_SEGMENT) \
	--data-name $(DATA_SEGMENT)
 
# Flag for assembler
AFLAGS=
# Flags for C-code compiler
CFLAGS=-I . -t $(SYS) --add-source -O -Or -Cl -Os 
 
# Rule for making a *.o file out of a *.s file
.s.o:
  $(AS) -t $(SYS) -I $(CC65_ASMINC) -o $@ $(AFLAGS) $<
 
# Rule for making a *.o file out of a *.c file
.c.o:
  $(CC) $(SEGMENTS) $(CFLAGS) $<
  $(AS) -o $@ $(AFLAGS) $(*).s
 
ataristd.o:
  $(CP) $(CC65_INC)\..\joy\$*.joy .
  $(CO) --code-label _ataristd $*.joy
  $(AS) -t atari -o $@ $(AFLAGS) $*.s
  $(RM) $*.joy
  $(RM) $*.s
 
atari4.o:
  $(CP) $(CC65_INC)\..\tgi\$*.tgi .
  $(CO) --code-label _atari $*.tgi
  $(AS) -t atari -o $@ $(AFLAGS) $*.s
  $(RM) $*.tgi
  $(RM) $*.s
 
# Rule for making a *.o file out of a *.bmp file
.bmp.o:
  $(SPRPCK) -t6 -p2 $<
  $(ECHO) .global _$(*B) > $*.s
  $(ECHO) .segment "$(RODATA_SEGMENT)" >> $*.s
  $(ECHO) _$(*B): .incbin "$*.spr" >> $*.s
  $(AS) -t atari -o $@ $(AFLAGS) $*.s
  $(RM) $*.s
  $(RM) $*.pal
  $(RM) $*.spr