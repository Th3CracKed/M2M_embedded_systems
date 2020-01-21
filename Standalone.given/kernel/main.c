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

#include "main.h"

int i=0;


void kmain(void) {
	
  serial_init(COM1);

	serial_send_string(COM1,"\n\rHello!\n\r\n");
  serial_send_string(COM1,"This is a simple echo console... please type something.\n\r\n\r");

  while(1) {
		int scancode;
    unsigned char c;
		c=serial_receive(COM1);
		if (c==13) {
			c = '\r';
			serial_send(COM1,c);
			c = '\n';
			serial_send(COM1,c);
		} else 
			serial_send(COM1,c);
  }
}
