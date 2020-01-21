
# Color definitions for colored output via echo.
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
NOCOLOR='\033[0m'

#======================================================================
# Checking for GCC
#======================================================================

echo "Checking for gcc..."
which $GCC >> /dev/null 2>&1
if [ $? -ne 0 ] ; then
		echo -e -n "${RED}"
		echo "Missing $GCC, really?"
		echo -e -n "${NOCOLOR}"
    exit 1
fi
echo " + found $GCC"

#======================================================================
# Checking for QEMU
#======================================================================

echo "Checking for QEMU for the architecture i386"
which $QEMU >> /dev/null 2>&1
if [ $? -ne 0 ] ; then
		echo -e -n "${RED}"
		echo "Missing QEMU: $QEMU "
		echo "On Ubuntu/Debian, you can usually install it this way:"
		echo "  $ sudo apt-get install qemu-system-x86"
		echo -e -n "${NOCOLOR}"
    exit 1
fi
echo " + found $QEMU"

#======================================================================
# We will need to compile for the architecture i386
# First, we need to check that the architecture is allowed for dpkg.
# Then we need to check if multilib support has been installed for gcc.
#
# Nota Bene: if this section does not work for your distribution of Linux
#======================================================================

echo "Checking i386 support..."
dpkg --print-architecture | grep i386 >> /dev/null 2>&1
if [ $? -ne 0 ] ; then
  dpkg --print-foreign-architectures | grep i386 >> /dev/null 2>&1
  if [ $? -ne 0 ] ; then
			echo -e -n "${RED}"
			echo "FAILED."
			echo "  You need to allow for packages for the i386 architecture to be installed."
			echo "  Read the comment in the script below the line ${LINENO}"
			echo "  to have more information."

			# On Ubuntu or Debian:
			#
			#   $ sudo dpkg --add-architecture i386"
			#
			# You may want to look at 
		  #   https://wiki.debian.org/Multiarch/HOWTO"
			# Otherwise, Google is your best friend...
		echo -e -n "${NOCOLOR}"
    exit 1
  fi
fi
echo " + dpkg has support for the i386 architecture"

dpkg-query --search gcc*multilib  >> /dev/null 2>&1
if [ $? -ne 0 ] ; then
    echo -e -n "${RED}"			
		echo "FAILED."
		echo "  You are missing multilib support for gcc."
		echo "  Read the comment in the script below the line ${LINENO}"
		echo "  to have more information."

		# You can install it like this on Ubuntu/Debian:
    #   $ sudo apt-get install gcc-multilib"
		echo -e -n "${NOCOLOR}"
		exit 1
fi
echo " + gcc has multilib support"

