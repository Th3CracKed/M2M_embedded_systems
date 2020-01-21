/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Author: Olivier Gruber (olivier dot gruber at acm dot org)
*/

#define STACK_SIZE 8192

.section .text
.comm stack_top,STACK_SIZE,32

.align 4
.global crt0
crt0:
	# set up a stack
	leal	stack_top,%esp
	addl	$STACK_SIZE,%esp
	xorl	%ebp,%ebp

	# clear the processor flags
	pushl	$0
	popfl

  # zero-fill the uninitialized common symbols
  # (in the sections .bss).
	movl $_bbss, %edi
	xorl %eax, %eax
0:	movl %eax, (%edi)
	addl $4, %edi
	cmpl $_ebss, %edi
	jb	0b

  # upcall the C entry point.
	call kmain

  # in case the C entry point returns,
  # just hang the pocessor in never-ending loop.
hang:
	hlt
	jmp hang
