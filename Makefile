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

c64_3k_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=3000 -DDISPLAY_START=2981 PPT.c extern_c64_long_vars.s -o PPT_3k_long.prg
	rm extern_c64_long_vars.o
	rm PPT.o

c64_2k5_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=2500 -DDISPLAY_START=2481 PPT.c extern_c64_long_vars.s -o PPT_2k5_long.prg
	rm extern_c64_long_vars.o
	rm PPT.o

c64_2k_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=2000 -DDISPLAY_START=1981 PPT.c extern_c64_long_vars.s -o PPT_2k_long.prg
	rm extern_c64_long_vars.o
	rm PPT.o

c64_opt_short:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT_short.c extern_c64_short_vars.s -o PPT_opt_short.prg
	rm PPT_short.o
	rm extern_c64_short_vars.o

zx_opt_short:
	zcc$(EXEEXT) +zx -O3 -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT_short.c -lndos -create-app 
	mv a.tap PPT_opt_short_zx.tap
	rm a.bin
	rm a_BANK_7.bin
	
zx_opt_short_sdcc:
	zcc$(EXEEXT) +zx -startup=1 -compiler=sdcc -SO3 --max-allocs-per-node200000 -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT_short.c -lndos -create-app
	mv a.tap PPT_opt_short_zx_sdcc.tap
	rm a.bin
	rm a_BANK_7.bin
	
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
	
c64_short:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o PPT_short.prg
	rm PPT.o
	
c64_long:
	cl65$(EXEEXT) -t c64 -O --codesize 800 -Cl -DEXTERN_VARS -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_long_vars.s -o PPT_long.prg
	rm extern_c64_long_vars.o
	rm PPT.o
	
pc_opt_short:
	gcc -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT_short.c -o PPT_opt_short$(COMPILEDEXT)
	
pc_long:
	gcc -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o PPT_long$(COMPILEDEXT)
	
	
all: c64_short c64_long pc_short pc_long
	
clean:
	rm -rf *$(COMPILEDEXT)
	rm -rf *.prg
	rm -rf *.o
	rm -rf *.bin


	
