
AS=gcc
ASFLAGS=-m32 -g -Os
ASFLAGS+=-fno-builtin -nostdinc -falign-jumps=1 -falign-loops=1 -falign-functions=1

CC=gcc
CFLAGS=-m32 -g -Os
CFLAGS+= -fno-builtin -nostdinc \
	-falign-jumps=1 -falign-loops=1 -falign-functions=1 \
	-fno-stack-protector -fno-builtin-printf -fno-asynchronous-unwind-tables \
	-fno-asynchronous-unwind-tables

LD=ld

all : clean kernel.elf

#----------------------------------------------------------------------
# Compiling and linking a simple kernel, as an ELF executable.
#
# Notice the linking with no standard libraries and as an i386 elf.
# Very important: do not link with the -N option, our simple bootloader 
# would no longer be able to load it. 
#
# The reason why is not understood so far, it is just like this.
# This is a bit confusing since the -N option is necessary to link 
# the bootloader itself. Oh well...
#----------------------------------------------------------------------

kernel.elf: main.o crt0.o serial.o
	$(LD) -nostdlib -m elf_i386 -e crt0 -Tldscript -o $@ $+
	echo "  Done."

crt0.o: crt0.S 
	$(AS) -c $(ASFLAGS) -o $@ $<

main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

serial.o: serial.c
	$(CC) -c $(CFLAGS) -o $@ $<

#----------------------------------------------------------------------

clean:
	rm -f *.o kernel.elf *~ 

