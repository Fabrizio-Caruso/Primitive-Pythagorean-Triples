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


# More than 1000 triples
c64_2k5_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=2500 -DDISPLAY_START=2481 PPT.c extern_c64_vars.s -o PPT_2k5_long.prg
	rm extern_c64_vars.o
	rm PPT.o

c64_2k_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=2000 -DDISPLAY_START=1981 PPT.c extern_c64_vars.s -o PPT_2k_long.prg
	rm extern_c64_vars.o
	rm PPT.o

# Compute up to 1000 with short digits (a few wrong triples when short is 16-bit)

## Sinclair ZX targets
	
	
zx_short:
	zcc$(EXEEXT) +zx -O3 -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -lndos -create-app 
	mv a.tap PPT_short_zx.tap
	rm a.bin
	rm a_BANK_7.bin

zx_short_sdcc:
	zcc$(EXEEXT) +zx -startup=1 -compiler=sdcc -SO3 --max-allocs-per-node200000 -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -lndos -create-app
	mv a.tap PPT_short_zx_sdcc.tap	
	rm a.bin
	rm a_BANK_7.bin
	
all_zx_short: zx_short zx_opt_short

all_zx_short_sdcc: zx_short_sdcc zx_opt_short_sdcc
	
	
## C64 targets	
c64_short:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_vars.s -o PPT_short.prg
	rm extern_c64_vars.o
	rm PPT.o

c64_more_vars_short:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DUSE_MORE_VARIABLES -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_vars.s -o PPT_opt_short.prg
	rm -rf PPT.o
	rm -rf PPT_short.o
	rm -rf extern_c64_short_vars.o
	
c64_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_vars.s -o PPT_long.prg
	rm extern_c64_vars.o
	rm PPT.o

all_c64: c64_short c64_long c64_more_vars_short
	
## PC targets
pc_short:
	gcc -DUSE_SHORT -DUSE_SHORT -DTARGET=65500 -DDISPLAY_START=65481 PPT.c -o PPT_short$(COMPILEDEXT)
	
pc_long:
	gcc -DTARGET=65500 -DDISPLAY_START=65481 PPT.c -o PPT_long$(COMPILEDEXT)
	
	
# 	
all: c64_short c64_long pc_short pc_long
	
clean:
	rm -rf *$(COMPILEDEXT)
	rm -rf *.prg
	rm -rf *.o
	rm -rf *.bin


	
