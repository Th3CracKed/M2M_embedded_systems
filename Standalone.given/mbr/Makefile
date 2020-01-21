
NOOUTPUT=">> /dev/null 2>&1"

AS=gcc
ASFLAGS=-m32 -g -Os -fno-builtin -nostdinc -falign-jumps=1 -falign-loops=1 -falign-functions=1

CC=gcc
CFLAGS=-m32 -g -Os \
	-fno-builtin -nostdinc \
	-falign-jumps=1 -falign-loops=1 -falign-functions=1 \
	-fno-stack-protector -fno-builtin-printf -fno-asynchronous-unwind-tables \
	-fno-asynchronous-unwind-tables

LD=ld
LDFLAGS= -nostdlib -N -m elf_i386

OBJCOPY=objcopy
all: clean boot.mbr

#---------------------------------------------------------------------------
# Generates Master Boot Record (mbr)
#---------------------------------------------------------------------------
boot.mbr: boot.elf 
	$(OBJCOPY) -S -O binary $< $@ 
	exec echo -n -e "\x55\xAA" | dd of=$@ seek=510 bs=1 conv=notrunc >> /dev/null 2>&1
	echo "  Done."

boot.elf: boot.o loader.o
	$(LD) $(LDFLAGS) -e start -Ttext 0x7c00 -o $@ $+

# Older command formats with earlier GCC toolchains...
#	$(LD) --verbose -m elf_i386 -e start -Ttext 0x7c00 --oformat binary -o $@ $+
#	$(LD) -m elf_i386 -e start -Ttext 0x7c00 --oformat binary -b elf32-i386 -o $@ $+

boot.o: boot.S 
	$(AS) -c $(ASFLAGS) -o $@ $<

loader.o: loader.c loader.h
	$(CC) -c $(CFLAGS) -o $@ $<

#----------------------------------------------------------------------
clean:
	rm -f boot.mbr boot.elf *.o *~
