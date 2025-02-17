/*
 * See:
 *   http://wiki.osdev.org/Printing_To_Screen
 *   http://wiki.osdev.org/Text_UI
 *
 * Note this example will always write to the top
 * line of the screen.
 * Note it assumes a color screen 0xB8000.
 * It also assumes the screen is in text mode,
 * and page-0 is displayed.
 * Screen is 80x25 (80 characters, 25 lines).
 *
 * For more info:
 *   http://wiki.osdev.org/VGA_Resources
 */

#include "main.h"

#define VIDEO_BUFFER_ADDRESS 0xB8000
static char *cursor = (char*)VIDEO_BUFFER_ADDRESS;
#define SCREEN_SIZE (25*80)

void video_write(int color, const char c) {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	if (offset>=2*SCREEN_SIZE)
		cursor = (char*)VIDEO_BUFFER_ADDRESS;
	*cursor++ = c;
	*cursor++ = color;
}

void video_write_string( int color, const char *string ) {
    while( *string != 0 )
			video_write(color, *string++);
}


void putchar(char c) {
	video_write(15, c);
	addCursorIndicator();
}

/*
 * WARNING: ignore this function until you are told to consider it.
 */
void printf(const char *fmt, ...) {
  /* http://www.pagetable.com/?p=298 */
  va_list ap;
  va_start(ap, fmt);
  kvprintf(fmt, putchar, 10, ap);
  va_end(ap);
}

void clearScreen() {
  char * startPoint = (char*)VIDEO_BUFFER_ADDRESS;
  for(int i = 0;i < SCREEN_SIZE*2; i++) {
	*startPoint++ = 0;
  }
  cursor = (char*)VIDEO_BUFFER_ADDRESS;
  addCursorIndicator();
}

void goLeft() {
	cursor -= 2;
}

void moveLeft() {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	if(offset - 2 < 0) return;
	shiftCursorIndicator(goLeft);
}

void goRight() {
	cursor += 2;
}

void moveRight() {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	if(offset + 2 >= 2*SCREEN_SIZE) return;
	shiftCursorIndicator(goRight);
}

void goUp() {
	cursor -= 80*2;
}

void moveUp() {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	if(offset < 2*80) return;
	shiftCursorIndicator(goUp);
}

void goDown() {
	cursor += 80*2;
}

void moveDown() {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	if(offset + 80*2 >= 2*SCREEN_SIZE) return;
	shiftCursorIndicator(goDown);
}

void delete() {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	int remainingBufferSize = SCREEN_SIZE*2 - (offset + 2);
	char *start = cursor;
	for(int i = 0; i < remainingBufferSize; i++){
		*cursor++ = *(cursor + 2);
	}
	*cursor = 0;
	*(cursor + 1) = 0;
	cursor = start;
	addCursorIndicator();
}

void backspace() {
	int offset = cursor - (char*)VIDEO_BUFFER_ADDRESS;
	if(offset >= 2) {
		shiftCursorIndicator(goLeft);
		delete();
	}
}

void addCursorIndicator(){
	*(++cursor) = 232; // TODO change color
  	cursor--;
}


void shiftCursorIndicator(void (*cursorAction)()){
	char bkColor = *(++cursor); // save cursor color
	*(cursor) = 15; // remove bk color (cursor)
  	cursor--; // reset position
	cursorAction();
	*(++cursor) = bkColor; // restor color (cursor)
	cursor--; // reset position
}