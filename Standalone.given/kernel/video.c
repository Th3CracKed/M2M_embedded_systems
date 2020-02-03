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


/*
 * WARNING: ignore this function until you are told to consider it.
 */
void printf(const char *fmt, ...) {
	video_write_string(47, fmt);
}
