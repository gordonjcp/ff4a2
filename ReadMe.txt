30/1/2023 Gordon JC Pearce
This is a modified version of FIG-Forth for the Apple II, intended to allow
for running Cosmic Conquest as written out in the December 1982 issue of
Byte magazine.

The original source was taken from https://dwheeler.com/6502/

I made a handful of changes to allow it to assemble and link with ca65 and
ld65 as packaged for Ubuntu (although other distros ought to work too), and
also to move the loading address down and shift some zeropage addresses to
allow the high-res graphics to work.


How to build the fig-forth for the Apple II 080207 dkrueger

Install cc65 and a2tools.

Console:

ca65 figforth.s -l

ld65 -C apple2x.cfg figforth.o -o figforth.bin

a2tools in -r b MASTER.DSK FIGFORTH figforth.bin
