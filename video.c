#include "video.h"
#define VGA_START_ADDRESS 0xb8000
#define COLUMNS 80
#define LINES 24
#define SCREEN_SIZE COLUMNS * LINES
#define PIXEL_MODE 15

static char * const video = (char *) (VGA_START_ADDRESS);
static int xpos, ypos;

void vga_cls() {
	int i = 0;
	for (i = 0; i < 2 * SCREEN_SIZE; i++) {
		video[i] = 0;
	}
	xpos = 0;
	ypos = 0;
}


void vga_putchar(int c) {
	if (c == '\n' || c == '\r') {
		newline: xpos = 0;
		ypos++;
		if (ypos >= LINES)
			ypos = 0;
		return;
	}

	*(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
	*(video + (xpos + ypos * COLUMNS) * 2 + 1) = PIXEL_MODE;

	xpos++;
	if (xpos >= COLUMNS)
		goto newline;
}

