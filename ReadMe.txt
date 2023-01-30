30/1/2023 Gordon JC Pearce
This is a modified version of FIG-Forth for the Apple II, intended to allow
for running Cosmic Conquest as written out in the December 1982 issue of
Byte magazine.

The original source was taken from https://dwheeler.com/6502/

I made a handful of changes to allow it to assemble and link with ca65 and
ld65 as packaged for Ubuntu (although other distros ought to work too), and
also to move the loading address down and shift some zeropage addresses to
allow the high-res graphics to work.

Copying Forth Screens onto the disk
-----------------------------------

The included tool `screenify` is a very dangerous tool for writing text onto
raw blocks of the disk. Dangerous, because it's quite badly written, may be
able to crash your system if misused, and will almost certainly leave your
Apple II disk image unusable if you get the slightest thing wrong.

Please note that `screenify` will make no effort to stop you overwriting
the DOS sectors or directory sectors, or any existing files.

To compile it, type:

    gcc screenify.c -o screenify

To copy a file into the disk, use the command like `./screenify forth.dsk
screens.txt 10`, which will write to "Screen 10" of the disk.


Original Readme file
--------------------

How to build the fig-forth for the Apple II 080207 dkrueger

Install cc65 and a2tools.

Console:

ca65 figforth.s -l

ld65 -C apple2x.cfg figforth.o -o figforth.bin

a2tools in -r b MASTER.DSK FIGFORTH figforth.bin
