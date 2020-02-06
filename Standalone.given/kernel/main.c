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

  addCursorIndicator();
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
      break;
    /* ctrl + x */
    case 24:
      kprintf("%c%c%c%c",27, 91, '2', 'J'); // Erase Screen
      kprintf("%c%c%s%s",27, 91,"24","F"); // Move Cursor To Top Left
      clearScreen(); // Move Cursor To Top Left
      break;
    /* Esc */ 
    case 27:
        /* [ */  
      moveCursor(c);
      break;
    /* Delete */
    case 126:
      kprintf("%c%c%c%c",27, 91, '1','P'); // delete
      delete();
      break;
    /* backSpace */
    case 127:
      kprintf("%c%c%c%c",27, 91, 68); // Go left
      // TODO check position change before and after going left to avoid deleting
      kprintf("%c%c%c%c",27, 91, '1','P'); // delete
      backspace();
      break;
    default:
      kprintf("%c",c);
      printf("%c", c);
      break;
    }
  }
}

void moveCursor() {
    if(serial_receive(COM1) == 91){
    char c = serial_receive(COM1);
    kprintf("%c%c%c",27, 91, c); // send correct arrow
    switch (c)
    {
    case 65:
      moveUp();
      break;
    case 66:
      moveDown();
      break;
    case 67:
      moveRight();
      break;
    case 68:
      // TODO qemu terminal move up when beggining of the line
      moveLeft();
      break;
    }
  }
}

/*

moveCursorToTopLeft(); // Erase Screen
eraseScreen(); // Move Cursor To Top Left
moveCursorToTopLeft();

void moveCursorToTopLeft() {
  unsigned int i = 0;
  for(int i = 0;i < 24; i++) {
    kprintf("%c",27);
    kprintf("%c",91);
    kprintf("%c",65);
  }
  for(i = 0;i < 80; i++) {
    kprintf("%c",27);
    kprintf("%c",91);
    kprintf("%c",68);
  }
}

void eraseScreen() {
  for(int i = 0; i < 24; i++) {
    for(int j = 0; j < 80; j++) {
      kprintf("%c",' ');
    }
  }
}
*/