#!/bin/bash

# The QEMU hypervisor for the architecture i386
QEMU=qemu-system-i386

# QEMU Flags
#   debug: -s -S
# To set the debug flags, use the -debug argument.
#QFLAGS="-nographic"
QFLAGS=""

# The GNU compiler
# If you change this, make sure to change it also
# in the makefiles under ./mbr and ./kernel
GCC=gcc

# Flags for launching the sub-makefiles
#   -s for silent makefiles (no printing of the executed commands)
MFLAGS="-s"

# The name of the file containing our disk image.
DISK=disk.img
MBR=mbr/boot.mbr
KERNEL=kernel/kernel.elf

#--------------------------------------------------------------
# This function displays the help about how to use this script. 
#--------------------------------------------------------------
function help() {
    echo "Usage:"
    echo " $ ./mkdisk.sh [-help] [-debug]"
    echo " The debug option will launch QEMU in debug mode,"
    echo " waiting for a connection from gdb."
    echo " Look at the .gdbinit file to see the debug configuration."
}

#--------------------------------------------------------------
# Parsing arguments
#--------------------------------------------------------------

for arg in $* ; do
		if [ $arg == "-help" ]; then
				help
				exit 0
		elif [ $arg == "-debug" ]; then
				QFLAGS+=" -s -S"
		fi
done

#--------------------------------------------------------------
# Notice here that we source another script.
#--------------------------------------------------------------

echo "======================================================================"
echo "Checking dependencies..."
source checks.sh

#--------------------------------------------------------------
# Building the master boot record, the first sector of our
# disk image. The MBR contains our bootloder that will be
# loaded by the BIOS. The bootloader will load our kernel.
#--------------------------------------------------------------

echo "======================================================================"
echo "Building Master Boot Record..."

(cd mbr ; make $MFLAGS )
if [ $? -ne 0 ] ; then
    echo -e -n "${RED}"			
		echo "FAILED."
    echo "  Read the comment in the script below the line ${LINENO}"
		echo "  to have more information."
		echo -e -n "${NOCOLOR}"

		# Hum... something went wrong.
		# **** ASK FOR HELP ****
		#
		# First, try to understand what went wrong, launch the makefile manually.
		# You may be able to fix it easily.
		#
		# If this is a compilation error, related to cross-compiling to i386,
    # since we already checked that you have the support for the i386 architecture
		# and the multilib support for gcc, everything should have worked.
		# Bummer!
		#
		# You may be using a specific version of gcc, that is not the default one.
		# Check your version of gcc:
		#
		#   $ gcc --version
		#   gcc (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609
		#
    # So the version is 5.4.0 in this example.
		# Check to see if you have the corresponding support installed:
    #
		#   $ dpkg-query --search gcc-5*-multilib 
    #
		# If not, search for the package for the corresponding multilib support:
		#
		#   $ apt-cache search multilib | grep gcc-5
		#   gcc-5-multilib - GNU C compiler (multilib support)
    #
		# So you can install that specific multilib support, like this:
    #   $ sudo apt-get install gcc-5-multilib
    #
		# Otherwise, you can look at 
		#   https://wiki.debian.org/Multiarch/HOWTO"
    exit 1
fi

#--------------------------------------------------------------
# Building the code for our kernel
#--------------------------------------------------------------

echo "======================================================================"
echo "Building the kernel..."
(cd kernel ; make $MFLAGS )
if [ $? -ne 0 ] ; then
    echo -e -n "${RED}"			
    echo "Failed..."
    echo "  Read the comment in the script below the line ${LINENO}"
		echo "  to have more information."
		echo -e -n "${NOCOLOR}"
		# First, try to understand what went wrong, launch the makefile manually.
		# You may be able to fix it easily.
		#
		# If this is a compilation error, related to cross-compiling to i386,
    # since we already checked that you have the support for the i386 architecture
		# and the multilib support for gcc, everything should have worked.
		# Bummer!
		# **** ASK FOR HELP ****
    exit 1
fi

#--------------------------------------------------------------
# Creating the disk image, a raw disk image for QEMU
#  - small disk image 16KB = 32 * 512B
#  - Our MBR in the first sector
#  - Our kernel after that
#--------------------------------------------------------------

echo "======================================================================"
echo "Creating the disk image (QEMU raw format)..."

dd if=/dev/zero of=$DISK bs=512 count=32
dd if=$MBR of=$DISK bs=512 count=1
dd if=$KERNEL of=$DISK bs=512 seek=1
echo ""
echo "  Done."

#--------------------------------------------------------------
# Booting a i386 virtual machine, using QEMU.
# This will execute our kernel.
# You may take this execution under the control of the GNU debugger (gdb).
# You have been given two readme files: README-QEMU and README-GDB
echo "======================================================================"
echo "Booting a virtual machine with QEMU..."
echo ""
echo -e -n "${GREEN}"			
echo "Nota Bene: to stop QEMU: "
echo "    - hit 'Ctrl-A' and then 'c', you will get to QEMU monitor"
echo "    - then type 'quit' "
echo -e -n "${NOCOLOR}"
echo ""

$QEMU -serial mon:stdio -drive format=raw,file=$DISK $QFLAGS

exit 0
