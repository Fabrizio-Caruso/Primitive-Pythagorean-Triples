# Primitive-Pythagorean-Triples
Primitive Pythagorean Triples

This is a simple code that enumerates all primitive Pythagorean triples by using Barning's theorem.
The triples are enumarate in breadth-first order.
The code can be built by any standard ANSI-complyant compiler such as GCC and CC65 (for the 6502 architecture).

## Compilation

### Use the Makefile targets.
For example use
**make all** produce versions that use unsigned short, unsigned long numbers for both the PC and the Commodore 64.
See Makefile for other targets

### Use the compiler and pass the parameters

Use your prefered C compiler for your target architecture and pass the following parameters:
1. **-DUSE_SHORT** to force unsigned short computation (faster but at the risk of overflow) 
2. **-DTARGET=1000** to set the number of triples to compute
3. **-DDISPLAY_START=981** to set the initial triple to display

For example:
Under Linux, if you want to use **gcc** you may use:
gcc -DUSE_SHORT -DTARGET=1000 -DDISPLAY_START=981 PPT.c -o PPT_short.out


