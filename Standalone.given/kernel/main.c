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
	video_write_string(0x2a,"Console greetings!");
  serial_init(COM1);

	serial_send_string(COM1,"\n\rHello!\n\r\n");
  serial_send_string(COM1,"This is a simple echo console... please type something.\n\r\n\r");

  while(1) {
		int scancode;
    unsigned char c;
		c = serial_receive(COM1);
    //kprintf("[%c] %d \n",c,(int)c);
    
    switch (c)
    {
    /* Enter */
    case 13:
      kprintf("\n");
      // c2 = '\n';
      printf("\n");
      break;
    /* ctrl + x */
    case 24:
      eraseScreen();
      moveCursorToTopLeft();
      break;
    /* Esc */ 
    case 27:
        /* [ */  
      if(serial_receive(COM1) == 91){
        kprintf("%c%c%c",27, 91, serial_receive(COM1));
      }
      break;
    /* Delete */
    case 126:
      kprintf("%c%c%c%c",27, 91, '1','P');
      break;
    /* Delete */
    case 127:
      kprintf("%c%c%c%c",27, 91, 68); // Go left
      kprintf("%c%c%c%c",27, 91, '1','P');
      break;
    default:
      kprintf("%c",c);
      printf(&c);
      break;
    }
  }
}

void eraseScreen(){
  kprintf("%c%c%c%c",27, 91, '2', 'J');
}

void moveCursorToTopLeft(){
  kprintf("%c%c%s%s",27, 91,"24","F");
}
void kputchar(char c) {
  serial_send(COM1, c);
}
