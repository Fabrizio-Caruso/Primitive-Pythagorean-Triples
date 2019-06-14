ifneq ($(COMSPEC),)
DO_WIN:=1
endif
ifneq ($(ComSpec),)
DO_WIN:=1
endif 

ifeq ($(DO_WIN),1)
EXEEXT = .exe
endif

ifeq ($(DO_WIN),1)
COMPILEDEXT = .exe
else
COMPILEDEXT = .out
endif


c64_short:
	cl65$(EXEEXT) -t c64 -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 -Oisr -Cl PPT_short.c -o PPT_short.prg
	rm PPT_short.o
	
c64_long:
	cl65$(EXEEXT) -t c64 -DTARGET=1000 -DDISPLAY_START=981  -Oisr -Cl PPT.c -o PPT_long.prg
	rm PPT.o
	
pc_short:
	gcc -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT_short.c -o PPT_short$(COMPILEDEXT)
	
pc_long:
	gcc -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o PPT_long$(COMPILEDEXT)
	
	
all: c64_short c64_long pc_short pc_long
	
clean:
	rm -rf *$(COMPILEDEXT)
	rm -rf *.prg
	rm -rf *.o
	
