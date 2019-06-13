# Primitive-Pythagorean-Triples
Primitive Pythagorean Triples

by Fabrizio Caruso


This is a simple code that enumerates all primitive Pythagorean triples by using Barning's theorem.
The triples are enumerated in breadth-first order.
The code can be built by any standard ANSI-compliant compiler such as GCC and CC65 (for the 6502 architecture).

## Compilation

### Use the Makefile targets.
For example: 
- **make c64_short** to produce a C64 binary that uses 16 bit integers 
- **make c64_long** to produce a C64 binary that uses 32 bit integers
- **make pc_short** to produce a PC binary that uses unsigned short integers
- **make pc_long** to produce a PC binary that uses unsigned long integers
- **make all** to produce all binary versions

### Use directly a compiler and pass the parameters to customize the computation and display

Use your preferred C compiler for your target architecture and pass the following parameters:
1. **-DUSE_SHORT** to force unsigned short computation (faster but at the risk of overflow) 
2. **-DTARGET=1000** to set the number of triples to compute
3. **-DDISPLAY_START=981** to set the initial triple to display

For example:
Under Linux, if you want to use **gcc** you may use:
gcc -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o PPT_short.out


