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

BUILD_PATH ?= ./build

# More than 1000 triples
c64_2k5_long:
	cl65$(EXEEXT) -t c64 -O $(CODE_SIZE_OPT) -Cl -DEXTERN_VARS -DTARGET=2500 -DDISPLAY_START=2481 PPT.c extern_c64_vars.s -o $(BUILD_PATH)/PPT_2k5_long.prg
	rm extern_c64_vars.o
	rm PPT.o

c64_2k_long:
	cl65$(EXEEXT) -t c64 -O $(CODE_SIZE_OPT) -Cl -DEXTERN_VARS -DTARGET=2000 -DDISPLAY_START=1981 PPT.c extern_c64_vars.s -o $(BUILD_PATH)/PPT_2k_long.prg
	rm extern_c64_vars.o
	rm PPT.o

# Compute up to 1000 with short digits (a few wrong triples when short is 16-bit)

## Sinclair ZX targets

CODE_SIZE_OPT=--codesize 800

test_sccz80:
	zcc$(EXEEXT) +zx test.c -lndos -create-app
	mv a.tap $(BUILD_PATH)/test_sccz80.tap	
	rm a.bin
	rm a_BANK_7.bin	

test_sdcc:
	zcc$(EXEEXT) +zx -v -compiler=sdcc test.c  -lndos -create-app
	mv a.tap $(BUILD_PATH)/test_sdcc.tap	
	rm a.bin
	rm a_BANK_7.bin	
	
zx_short:
	zcc$(EXEEXT) +zx -O2 --opt-code-speed=all -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -lndos -create-app 
	mv a.tap $(BUILD_PATH)/PPT_short_zx.tap
	rm a.bin
	rm a_BANK_7.bin

zx_short_sdcc:
	zcc$(EXEEXT) +zx -compiler=sdcc -SO3 --max-allocs-per-node200000 -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -lndos -create-app
	mv a.tap $(BUILD_PATH)/PPT_short_zx_sdcc.tap	
	rm a.bin
	rm a_BANK_7.bin
	
zx_long:
	zcc$(EXEEXT) +zx -O2 --opt-code-speed=all -DTARGET=1000 -DDISPLAY_START=981 PPT.c -lndos -create-app 
	mv a.tap $(BUILD_PATH)/PPT_long_zx.tap
	rm a.bin
	rm a_BANK_7.bin

zx_long_sdcc:
	zcc$(EXEEXT) +zx -compiler=sdcc -SO3 --max-allocs-per-node200000 -DTARGET=1000 -DDISPLAY_START=981 PPT.c -lndos -create-app
	mv a.tap $(BUILD_PATH)/PPT_long_zx_sdcc.tap	
	rm a.bin
	rm a_BANK_7.bin	
	
all_zx: zx_short zx_long

all_zx_sdcc: zx_short_sdcc zx_long_sdcc

## VBCC C64 targets	

vbcc_c64_triples: vbcc_c64_short

vbcc_c64_short:
	vc$(EXEEXT) +c64 -O4  -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o $(BUILD_PATH)/vbcc_c64_PPT_short.prg
	
## C64 targets	

cc65_c64_triples: c64_short_no_extern

c64_short_less_vars:
	cl65$(EXEEXT) -t c64 -O $(CODE_SIZE_OPT) -Cl -DEXTERN_VARS -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_vars.s -o $(BUILD_PATH)/PPT_short_less_vars.prg
	rm -rf extern_c64_vars.o
	rm -rf PPT.o

c64_short_no_extern:
	cl65$(EXEEXT) -t c64 -Or $(CODE_SIZE_OPT) -Cl -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o $(BUILD_PATH)/PPT_short_no_extern.prg
	rm -rf PPT.o



c64_short:
	cl65$(EXEEXT) -t c64 -O $(CODE_SIZE_OPT) -Cl -DEXTERN_VARS -DUSE_MORE_VARIABLES -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_extra_vars.s extern_c64_vars.s -o $(BUILD_PATH)/cc65_c64_PPT_short.prg
	rm -rf PPT.o
	rm -rf PPT_short.o
	rm -rf extern_c64_vars.o
	rm -rf extern_c64_extra_vars.o
	
c64_long:
	cl65$(EXEEXT) -t c64 -O $(CODE_SIZE_OPT) -Cl -DEXTERN_VARS -DTARGET=1000 -DDISPLAY_START=981 PPT.c extern_c64_vars.s -o $(BUILD_PATH)/PPT_long.prg
	rm -rf extern_c64_vars.o
	rm -rf PPT.o

all_c64: c64_short c64_long c64_short_less_vars c64_short_no_extern
	
## PC targets
pc_short:
	gcc -DUSE_SHORT -DUSE_SHORT -DTARGET=65500 -DDISPLAY_START=65481 PPT.c -o $(BUILD_PATH)/PPT_short$(COMPILEDEXT)
	
pc_long:
	gcc -DTARGET=65500 -DDISPLAY_START=65481 PPT.c -o $(BUILD_PATH)/PPT_long$(COMPILEDEXT)
	
all_pc: pc_short pc_long

# 	
all: all_zx all_c64 all_pc
	
clean:
	rm -rf *$(COMPILEDEXT)
	rm -rf *.prg
	rm -rf *.o
	rm -rf *.bin


	
