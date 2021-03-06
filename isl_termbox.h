/* 
 isl_termbox - v1.4.0 - public domain library for writing text-based user interfaces
                        no warranty implied; use at your own risk

 author: Ilya Kolbin (iskolbin@gmail.com)
 url: github.com/iskolbin/isl_termbox

 This is single-header port of Termbox library by nsf (no.smile.face@gmail.com)
 https://github.com/nsf/termbox
	
 Original licenese taken from https://github.com/nsf/termbox/blob/master/COPYING

 (https://github.com/nsf/termbox) 
 Copyright (C) 2010-2013 nsf <no.smile.face@gmail.com>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 Includes wcwidth function implementation by mattn (mattn.jp@gmail.com)
 https://github.com/mattn/wcwidth.c

 License for wcwidth implementation is unknown

 Do this:
		#define ISL_TERMBOX_IMPLEMENTATION
 before you include this file in *one* C or C++ file to create the implementation.

 Also bindings for Lua 5.1+ is included, to include them use:
 		#define ISL_TERMBOX_LUA
 To build shared library for load in Lua you can use make, Makefile is included in
 the distribution, this will produce termbox.so, after that you can simply
		require('termbox') -- Lua 5.2

 LICENSE

 This software is dual-licensed to the public domain and under the following
 license: you are granted a perpetual, irrevocable license to copy, modify,
 publish, and distribute this file as you see fit.
*/

#ifndef ISL_INCLUDE_TERMBOX_H_
#define ISL_INCLUDE_TERMBOX_H_

#include <stdint.h>

/* for shared objects */
#ifdef ISLTB_STATIC
 #define SO_IMPORT static
#elif defined(ISLTB_SHARED)
 #if __GNUC__ >= 4
  #define SO_IMPORT __attribute__((visibility("default")))
 #else
  #error "You can build shared library only using GCC 4+"
 #endif
#else
 #define SO_IMPORT extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Key constants. See also struct tb_event's key field.
 *
 * These are a safe subset of terminfo keys, which exist on all popular
 * terminals. Termbox uses only them to stay truly portable.
 */
#define TB_KEY_F1               (0xFFFF-0)
#define TB_KEY_F2               (0xFFFF-1)
#define TB_KEY_F3               (0xFFFF-2)
#define TB_KEY_F4               (0xFFFF-3)
#define TB_KEY_F5               (0xFFFF-4)
#define TB_KEY_F6               (0xFFFF-5)
#define TB_KEY_F7               (0xFFFF-6)
#define TB_KEY_F8               (0xFFFF-7)
#define TB_KEY_F9               (0xFFFF-8)
#define TB_KEY_F10              (0xFFFF-9)
#define TB_KEY_F11              (0xFFFF-10)
#define TB_KEY_F12              (0xFFFF-11)
#define TB_KEY_INSERT           (0xFFFF-12)
#define TB_KEY_DELETE           (0xFFFF-13)
#define TB_KEY_HOME             (0xFFFF-14)
#define TB_KEY_END              (0xFFFF-15)
#define TB_KEY_PGUP             (0xFFFF-16)
#define TB_KEY_PGDN             (0xFFFF-17)
#define TB_KEY_ARROW_UP         (0xFFFF-18)
#define TB_KEY_ARROW_DOWN       (0xFFFF-19)
#define TB_KEY_ARROW_LEFT       (0xFFFF-20)
#define TB_KEY_ARROW_RIGHT      (0xFFFF-21)
#define TB_KEY_MOUSE_LEFT       (0xFFFF-22)
#define TB_KEY_MOUSE_RIGHT      (0xFFFF-23)
#define TB_KEY_MOUSE_MIDDLE     (0xFFFF-24)
#define TB_KEY_MOUSE_RELEASE    (0xFFFF-25)
#define TB_KEY_MOUSE_WHEEL_UP   (0xFFFF-26)
#define TB_KEY_MOUSE_WHEEL_DOWN (0xFFFF-27)

/* These are all ASCII code points below SPACE character and a BACKSPACE key. */
#define TB_KEY_CTRL_TILDE       0x00
#define TB_KEY_CTRL_2           0x00 /* clash with 'CTRL_TILDE' */
#define TB_KEY_CTRL_A           0x01
#define TB_KEY_CTRL_B           0x02
#define TB_KEY_CTRL_C           0x03
#define TB_KEY_CTRL_D           0x04
#define TB_KEY_CTRL_E           0x05
#define TB_KEY_CTRL_F           0x06
#define TB_KEY_CTRL_G           0x07
#define TB_KEY_BACKSPACE        0x08
#define TB_KEY_CTRL_H           0x08 /* clash with 'CTRL_BACKSPACE' */
#define TB_KEY_TAB              0x09
#define TB_KEY_CTRL_I           0x09 /* clash with 'TAB' */
#define TB_KEY_CTRL_J           0x0A
#define TB_KEY_CTRL_K           0x0B
#define TB_KEY_CTRL_L           0x0C
#define TB_KEY_ENTER            0x0D
#define TB_KEY_CTRL_M           0x0D /* clash with 'ENTER' */
#define TB_KEY_CTRL_N           0x0E
#define TB_KEY_CTRL_O           0x0F
#define TB_KEY_CTRL_P           0x10
#define TB_KEY_CTRL_Q           0x11
#define TB_KEY_CTRL_R           0x12
#define TB_KEY_CTRL_S           0x13
#define TB_KEY_CTRL_T           0x14
#define TB_KEY_CTRL_U           0x15
#define TB_KEY_CTRL_V           0x16
#define TB_KEY_CTRL_W           0x17
#define TB_KEY_CTRL_X           0x18
#define TB_KEY_CTRL_Y           0x19
#define TB_KEY_CTRL_Z           0x1A
#define TB_KEY_ESC              0x1B
#define TB_KEY_CTRL_LSQ_BRACKET 0x1B /* clash with 'ESC' */
#define TB_KEY_CTRL_3           0x1B /* clash with 'ESC' */
#define TB_KEY_CTRL_4           0x1C
#define TB_KEY_CTRL_BACKSLASH   0x1C /* clash with 'CTRL_4' */
#define TB_KEY_CTRL_5           0x1D
#define TB_KEY_CTRL_RSQ_BRACKET 0x1D /* clash with 'CTRL_5' */
#define TB_KEY_CTRL_6           0x1E
#define TB_KEY_CTRL_7           0x1F
#define TB_KEY_CTRL_SLASH       0x1F /* clash with 'CTRL_7' */
#define TB_KEY_CTRL_UNDERSCORE  0x1F /* clash with 'CTRL_7' */
#define TB_KEY_SPACE            0x20
#define TB_KEY_BACKSPACE2       0x7F
#define TB_KEY_CTRL_8           0x7F /* clash with 'BACKSPACE2' */

/* These are non-existing ones.
 *
 * #define TB_KEY_CTRL_1 clash with '1'
 * #define TB_KEY_CTRL_9 clash with '9'
 * #define TB_KEY_CTRL_0 clash with '0'
 */

/*
 * Alt modifier constant, see tb_event.mod field and tb_select_input_mode function.
 * Mouse-motion modifier
 */
#define TB_MOD_ALT    0x01
#define TB_MOD_MOTION 0x02

/* Colors (see struct tb_cell's fg and bg fields). */
#define TB_DEFAULT 0x00
#define TB_BLACK   0x01
#define TB_RED     0x02
#define TB_GREEN   0x03
#define TB_YELLOW  0x04
#define TB_BLUE    0x05
#define TB_MAGENTA 0x06
#define TB_CYAN    0x07
#define TB_WHITE   0x08

/* Attributes, it is possible to use multiple attributes by combining them
 * using bitwise OR ('|'). Although, colors cannot be combined. But you can
 * combine attributes and a single color. See also struct tb_cell's fg and bg
 * fields.
 */
#define TB_BOLD      0x0100
#define TB_UNDERLINE 0x0200
#define TB_REVERSE   0x0400

/* A cell, single conceptual entity on the terminal screen. The terminal screen
 * is basically a 2d array of cells. It has the following fields:
 *  - 'ch' is a unicode character
 *  - 'fg' foreground color and attributes
 *  - 'bg' background color and attributes
 */
struct tb_cell {
	uint32_t ch;
	uint16_t fg;
	uint16_t bg;
};

#define TB_EVENT_KEY    1
#define TB_EVENT_RESIZE 2
#define TB_EVENT_MOUSE  3

/* An event, single interaction from the user. The 'mod' and 'ch' fields are
 * valid if 'type' is TB_EVENT_KEY. The 'w' and 'h' fields are valid if 'type'
 * is TB_EVENT_RESIZE. The 'x' and 'y' fields are valid if 'type' is
 * TB_EVENT_MOUSE. The 'key' field is valid if 'type' is either TB_EVENT_KEY
 * or TB_EVENT_MOUSE. The fields 'key' and 'ch' are mutually exclusive; only
 * one of them can be non-zero at a time.
 */
struct tb_event {
	uint8_t type;
	uint8_t mod; /* modifiers to either 'key' or 'ch' below */
	uint16_t key; /* one of the TB_KEY_* constants */
	uint32_t ch; /* unicode character */
	int32_t w;
	int32_t h;
	int32_t x;
	int32_t y;
};

/* Error codes returned by tb_init(). All of them are self-explanatory, except
 * the pipe trap error. Termbox uses unix pipes in order to deliver a message
 * from a signal handler (SIGWINCH) to the main event reading loop. Honestly in
 * most cases you should just check the returned code as < 0.
 */
#define TB_TB_ENSUPPORTED_TERMINAL -1
#define TB_EFAILED_TO_OPEN_TTY   -2
#define TB_EPIPE_TRAP_ERROR      -3

/* Initializes the termbox library. This function should be called before any
 * other functions. Function tb_init is same as tb_init_file("/dev/tty").
 * After successful initialization, the library must be
 * finalized using the tb_shutdown() function.
 */
SO_IMPORT int tb_init(void);
SO_IMPORT int tb_init_file(const char* name);
SO_IMPORT int tb_init_fd(int inout);
SO_IMPORT void tb_shutdown(void);

/* Returns the size of the internal back buffer (which is the same as
 * terminal's window size in characters). The internal buffer can be resized
 * after tb_clear() or tb_present() function calls. Both dimensions have an
 * unspecified negative value when called before tb_init() or after
 * tb_shutdown().
 */
SO_IMPORT int tb_width(void);
SO_IMPORT int tb_height(void);

/* Clears the internal back buffer using TB_DEFAULT color or the
 * color/attributes set by tb_set_clear_attributes() function.
 */
SO_IMPORT void tb_clear(void);
SO_IMPORT void tb_set_clear_attributes(uint16_t fg, uint16_t bg);

/* Synchronizes the internal back buffer with the terminal. */
SO_IMPORT void tb_present(void);

#define TB_HIDE_CURSOR -1

/* Sets the position of the cursor. Upper-left character is (0, 0). If you pass
 * TB_HIDE_CURSOR as both coordinates, then the cursor will be hidden. Cursor
 * is hidden by default.
 */
SO_IMPORT void tb_set_cursor(int cx, int cy);

/* Changes cell's parameters in the internal back buffer at the specified
 * position.
 */
SO_IMPORT void tb_put_cell(int x, int y, const struct tb_cell *cell);
SO_IMPORT void tb_change_cell(int x, int y, uint32_t ch, uint16_t fg, uint16_t bg);

/* Copies the buffer from 'cells' at the specified position, assuming the
 * buffer is a two-dimensional array of size ('w' x 'h'), represented as a
 * one-dimensional buffer containing lines of cells starting from the top.
 *
 * (DEPRECATED: use tb_cell_buffer() instead and copy memory on your own)
 */
SO_IMPORT void tb_blit(int x, int y, int w, int h, const struct tb_cell *cells);

/* Returns a pointer to internal cell back buffer. You can get its dimensions
 * using tb_width() and tb_height() functions. The pointer stays valid as long
 * as no tb_clear() and tb_present() calls are made. The buffer is
 * one-dimensional buffer containing lines of cells starting from the top.
 */
SO_IMPORT struct tb_cell *tb_cell_buffer(void);

#define TB_INPUT_CURRENT 0 /* 000 */
#define TB_INPUT_ESC     1 /* 001 */
#define TB_INPUT_ALT     2 /* 010 */
#define TB_INPUT_MOUSE   4 /* 100 */

/* Sets the termbox input mode. Termbox has two input modes:
 * 1. Esc input mode.
 *    When ESC sequence is in the buffer and it doesn't match any known
 *    ESC sequence => ESC means TB_KEY_ESC.
 * 2. Alt input mode.
 *    When ESC sequence is in the buffer and it doesn't match any known
 *    sequence => ESC enables TB_MOD_ALT modifier for the next keyboard event.
 *
 * You can also apply TB_INPUT_MOUSE via bitwise OR operation to either of the
 * modes (e.g. TB_INPUT_ESC | TB_INPUT_MOUSE). If none of the main two modes
 * were set, but the mouse mode was, TB_INPUT_ESC mode is used. If for some
 * reason you've decided to use (TB_INPUT_ESC | TB_INPUT_ALT) combination, it
 * will behave as if only TB_INPUT_ESC was selected.
 *
 * If 'mode' is TB_INPUT_CURRENT, it returns the current input mode.
 *
 * Default termbox input mode is TB_INPUT_ESC.
 */
SO_IMPORT int tb_select_input_mode(int mode);

#define TB_OUTPUT_CURRENT   0
#define TB_OUTPUT_NORMAL    1
#define TB_OUTPUT_256       2
#define TB_OUTPUT_216       3
#define TB_OUTPUT_GRAYSCALE 4

/* Sets the termbox output mode. Termbox has three output options:
 * 1. TB_OUTPUT_NORMAL     => [1..8]
 *    This mode provides 8 different colors:
 *      black, red, green, yellow, blue, magenta, cyan, white
 *    Shortcut: TB_BLACK, TB_RED, ...
 *    Attributes: TB_BOLD, TB_UNDERLINE, TB_REVERSE
 *
 *    Example usage:
 *        tb_change_cell(x, y, '@', TB_BLACK | TB_BOLD, TB_RED);
 *
 * 2. TB_OUTPUT_256        => [0..256]
 *    In this mode you can leverage the 256 terminal mode:
 *    0x00 - 0x07: the 8 colors as in TB_OUTPUT_NORMAL
 *    0x08 - 0x0f: TB_* | TB_BOLD
 *    0x10 - 0xe7: 216 different colors
 *    0xe8 - 0xff: 24 different shades of grey
 *
 *    Example usage:
 *        tb_change_cell(x, y, '@', 184, 240);
 *        tb_change_cell(x, y, '@', 0xb8, 0xf0);
 *
 * 2. TB_OUTPUT_216        => [0..216]
 *    This mode supports the 3rd range of the 256 mode only.
 *    But you don't need to provide an offset.
 *
 * 3. TB_OUTPUT_GRAYSCALE  => [0..23]
 *    This mode supports the 4th range of the 256 mode only.
 *    But you dont need to provide an offset.
 *
 * Execute build/src/demo/output to see its impact on your terminal.
 *
 * If 'mode' is TB_OUTPUT_CURRENT, it returns the current output mode.
 *
 * Default termbox output mode is TB_OUTPUT_NORMAL.
 */
SO_IMPORT int tb_select_output_mode(int mode);

/* Wait for an event up to 'timeout' milliseconds and fill the 'event'
 * structure with it, when the event is available. Returns the type of the
 * event (one of TB_EVENT_* constants) or -1 if there was an error or 0 in case
 * there were no event during 'timeout' period.
 */
SO_IMPORT int tb_peek_event(struct tb_event *event, int timeout);

/* Wait for an event forever and fill the 'event' structure with it, when the
 * event is available. Returns the type of the event (one of TB_EVENT_*
 * constants) or -1 if there was an error.
 */
SO_IMPORT int tb_poll_event(struct tb_event *event);

/* Utility utf8 functions. */
#define TB_EOF -1
SO_IMPORT int tb_utf8_char_length(char c);
SO_IMPORT int tb_utf8_char_to_unicode(uint32_t *out, const char *c);
SO_IMPORT int tb_utf8_unicode_to_char(char *out, uint32_t c);

#ifdef __cplusplus
}
#endif

#endif // ISL_INCLUDE_TERMBOX_H_

#ifdef ISL_TERMBOX_IMPLEMENTATION

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <wchar.h>

struct bytebuffer {
	char *buf;
	int len;
	int cap;
};

static void bytebuffer_reserve(struct bytebuffer *b, int cap) {
	if (b->cap >= cap) {
		return;
	}

	// prefer doubling capacity
	if (b->cap * 2 >= cap) {
		cap = b->cap * 2;
	}

	char *newbuf = realloc(b->buf, cap);
	b->buf = newbuf;
	b->cap = cap;
}

static void bytebuffer_init(struct bytebuffer *b, int cap) {
	b->cap = 0;
	b->len = 0;
	b->buf = 0;

	if (cap > 0) {
		b->cap = cap;
		b->buf = malloc(cap); // just assume malloc works always
	}
}

static void bytebuffer_free(struct bytebuffer *b) {
	if (b->buf)
		free(b->buf);
}

static void bytebuffer_clear(struct bytebuffer *b) {
	b->len = 0;
}

static void bytebuffer_append(struct bytebuffer *b, const char *data, int len) {
	bytebuffer_reserve(b, b->len + len);
	memcpy(b->buf + b->len, data, len);
	b->len += len;
}

static void bytebuffer_puts(struct bytebuffer *b, const char *str) {
	bytebuffer_append(b, str, strlen(str));
}

static void bytebuffer_resize(struct bytebuffer *b, int len) {
	bytebuffer_reserve(b, len);
	b->len = len;
}

static void bytebuffer_flush(struct bytebuffer *b, int fd) {
	if (write(fd, b->buf, b->len))
		;
	bytebuffer_clear(b);
}

static void bytebuffer_truncate(struct bytebuffer *b, int n) {
	if (n <= 0)
		return;
	if (n > b->len)
		n = b->len;
	const int nmove = b->len - n;
	memmove(b->buf, b->buf+n, nmove);
	b->len -= n;
}

enum {
	T_ENTER_CA,
	T_EXIT_CA,
	T_SHOW_CURSOR,
	T_HIDE_CURSOR,
	T_CLEAR_SCREEN,
	T_SGR0,
	T_UNDERLINE,
	T_BOLD,
	T_BLINK,
	T_REVERSE,
	T_ENTER_KEYPAD,
	T_EXIT_KEYPAD,
	T_TB_ENTER_MOUSE,
	T_EXIT_MOUSE,
	T_FUNCS_NUM,
};

#define TB_ENTER_MOUSE_SEQ "\x1b[?1000h\x1b[?1002h\x1b[?1015h\x1b[?1006h"
#define TB_EXIT_MOUSE_SEQ "\x1b[?1006l\x1b[?1015l\x1b[?1002l\x1b[?1000l"

#define TB_ENSUPPORTED_TERM -1

// rxvt-256color
static const char *rxvt_256color_keys[] = {
	"\033[11~","\033[12~","\033[13~","\033[14~","\033[15~","\033[17~","\033[18~","\033[19~","\033[20~","\033[21~","\033[23~","\033[24~","\033[2~","\033[3~","\033[7~","\033[8~","\033[5~","\033[6~","\033[A","\033[B","\033[D","\033[C", 0
};
static const char *rxvt_256color_funcs[] = {
	"\0337\033[?47h", "\033[2J\033[?47l\0338", "\033[?25h", "\033[?25l", "\033[H\033[2J", "\033[m", "\033[4m", "\033[1m", "\033[5m", "\033[7m", "\033=", "\033>", TB_ENTER_MOUSE_SEQ, TB_EXIT_MOUSE_SEQ,
};

// Eterm
static const char *eterm_keys[] = {
	"\033[11~","\033[12~","\033[13~","\033[14~","\033[15~","\033[17~","\033[18~","\033[19~","\033[20~","\033[21~","\033[23~","\033[24~","\033[2~","\033[3~","\033[7~","\033[8~","\033[5~","\033[6~","\033[A","\033[B","\033[D","\033[C", 0
};
static const char *eterm_funcs[] = {
	"\0337\033[?47h", "\033[2J\033[?47l\0338", "\033[?25h", "\033[?25l", "\033[H\033[2J", "\033[m", "\033[4m", "\033[1m", "\033[5m", "\033[7m", "", "", "", "",
};

// screen
static const char *screen_keys[] = {
	"\033OP","\033OQ","\033OR","\033OS","\033[15~","\033[17~","\033[18~","\033[19~","\033[20~","\033[21~","\033[23~","\033[24~","\033[2~","\033[3~","\033[1~","\033[4~","\033[5~","\033[6~","\033OA","\033OB","\033OD","\033OC", 0
};
static const char *screen_funcs[] = {
	"\033[?1049h", "\033[?1049l", "\033[34h\033[?25h", "\033[?25l", "\033[H\033[J", "\033[m", "\033[4m", "\033[1m", "\033[5m", "\033[7m", "\033[?1h\033=", "\033[?1l\033>", TB_ENTER_MOUSE_SEQ, TB_EXIT_MOUSE_SEQ,
};

// rxvt-unicode
static const char *rxvt_unicode_keys[] = {
	"\033[11~","\033[12~","\033[13~","\033[14~","\033[15~","\033[17~","\033[18~","\033[19~","\033[20~","\033[21~","\033[23~","\033[24~","\033[2~","\033[3~","\033[7~","\033[8~","\033[5~","\033[6~","\033[A","\033[B","\033[D","\033[C", 0
};
static const char *rxvt_unicode_funcs[] = {
	"\033[?1049h", "\033[r\033[?1049l", "\033[?25h", "\033[?25l", "\033[H\033[2J", "\033[m\033(B", "\033[4m", "\033[1m", "\033[5m", "\033[7m", "\033=", "\033>", TB_ENTER_MOUSE_SEQ, TB_EXIT_MOUSE_SEQ,
};

// linux
static const char *linux_keys[] = {
	"\033[[A","\033[[B","\033[[C","\033[[D","\033[[E","\033[17~","\033[18~","\033[19~","\033[20~","\033[21~","\033[23~","\033[24~","\033[2~","\033[3~","\033[1~","\033[4~","\033[5~","\033[6~","\033[A","\033[B","\033[D","\033[C", 0
};
static const char *linux_funcs[] = {
	"", "", "\033[?25h\033[?0c", "\033[?25l\033[?1c", "\033[H\033[J", "\033[0;10m", "\033[4m", "\033[1m", "\033[5m", "\033[7m", "", "", "", "",
};

// xterm
static const char *xterm_keys[] = {
	"\033OP","\033OQ","\033OR","\033OS","\033[15~","\033[17~","\033[18~","\033[19~","\033[20~","\033[21~","\033[23~","\033[24~","\033[2~","\033[3~","\033OH","\033OF","\033[5~","\033[6~","\033OA","\033OB","\033OD","\033OC", 0
};
static const char *xterm_funcs[] = {
	"\033[?1049h", "\033[?1049l", "\033[?12l\033[?25h", "\033[?25l", "\033[H\033[2J", "\033(B\033[m", "\033[4m", "\033[1m", "\033[5m", "\033[7m", "\033[?1h\033=", "\033[?1l\033>", TB_ENTER_MOUSE_SEQ, TB_EXIT_MOUSE_SEQ,
};

static struct term {
	const char *name;
	const char **keys;
	const char **funcs;
} terms[] = {
	{"rxvt-256color", rxvt_256color_keys, rxvt_256color_funcs},
	{"Eterm", eterm_keys, eterm_funcs},
	{"screen", screen_keys, screen_funcs},
	{"rxvt-unicode", rxvt_unicode_keys, rxvt_unicode_funcs},
	{"linux", linux_keys, linux_funcs},
	{"xterm", xterm_keys, xterm_funcs},
	{0, 0, 0},
};

static bool init_from_terminfo = false;
static const char **keys;
static const char **funcs;

static int try_compatible(const char *term, const char *name,
			  const char **tkeys, const char **tfuncs)
{
	if (strstr(term, name)) {
		keys = tkeys;
		funcs = tfuncs;
		return 0;
	}

	return TB_ENSUPPORTED_TERM;
}

static int init_term_builtin(void)
{
	int i;
	const char *term = getenv("TERM");

	if (term) {
		for (i = 0; terms[i].name; i++) {
			if (!strcmp(terms[i].name, term)) {
				keys = terms[i].keys;
				funcs = terms[i].funcs;
				return 0;
			}
		}

		/* let's do some heuristic, maybe it's a compatible terminal */
		if (try_compatible(term, "xterm", xterm_keys, xterm_funcs) == 0)
			return 0;
		if (try_compatible(term, "rxvt", rxvt_unicode_keys, rxvt_unicode_funcs) == 0)
			return 0;
		if (try_compatible(term, "linux", linux_keys, linux_funcs) == 0)
			return 0;
		if (try_compatible(term, "Eterm", eterm_keys, eterm_funcs) == 0)
			return 0;
		if (try_compatible(term, "screen", screen_keys, screen_funcs) == 0)
			return 0;
		/* let's assume that 'cygwin' is xterm compatible */
		if (try_compatible(term, "cygwin", xterm_keys, xterm_funcs) == 0)
			return 0;
	}

	return TB_ENSUPPORTED_TERM;
}

//----------------------------------------------------------------------
// terminfo
//----------------------------------------------------------------------

static char *read_file(const char *file) {
	FILE *f = fopen(file, "rb");
	if (!f)
		return 0;

	struct stat st;
	if (fstat(fileno(f), &st) != 0) {
		fclose(f);
		return 0;
	}

	char *data = malloc(st.st_size);
	if (!data) {
		fclose(f);
		return 0;
	}

	if (fread(data, 1, st.st_size, f) != (size_t)st.st_size) {
		fclose(f);
		free(data);
		return 0;
	}

	fclose(f);
	return data;
}

static char *terminfo_try_path(const char *path, const char *term) {
	char tmp[4096];
	snprintf(tmp, sizeof(tmp), "%s/%c/%s", path, term[0], term);
	tmp[sizeof(tmp)-1] = '\0';
	char *data = read_file(tmp);
	if (data) {
		return data;
	}

	// fallback to darwin specific dirs structure
	snprintf(tmp, sizeof(tmp), "%s/%x/%s", path, term[0], term);
	tmp[sizeof(tmp)-1] = '\0';
	return read_file(tmp);
}

static char *load_terminfo(void) {
	char tmp[4096];
	const char *term = getenv("TERM");
	if (!term) {
		return 0;
	}

	// if TERMINFO is set, no other directory should be searched
	const char *terminfo = getenv("TERMINFO");
	if (terminfo) {
		return terminfo_try_path(terminfo, term);
	}

	// next, consider ~/.terminfo
	const char *home = getenv("HOME");
	if (home) {
		snprintf(tmp, sizeof(tmp), "%s/.terminfo", home);
		tmp[sizeof(tmp)-1] = '\0';
		char *data = terminfo_try_path(tmp, term);
		if (data)
			return data;
	}

	// next, TERMINFO_DIRS
	const char *dirs = getenv("TERMINFO_DIRS");
	if (dirs) {
		snprintf(tmp, sizeof(tmp), "%s", dirs);
		tmp[sizeof(tmp)-1] = '\0';
		char *dir = strtok(tmp, ":");
		while (dir) {
			const char *cdir = dir;
			if (strcmp(cdir, "") == 0) {
				cdir = "/usr/share/terminfo";
			}
			char *data = terminfo_try_path(cdir, term);
			if (data)
				return data;
			dir = strtok(0, ":");
		}
	}

	// fallback to /usr/share/terminfo
	return terminfo_try_path("/usr/share/terminfo", term);
}

#define TI_MAGIC 0432
#define TI_HEADER_LENGTH 12
#define TB_KEYS_NUM 22

static const char *terminfo_copy_string(char *data, int str, int table) {
	const int16_t off = *(int16_t*)(data + str);
	const char *src = data + table + off;
	int len = strlen(src);
	char *dst = malloc(len+1);
	strcpy(dst, src);
	return dst;
}

static const int16_t ti_funcs[] = {
	28, 40, 16, 13, 5, 39, 36, 27, 26, 34, 89, 88,
};

static const int16_t ti_keys[] = {
	66, 68 /* apparently not a typo; 67 is F10 for whatever reason */, 69,
	70, 71, 72, 73, 74, 75, 67, 216, 217, 77, 59, 76, 164, 82, 81, 87, 61,
	79, 83,
};

static int init_term(void) {
	int i;
	char *data = load_terminfo();
	if (!data) {
		init_from_terminfo = false;
		return init_term_builtin();
	}

	int16_t *header = (int16_t*)data;
	if ((header[1] + header[2]) % 2) {
		// old quirk to align everything on word boundaries
		header[2] += 1;
	}

	const int str_offset = TI_HEADER_LENGTH +
		header[1] + header[2] +	2 * header[3];
	const int table_offset = str_offset + 2 * header[4];

	keys = malloc(sizeof(const char*) * (TB_KEYS_NUM+1));
	for (i = 0; i < TB_KEYS_NUM; i++) {
		keys[i] = terminfo_copy_string(data,
			str_offset + 2 * ti_keys[i], table_offset);
	}
	keys[TB_KEYS_NUM] = 0;

	funcs = malloc(sizeof(const char*) * T_FUNCS_NUM);
	// the last two entries are reserved for mouse. because the table offset is
	// not there, the two entries have to fill in manually
	for (i = 0; i < T_FUNCS_NUM-2; i++) {
		funcs[i] = terminfo_copy_string(data,
			str_offset + 2 * ti_funcs[i], table_offset);
	}

	funcs[T_FUNCS_NUM-2] = TB_ENTER_MOUSE_SEQ;
	funcs[T_FUNCS_NUM-1] = TB_EXIT_MOUSE_SEQ;

	init_from_terminfo = true;
	free(data);
	return 0;
}

static void shutdown_term(void) {
	if (init_from_terminfo) {
		int i;
		for (i = 0; i < TB_KEYS_NUM; i++) {
			free((void*)keys[i]);
		}
		// the last two entries are reserved for mouse. because the table offset
		// is not there, the two entries have to fill in manually and do not
		// need to be freed.
		for (i = 0; i < T_FUNCS_NUM-2; i++) {
			free((void*)funcs[i]);
		}
		free(keys);
		free(funcs);
	}
}

// if s1 starts with s2 returns true, else false
// len is the length of s1
// s2 should be null-terminated
static bool starts_with(const char *s1, int len, const char *s2)
{
	int n = 0;
	while (*s2 && n < len) {
		if (*s1++ != *s2++)
			return false;
		n++;
	}
	return *s2 == 0;
}

static int parse_mouse_event(struct tb_event *event, const char *buf, int len) {
	if (len >= 6 && starts_with(buf, len, "\033[M")) {
		// X10 mouse encoding, the simplest one
		// \033 [ M Cb Cx Cy
		int b = buf[3] - 32;
		switch (b & 3) {
		case 0:
			if ((b & 64) != 0)
				event->key = TB_KEY_MOUSE_WHEEL_UP;
			else
				event->key = TB_KEY_MOUSE_LEFT;
			break;
		case 1:
			if ((b & 64) != 0)
				event->key = TB_KEY_MOUSE_WHEEL_DOWN;
			else
				event->key = TB_KEY_MOUSE_MIDDLE;
			break;
		case 2:
			event->key = TB_KEY_MOUSE_RIGHT;
			break;
		case 3:
			event->key = TB_KEY_MOUSE_RELEASE;
			break;
		default:
			return -6;
		}
		event->type = TB_EVENT_MOUSE; // TB_EVENT_KEY by default
		if ((b & 32) != 0)
			event->mod |= TB_MOD_MOTION;

		// the coord is 1,1 for upper left
		event->x = (uint8_t)buf[4] - 1 - 32;
		event->y = (uint8_t)buf[5] - 1 - 32;

		return 6;
	} else if (starts_with(buf, len, "\033[<") || starts_with(buf, len, "\033[")) {
		// xterm 1006 extended mode or urxvt 1015 extended mode
		// xterm: \033 [ < Cb ; Cx ; Cy (M or m)
		// urxvt: \033 [ Cb ; Cx ; Cy M
		int i, mi = -1, starti = -1;
		int isM, isU, s1 = -1, s2 = -1;
		int n1 = 0, n2 = 0, n3 = 0;

		for (i = 0; i < len; i++) {
			// We search the first (s1) and the last (s2) ';'
			if (buf[i] == ';') {
				if (s1 == -1)
					s1 = i;
				s2 = i;
			}

			// We search for the first 'm' or 'M'
			if ((buf[i] == 'm' || buf[i] == 'M') && mi == -1) {
				mi = i;
				break;
			}
		}
		if (mi == -1)
			return 0;

		// whether it's a capital M or not
		isM = (buf[mi] == 'M');

		if (buf[2] == '<') {
			isU = 0;
			starti = 3;
		} else {
			isU = 1;
			starti = 2;
		}

		if (s1 == -1 || s2 == -1 || s1 == s2)
			return 0;

		n1 = strtoul(&buf[starti], NULL, 10);
		n2 = strtoul(&buf[s1 + 1], NULL, 10);
		n3 = strtoul(&buf[s2 + 1], NULL, 10);
		
		if (isU)
			n1 -= 32;

		switch (n1 & 3) {
		case 0:
			if ((n1&64) != 0) {
				event->key = TB_KEY_MOUSE_WHEEL_UP;
			} else {
				event->key = TB_KEY_MOUSE_LEFT;
			}
			break;
		case 1:
			if ((n1&64) != 0) {
				event->key = TB_KEY_MOUSE_WHEEL_DOWN;
			} else {
				event->key = TB_KEY_MOUSE_MIDDLE;
			}
			break;
		case 2:
			event->key = TB_KEY_MOUSE_RIGHT;
			break;
		case 3:
			event->key = TB_KEY_MOUSE_RELEASE;
			break;
		default:
			return mi + 1;
		}

		if (!isM) {
			// on xterm mouse release is signaled by lowercase m
			event->key = TB_KEY_MOUSE_RELEASE;
		}

		event->type = TB_EVENT_MOUSE; // TB_EVENT_KEY by default
		if ((n1&32) != 0)
			event->mod |= TB_MOD_MOTION;

		event->x = (uint8_t)n2 - 1;
		event->y = (uint8_t)n3 - 1;

		return mi + 1;
	}

	return 0;
}

// convert escape sequence to event, and return consumed bytes on success (failure == 0)
static int parse_escape_seq(struct tb_event *event, const char *buf, int len)
{
	int mouse_parsed = parse_mouse_event(event, buf, len);

	if (mouse_parsed != 0)
		return mouse_parsed;

	// it's pretty simple here, find 'starts_with' match and return
	// success, else return failure
	int i;
	for (i = 0; keys[i]; i++) {
		if (starts_with(buf, len, keys[i])) {
			event->ch = 0;
			event->key = 0xFFFF-i;
			return strlen(keys[i]);
		}
	}
	return 0;
}

static bool extract_event(struct tb_event *event, struct bytebuffer *inbuf, int inputmode)
{
	const char *buf = inbuf->buf;
	const int len = inbuf->len;
	if (len == 0)
		return false;

	if (buf[0] == '\033') {
		int n = parse_escape_seq(event, buf, len);
		if (n != 0) {
			bool success = true;
			if (n < 0) {
				success = false;
				n = -n;
			}
			bytebuffer_truncate(inbuf, n);
			return success;
		} else {
			// it's not escape sequence, then it's ALT or ESC,
			// check inputmode
			if (inputmode&TB_INPUT_ESC) {
				// if we're in escape mode, fill ESC event, pop
				// buffer, return success
				event->ch = 0;
				event->key = TB_KEY_ESC;
				event->mod = 0;
				bytebuffer_truncate(inbuf, 1);
				return true;
			} else if (inputmode&TB_INPUT_ALT) {
				// if we're in alt mode, set ALT modifier to
				// event and redo parsing
				event->mod = TB_MOD_ALT;
				bytebuffer_truncate(inbuf, 1);
				return extract_event(event, inbuf, inputmode);
			}
			assert(!"never got here");
		}
	}

	// if we're here, this is not an escape sequence and not an alt sequence
	// so, it's a FUNCTIONAL KEY or a UNICODE character

	// first of all check if it's a functional key
	if ((unsigned char)buf[0] <= TB_KEY_SPACE ||
	    (unsigned char)buf[0] == TB_KEY_BACKSPACE2)
	{
		// fill event, pop buffer, return success */
		event->ch = 0;
		event->key = (uint16_t)buf[0];
		bytebuffer_truncate(inbuf, 1);
		return true;
	}

	// feh... we got utf8 here

	// check if there is all bytes
	if (len >= tb_utf8_char_length(buf[0])) {
		/* everything ok, fill event, pop buffer, return success */
		tb_utf8_char_to_unicode(&event->ch, buf);
		event->key = 0;
		bytebuffer_truncate(inbuf, tb_utf8_char_length(buf[0]));
		return true;
	}

	// event isn't recognized, perhaps there is not enough bytes in utf8
	// sequence
	return false;
}

struct cellbuf {
	int width;
	int height;
	struct tb_cell *cells;
};

#define TB_CELL(buf, x, y) (buf)->cells[(y) * (buf)->width + (x)]
#define TB_IS_CURSOR_HIDDEN(cx, cy) (cx == -1 || cy == -1)
#define TB_LAST_COORD_INIT -1

static struct termios orig_tios;

static struct cellbuf back_buffer;
static struct cellbuf front_buffer;
static struct bytebuffer output_buffer;
static struct bytebuffer input_buffer;

static int termw = -1;
static int termh = -1;

static int inputmode = TB_INPUT_ESC;
static int outputmode = TB_OUTPUT_NORMAL;

static int inout;
static int winch_fds[2];

static int lastx = TB_LAST_COORD_INIT;
static int lasty = TB_LAST_COORD_INIT;
static int cursor_x = -1;
static int cursor_y = -1;

static uint16_t background = TB_DEFAULT;
static uint16_t foreground = TB_DEFAULT;

static void write_cursor(int x, int y);
static void write_sgr(uint16_t fg, uint16_t bg);

static void cellbuf_init(struct cellbuf *buf, int width, int height);
static void cellbuf_resize(struct cellbuf *buf, int width, int height);
static void cellbuf_clear(struct cellbuf *buf);
static void cellbuf_free(struct cellbuf *buf);

static void update_size(void);
static void update_term_size(void);
static void send_attr(uint16_t fg, uint16_t bg);
static void send_char(int x, int y, uint32_t c);
static void send_clear(void);
static void sigwinch_handler(int xxx);
static int wait_fill_event(struct tb_event *event, struct timeval *timeout);

/* may happen in a different thread */
static volatile int buffer_size_change_request;

/* -------------------------------------------------------- */

int tb_init_fd(int inout_)
{
	inout = inout_;
	if (inout == -1) {
		return TB_EFAILED_TO_OPEN_TTY;
	}

	if (init_term() < 0) {
		close(inout);
		return TB_TB_ENSUPPORTED_TERMINAL;
	}

	if (pipe(winch_fds) < 0) {
		close(inout);
		return TB_EPIPE_TRAP_ERROR;
	}

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigwinch_handler;
	sa.sa_flags = 0;
	sigaction(SIGWINCH, &sa, 0);

	tcgetattr(inout, &orig_tios);

	struct termios tios;
	memcpy(&tios, &orig_tios, sizeof(tios));

	tios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
	tios.c_oflag &= ~OPOST;
	tios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tios.c_cflag &= ~(CSIZE | PARENB);
	tios.c_cflag |= CS8;
	tios.c_cc[VMIN] = 0;
	tios.c_cc[VTIME] = 0;
	tcsetattr(inout, TCSAFLUSH, &tios);

	bytebuffer_init(&input_buffer, 128);
	bytebuffer_init(&output_buffer, 32 * 1024);

	bytebuffer_puts(&output_buffer, funcs[T_ENTER_CA]);
	bytebuffer_puts(&output_buffer, funcs[T_ENTER_KEYPAD]);
	bytebuffer_puts(&output_buffer, funcs[T_HIDE_CURSOR]);
	send_clear();

	update_term_size();
	cellbuf_init(&back_buffer, termw, termh);
	cellbuf_init(&front_buffer, termw, termh);
	cellbuf_clear(&back_buffer);
	cellbuf_clear(&front_buffer);

	return 0;
}

int tb_init_file(const char* name){
	return tb_init_fd(open(name, O_RDWR));
}

int tb_init(void)
{
	return tb_init_file("/dev/tty");
}

void tb_shutdown(void)
{
	if (termw == -1) {
		fputs("tb_shutdown() should not be called twice.", stderr);
		abort();
	}

	bytebuffer_puts(&output_buffer, funcs[T_SHOW_CURSOR]);
	bytebuffer_puts(&output_buffer, funcs[T_SGR0]);
	bytebuffer_puts(&output_buffer, funcs[T_CLEAR_SCREEN]);
	bytebuffer_puts(&output_buffer, funcs[T_EXIT_CA]);
	bytebuffer_puts(&output_buffer, funcs[T_EXIT_KEYPAD]);
	bytebuffer_puts(&output_buffer, funcs[T_EXIT_MOUSE]);
	bytebuffer_flush(&output_buffer, inout);
	tcsetattr(inout, TCSAFLUSH, &orig_tios);

	shutdown_term();
	close(inout);
	close(winch_fds[0]);
	close(winch_fds[1]);

	cellbuf_free(&back_buffer);
	cellbuf_free(&front_buffer);
	bytebuffer_free(&output_buffer);
	bytebuffer_free(&input_buffer);
	termw = termh = -1;
}

/*
 * This is adapted part from https://github.com/mattn/wcwidth.c/blob/master/wcwidth.c
 * Original author is [mattn](mattn.jp@gmail.com)
 */

struct isltb__interval {
	long first;
	long last;
};

static int isltb__bisearch(wchar_t ucs, const struct isltb__interval *table, int max) {
	int min = 0;
	int mid;

	if (ucs < table[0].first || ucs > table[max].last)
		return 0;
	while (max >= min) {
		mid = (min + max) / 2;
		if (ucs > table[mid].last)
			min = mid + 1;
		else if (ucs < table[mid].first)
			max = mid - 1;
		else
			return 1;
	}

	return 0;
}

static int isltb__wcwidth(wchar_t ucs) {
	/* sorted list of non-overlapping intervals of non-spacing characters */
	static const struct isltb__interval combining[] = {
		{ 0x0300, 0x034E }, { 0x0360, 0x0362 }, { 0x0483, 0x0486 },
		{ 0x0488, 0x0489 }, { 0x0591, 0x05A1 }, { 0x05A3, 0x05B9 },
		{ 0x05BB, 0x05BD }, { 0x05BF, 0x05BF }, { 0x05C1, 0x05C2 },
		{ 0x05C4, 0x05C4 }, { 0x064B, 0x0655 }, { 0x0670, 0x0670 },
		{ 0x06D6, 0x06E4 }, { 0x06E7, 0x06E8 }, { 0x06EA, 0x06ED },
		{ 0x070F, 0x070F }, { 0x0711, 0x0711 }, { 0x0730, 0x074A },
		{ 0x07A6, 0x07B0 }, { 0x0901, 0x0902 }, { 0x093C, 0x093C },
		{ 0x0941, 0x0948 }, { 0x094D, 0x094D }, { 0x0951, 0x0954 },
		{ 0x0962, 0x0963 }, { 0x0981, 0x0981 }, { 0x09BC, 0x09BC },
		{ 0x09C1, 0x09C4 }, { 0x09CD, 0x09CD }, { 0x09E2, 0x09E3 },
		{ 0x0A02, 0x0A02 }, { 0x0A3C, 0x0A3C }, { 0x0A41, 0x0A42 },
		{ 0x0A47, 0x0A48 }, { 0x0A4B, 0x0A4D }, { 0x0A70, 0x0A71 },
		{ 0x0A81, 0x0A82 }, { 0x0ABC, 0x0ABC }, { 0x0AC1, 0x0AC5 },
		{ 0x0AC7, 0x0AC8 }, { 0x0ACD, 0x0ACD }, { 0x0B01, 0x0B01 },
		{ 0x0B3C, 0x0B3C }, { 0x0B3F, 0x0B3F }, { 0x0B41, 0x0B43 },
		{ 0x0B4D, 0x0B4D }, { 0x0B56, 0x0B56 }, { 0x0B82, 0x0B82 },
		{ 0x0BC0, 0x0BC0 }, { 0x0BCD, 0x0BCD }, { 0x0C3E, 0x0C40 },
		{ 0x0C46, 0x0C48 }, { 0x0C4A, 0x0C4D }, { 0x0C55, 0x0C56 },
		{ 0x0CBF, 0x0CBF }, { 0x0CC6, 0x0CC6 }, { 0x0CCC, 0x0CCD },
		{ 0x0D41, 0x0D43 }, { 0x0D4D, 0x0D4D }, { 0x0DCA, 0x0DCA },
		{ 0x0DD2, 0x0DD4 }, { 0x0DD6, 0x0DD6 }, { 0x0E31, 0x0E31 },
		{ 0x0E34, 0x0E3A }, { 0x0E47, 0x0E4E }, { 0x0EB1, 0x0EB1 },
		{ 0x0EB4, 0x0EB9 }, { 0x0EBB, 0x0EBC }, { 0x0EC8, 0x0ECD },
		{ 0x0F18, 0x0F19 }, { 0x0F35, 0x0F35 }, { 0x0F37, 0x0F37 },
		{ 0x0F39, 0x0F39 }, { 0x0F71, 0x0F7E }, { 0x0F80, 0x0F84 },
		{ 0x0F86, 0x0F87 }, { 0x0F90, 0x0F97 }, { 0x0F99, 0x0FBC },
		{ 0x0FC6, 0x0FC6 }, { 0x102D, 0x1030 }, { 0x1032, 0x1032 },
		{ 0x1036, 0x1037 }, { 0x1039, 0x1039 }, { 0x1058, 0x1059 },
		{ 0x1160, 0x11FF }, { 0x17B7, 0x17BD }, { 0x17C6, 0x17C6 },
		{ 0x17C9, 0x17D3 }, { 0x180B, 0x180E }, { 0x18A9, 0x18A9 },
		{ 0x200B, 0x200F }, { 0x202A, 0x202E }, { 0x206A, 0x206F },
		{ 0x20D0, 0x20E3 }, { 0x302A, 0x302F }, { 0x3099, 0x309A },
		{ 0xFB1E, 0xFB1E }, { 0xFE20, 0xFE23 }, { 0xFEFF, 0xFEFF },
		{ 0xFFF9, 0xFFFB }
	};

	/* test for 8-bit control characters */
	if (ucs == 0)
		return 0;
	if (ucs < 32 || (ucs >= 0x7f && ucs < 0xa0))
		return -1;

	/* binary search in table of non-spacing characters */
	if (isltb__bisearch(ucs, combining,
				sizeof(combining) / sizeof(struct isltb__interval) - 1))
		return 0;

	/* if we arrive here, ucs is not a combining or C0/C1 control character */

	return 1 +
		(ucs >= 0x1100 &&
		 (ucs <= 0x115f ||                    /* Hangul Jamo init. consonants */
			(ucs >= 0x2e80 && ucs <= 0xa4cf && (ucs & ~0x0011) != 0x300a &&
			 ucs != 0x303f) ||                  /* CJK ... Yi */
			(ucs >= 0xac00 && ucs <= 0xd7a3) || /* Hangul Syllables */
			(ucs >= 0xf900 && ucs <= 0xfaff) || /* CJK Compatibility Ideographs */
			(ucs >= 0xfe30 && ucs <= 0xfe6f) || /* CJK Compatibility Forms */
			(ucs >= 0xff00 && ucs <= 0xff5f) || /* Fullwidth Forms */
			(ucs >= 0xffe0 && ucs <= 0xffe6) ||
#ifndef _WIN32
			(ucs >= 0x20000 && ucs <= 0x2ffff)
#else
			0
#endif
		 ));
}

/* End of adapted part for wcwidth implementation */

void tb_present(void)
{
	int x,y,w,i;
	struct tb_cell *back, *front;

	/* invalidate cursor position */
	lastx = TB_LAST_COORD_INIT;
	lasty = TB_LAST_COORD_INIT;

	if (buffer_size_change_request) {
		update_size();
		buffer_size_change_request = 0;
	}

	for (y = 0; y < front_buffer.height; ++y) {
		for (x = 0; x < front_buffer.width; ) {
			back = &TB_CELL(&back_buffer, x, y);
			front = &TB_CELL(&front_buffer, x, y);
			w = isltb__wcwidth(back->ch);
			if (w < 1) w = 1;
			if (memcmp(back, front, sizeof(struct tb_cell)) == 0) {
				x += w;
				continue;
			}
			memcpy(front, back, sizeof(struct tb_cell));
			send_attr(back->fg, back->bg);
			if (w > 1 && x >= front_buffer.width - (w - 1)) {
				// Not enough room for wide ch, so send spaces
				for (i = x; i < front_buffer.width; ++i) {
					send_char(i, y, ' ');
				}
			} else {
				send_char(x, y, back->ch);
				for (i = 1; i < w; ++i) {
					front = &TB_CELL(&front_buffer, x + i, y);
					front->ch = 0;
					front->fg = back->fg;
					front->bg = back->bg;
				}
			}
			x += w;
		}
	}
	if (!TB_IS_CURSOR_HIDDEN(cursor_x, cursor_y))
		write_cursor(cursor_x, cursor_y);
	bytebuffer_flush(&output_buffer, inout);
}

void tb_set_cursor(int cx, int cy)
{
	if (TB_IS_CURSOR_HIDDEN(cursor_x, cursor_y) && !TB_IS_CURSOR_HIDDEN(cx, cy))
		bytebuffer_puts(&output_buffer, funcs[T_SHOW_CURSOR]);

	if (!TB_IS_CURSOR_HIDDEN(cursor_x, cursor_y) && TB_IS_CURSOR_HIDDEN(cx, cy))
		bytebuffer_puts(&output_buffer, funcs[T_HIDE_CURSOR]);

	cursor_x = cx;
	cursor_y = cy;
	if (!TB_IS_CURSOR_HIDDEN(cursor_x, cursor_y))
		write_cursor(cursor_x, cursor_y);
}

void tb_put_cell(int x, int y, const struct tb_cell *cell)
{
	if ((unsigned)x >= (unsigned)back_buffer.width)
		return;
	if ((unsigned)y >= (unsigned)back_buffer.height)
		return;
	TB_CELL(&back_buffer, x, y) = *cell;
}

void tb_change_cell(int x, int y, uint32_t ch, uint16_t fg, uint16_t bg)
{
	struct tb_cell c = {ch, fg, bg};
	tb_put_cell(x, y, &c);
}

void tb_blit(int x, int y, int w, int h, const struct tb_cell *cells)
{
	if (x + w < 0 || x >= back_buffer.width)
		return;
	if (y + h < 0 || y >= back_buffer.height)
		return;
	int xo = 0, yo = 0, ww = w, hh = h;
	if (x < 0) {
		xo = -x;
		ww -= xo;
		x = 0;
	}
	if (y < 0) {
		yo = -y;
		hh -= yo;
		y = 0;
	}
	if (ww > back_buffer.width - x)
		ww = back_buffer.width - x;
	if (hh > back_buffer.height - y)
		hh = back_buffer.height - y;

	int sy;
	struct tb_cell *dst = &TB_CELL(&back_buffer, x, y);
	const struct tb_cell *src = cells + yo * w + xo;
	size_t size = sizeof(struct tb_cell) * ww;

	for (sy = 0; sy < hh; ++sy) {
		memcpy(dst, src, size);
		dst += back_buffer.width;
		src += w;
	}
}

struct tb_cell *tb_cell_buffer(void)
{
	return back_buffer.cells;
}

int tb_poll_event(struct tb_event *event)
{
	return wait_fill_event(event, 0);
}

int tb_peek_event(struct tb_event *event, int timeout)
{
	struct timeval tv;
	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout - (tv.tv_sec * 1000)) * 1000;
	return wait_fill_event(event, &tv);
}

int tb_width(void)
{
	return termw;
}

int tb_height(void)
{
	return termh;
}

void tb_clear(void)
{
	if (buffer_size_change_request) {
		update_size();
		buffer_size_change_request = 0;
	}
	cellbuf_clear(&back_buffer);
}

int tb_select_input_mode(int mode)
{
	if (mode) {
		if ((mode & (TB_INPUT_ESC | TB_INPUT_ALT)) == 0)
			mode |= TB_INPUT_ESC;

		/* technically termbox can handle that, but let's be nice and show here
		   what mode is actually used */
		if ((mode & (TB_INPUT_ESC | TB_INPUT_ALT)) == (TB_INPUT_ESC | TB_INPUT_ALT))
			mode &= ~TB_INPUT_ALT;

		inputmode = mode;
		if (mode&TB_INPUT_MOUSE) {
			bytebuffer_puts(&output_buffer, funcs[T_TB_ENTER_MOUSE]);
			bytebuffer_flush(&output_buffer, inout);
		} else {
			bytebuffer_puts(&output_buffer, funcs[T_EXIT_MOUSE]);
			bytebuffer_flush(&output_buffer, inout);
		}
	}
	return inputmode;
}

int tb_select_output_mode(int mode)
{
	if (mode)
		outputmode = mode;
	return outputmode;
}

void tb_set_clear_attributes(uint16_t fg, uint16_t bg)
{
	foreground = fg;
	background = bg;
}

static const unsigned char utf8_length[256] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1
};

static const unsigned char utf8_mask[6] = {
	0x7F,
	0x1F,
	0x0F,
	0x07,
	0x03,
	0x01
};

int tb_utf8_char_length(char c)
{
	return utf8_length[(unsigned char)c];
}

int tb_utf8_char_to_unicode(uint32_t *out, const char *c)
{
	if (*c == 0)
		return TB_EOF;

	int i;
	unsigned char len = tb_utf8_char_length(*c);
	unsigned char mask = utf8_mask[len-1];
	uint32_t result = c[0] & mask;
	for (i = 1; i < len; ++i) {
		result <<= 6;
		result |= c[i] & 0x3f;
	}

	*out = result;
	return (int)len;
}

int tb_utf8_unicode_to_char(char *out, uint32_t c)
{
	int len = 0;
	int first;
	int i;

	if (c < 0x80) {
		first = 0;
		len = 1;
	} else if (c < 0x800) {
		first = 0xc0;
		len = 2;
	} else if (c < 0x10000) {
		first = 0xe0;
		len = 3;
	} else if (c < 0x200000) {
		first = 0xf0;
		len = 4;
	} else if (c < 0x4000000) {
		first = 0xf8;
		len = 5;
	} else {
		first = 0xfc;
		len = 6;
	}

	for (i = len - 1; i > 0; --i) {
		out[i] = (c & 0x3f) | 0x80;
		c >>= 6;
	}
	out[0] = c | first;

	return len;
}
/* -------------------------------------------------------- */

static int convertnum(uint32_t num, char* buf) {
	int i, l = 0;
	int ch;
	do {
		buf[l++] = '0' + (num % 10);
		num /= 10;
	} while (num);
	for(i = 0; i < l / 2; i++) {
		ch = buf[i];
		buf[i] = buf[l - 1 - i];
		buf[l - 1 - i] = ch;
	}
	return l;
}

#define WRITE_LITERAL(X) bytebuffer_append(&output_buffer, (X), sizeof(X)-1)
#define WRITE_INT(X) bytebuffer_append(&output_buffer, buf, convertnum((X), buf))

static void write_cursor(int x, int y) {
	char buf[32];
	WRITE_LITERAL("\033[");
	WRITE_INT(y+1);
	WRITE_LITERAL(";");
	WRITE_INT(x+1);
	WRITE_LITERAL("H");
}

static void write_sgr(uint16_t fg, uint16_t bg) {
	char buf[32];

	if (fg == TB_DEFAULT && bg == TB_DEFAULT)
		return;

	switch (outputmode) {
	case TB_OUTPUT_256:
	case TB_OUTPUT_216:
	case TB_OUTPUT_GRAYSCALE:
		WRITE_LITERAL("\033[");
		if (fg != TB_DEFAULT) {
			WRITE_LITERAL("38;5;");
			WRITE_INT(fg);
			if (bg != TB_DEFAULT) {
				WRITE_LITERAL(";");
			}
		}
		if (bg != TB_DEFAULT) {
			WRITE_LITERAL("48;5;");
			WRITE_INT(bg);
		}
		WRITE_LITERAL("m");
		break;
	case TB_OUTPUT_NORMAL:
	default:
		WRITE_LITERAL("\033[");
		if (fg != TB_DEFAULT) {
			WRITE_LITERAL("3");
			WRITE_INT(fg - 1);
			if (bg != TB_DEFAULT) {
				WRITE_LITERAL(";");
			}
		}
		if (bg != TB_DEFAULT) {
			WRITE_LITERAL("4");
			WRITE_INT(bg - 1);
		}
		WRITE_LITERAL("m");
		break;
	}
}

static void cellbuf_init(struct cellbuf *buf, int width, int height)
{
	buf->cells = (struct tb_cell*)malloc(sizeof(struct tb_cell) * width * height);
	assert(buf->cells);
	buf->width = width;
	buf->height = height;
}

static void cellbuf_resize(struct cellbuf *buf, int width, int height)
{
	if (buf->width == width && buf->height == height)
		return;

	int oldw = buf->width;
	int oldh = buf->height;
	struct tb_cell *oldcells = buf->cells;

	cellbuf_init(buf, width, height);
	cellbuf_clear(buf);

	int minw = (width < oldw) ? width : oldw;
	int minh = (height < oldh) ? height : oldh;
	int i;

	for (i = 0; i < minh; ++i) {
		struct tb_cell *csrc = oldcells + (i * oldw);
		struct tb_cell *cdst = buf->cells + (i * width);
		memcpy(cdst, csrc, sizeof(struct tb_cell) * minw);
	}

	free(oldcells);
}

static void cellbuf_clear(struct cellbuf *buf)
{
	int i;
	int ncells = buf->width * buf->height;

	for (i = 0; i < ncells; ++i) {
		buf->cells[i].ch = ' ';
		buf->cells[i].fg = foreground;
		buf->cells[i].bg = background;
	}
}

static void cellbuf_free(struct cellbuf *buf)
{
	free(buf->cells);
}

static void get_term_size(int *w, int *h)
{
	struct winsize sz;
	memset(&sz, 0, sizeof(sz));

	ioctl(inout, TIOCGWINSZ, &sz);

	if (w) *w = sz.ws_col;
	if (h) *h = sz.ws_row;
}

static void update_term_size(void)
{
	struct winsize sz;
	memset(&sz, 0, sizeof(sz));

	ioctl(inout, TIOCGWINSZ, &sz);

	termw = sz.ws_col;
	termh = sz.ws_row;
}

static void send_attr(uint16_t fg, uint16_t bg)
{
#define TB_LAST_ATTR_INIT 0xFFFF
	static uint16_t lastfg = TB_LAST_ATTR_INIT, lastbg = TB_LAST_ATTR_INIT;
	if (fg != lastfg || bg != lastbg) {
		bytebuffer_puts(&output_buffer, funcs[T_SGR0]);

		uint16_t fgcol;
		uint16_t bgcol;

		switch (outputmode) {
		case TB_OUTPUT_256:
			fgcol = fg & 0xFF;
			bgcol = bg & 0xFF;
			break;

		case TB_OUTPUT_216:
			fgcol = fg & 0xFF; if (fgcol > 215) fgcol = 7;
			bgcol = bg & 0xFF; if (bgcol > 215) bgcol = 0;
			fgcol += 0x10;
			bgcol += 0x10;
			break;

		case TB_OUTPUT_GRAYSCALE:
			fgcol = fg & 0xFF; if (fgcol > 23) fgcol = 23;
			bgcol = bg & 0xFF; if (bgcol > 23) bgcol = 0;
			fgcol += 0xe8;
			bgcol += 0xe8;
			break;

		case TB_OUTPUT_NORMAL:
		default:
			fgcol = fg & 0x0F;
			bgcol = bg & 0x0F;
		}

		if (fg & TB_BOLD)
			bytebuffer_puts(&output_buffer, funcs[T_BOLD]);
		if (bg & TB_BOLD)
			bytebuffer_puts(&output_buffer, funcs[T_BLINK]);
		if (fg & TB_UNDERLINE)
			bytebuffer_puts(&output_buffer, funcs[T_UNDERLINE]);
		if ((fg & TB_REVERSE) || (bg & TB_REVERSE))
			bytebuffer_puts(&output_buffer, funcs[T_REVERSE]);

		write_sgr(fgcol, bgcol);

		lastfg = fg;
		lastbg = bg;
	}
}

static void send_char(int x, int y, uint32_t c)
{
	char buf[7];
	int bw = tb_utf8_unicode_to_char(buf, c);
	if (x-1 != lastx || y != lasty)
		write_cursor(x, y);
	lastx = x; lasty = y;
	if(!c) buf[0] = ' '; // replace 0 with whitespace
	bytebuffer_append(&output_buffer, buf, bw);
}

static void send_clear(void)
{
	send_attr(foreground, background);
	bytebuffer_puts(&output_buffer, funcs[T_CLEAR_SCREEN]);
	if (!TB_IS_CURSOR_HIDDEN(cursor_x, cursor_y))
		write_cursor(cursor_x, cursor_y);
	bytebuffer_flush(&output_buffer, inout);

	/* we need to invalidate cursor position too and these two vars are
	 * used only for simple cursor positioning optimization, cursor
	 * actually may be in the correct place, but we simply discard
	 * optimization once and it gives us simple solution for the case when
	 * cursor moved */
	lastx = TB_LAST_COORD_INIT;
	lasty = TB_LAST_COORD_INIT;
}

static void sigwinch_handler(int xxx)
{
	(void) xxx;
	const int zzz = 1;
	if(write(winch_fds[1], &zzz, sizeof(int)))
		;
}

static void update_size(void)
{
	update_term_size();
	cellbuf_resize(&back_buffer, termw, termh);
	cellbuf_resize(&front_buffer, termw, termh);
	cellbuf_clear(&front_buffer);
	send_clear();
}

static int read_up_to(int n) {
	assert(n > 0);
	const int prevlen = input_buffer.len;
	bytebuffer_resize(&input_buffer, prevlen + n);

	int read_n = 0;
	while (read_n <= n) {
		ssize_t r = 0;
		if (read_n < n) {
			r = read(inout, input_buffer.buf + prevlen + read_n, n - read_n);
		}
#ifdef __CYGWIN__
		// While linux man for tty says when VMIN == 0 && VTIME == 0, read
		// should return 0 when there is nothing to read, cygwin's read returns
		// -1. Not sure why and if it's correct to ignore it, but let's pretend
		// it's zero.
		if (r < 0) r = 0;
#endif
		if (r < 0) {
			// EAGAIN / EWOULDBLOCK shouldn't occur here
			assert(errno != EAGAIN && errno != EWOULDBLOCK);
			return -1;
		} else if (r > 0) {
			read_n += r;
		} else {
			bytebuffer_resize(&input_buffer, prevlen + read_n);
			return read_n;
		}
	}
	assert(!"unreachable");
	return 0;
}

static int wait_fill_event(struct tb_event *event, struct timeval *timeout)
{
	// ;-)
#define TB_ENOUGH_DATA_FOR_PARSING 64
	fd_set events;
	memset(event, 0, sizeof(struct tb_event));

	// try to extract event from input buffer, return on success
	event->type = TB_EVENT_KEY;
	if (extract_event(event, &input_buffer, inputmode))
		return event->type;

	// it looks like input buffer is incomplete, let's try the short path,
	// but first make sure there is enough space
	int n = read_up_to(TB_ENOUGH_DATA_FOR_PARSING);
	if (n < 0)
		return -1;
	if (n > 0 && extract_event(event, &input_buffer, inputmode))
		return event->type;

	// n == 0, or not enough data, let's go to select
	while (1) {
		FD_ZERO(&events);
		FD_SET(inout, &events);
		FD_SET(winch_fds[0], &events);
		int maxfd = (winch_fds[0] > inout) ? winch_fds[0] : inout;
		int result = select(maxfd+1, &events, 0, 0, timeout);
		if (!result)
			return 0;

		if (FD_ISSET(inout, &events)) {
			event->type = TB_EVENT_KEY;
			n = read_up_to(TB_ENOUGH_DATA_FOR_PARSING);
			if (n < 0)
				return -1;

			if (n == 0)
				continue;

			if (extract_event(event, &input_buffer, inputmode))
				return event->type;
		}
		if (FD_ISSET(winch_fds[0], &events)) {
			event->type = TB_EVENT_RESIZE;
			int zzz = 0;
			if(read(winch_fds[0], &zzz, sizeof(int)))
				;
			buffer_size_change_request = 1;
			get_term_size(&event->w, &event->h);
			return TB_EVENT_RESIZE;
		}
	}
}


#endif // ISL_TERMBOX_IMPLEMENTATION

#ifdef ISL_TERMBOX_LUA

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#if (LUA_VERSION_NUM<=501)
#define LUA_TB_LUA_LEN(L,i) (lua_pushnumber((L),lua_objlen((L),(i))))
#define LUA_TB_LUAL_NEWLIB(L,l) (lua_newtable(L),luaL_register(L,NULL,l))
#else
#define LUA_TB_LUA_LEN(L,i) lua_len((L),(i))
#define LUA_TB_LUAL_NEWLIB(L,l) luaL_newlib((L),(l))
#endif

#ifdef ISL_TERMBOX_DYNAMIC_LIB
#include <lua.h>
#include <lauxlib.h>
#define LUA_LIB
#ifdef _WIN32
__declspec (dllexport)
#endif
#endif
int luaopen_termbox( lua_State *L );

struct lua_tb_State {
	struct tb_event event;
	const char TB_EVENT_KEY_[1];
	const char TB_EVENT_RESIZE_[1];
	const char TB_EVENT_MOUSE_[1];
};

static int lua_tb_init( lua_State *L ) {
	int err = tb_init();
	struct lua_tb_State *ltbstate;

	if ( err ) {
		lua_pushnil( L );
		lua_pushinteger( L, err );
		return 2;
	}

	if ( lua_gettop( L ) >= 1 ) {
		if ( lua_isnumber( L, 1 )) {
			uint16_t inputmode = (uint16_t) lua_tonumber( L, 1 );
			tb_select_input_mode( inputmode );
		}
	}

	if ( lua_gettop( L ) >= 2 ) {
		if ( lua_isnumber( L, 2 )) {
			uint16_t ouputmode = (uint16_t) lua_tonumber( L, 2 );
			tb_select_output_mode( ouputmode );
		}
	}

	lua_pushlightuserdata( L, L );
	ltbstate = lua_newuserdata( L, sizeof *ltbstate );
	lua_settable( L, LUA_REGISTRYINDEX );

	return 0;
}

static int lua_tb_shutdown( lua_State *L ) {
	tb_shutdown();
	return 0;
}

static int lua_tb_width( lua_State *L ) {
	lua_pushinteger( L, tb_width());
	return 1;
}

static int lua_tb_height( lua_State *L ) {
	lua_pushinteger( L, tb_height());
	return 1;
}

static int lua_tb_clear( lua_State *L ) {
	if ( lua_gettop( L ) >= 2) {
		uint16_t fg = luaL_checkint( L, 1 ), bg = luaL_checkint( L, 2 );
		tb_set_clear_attributes( fg, bg );
	}
	tb_clear();
	return 0;
}

static int lua_tb_present( lua_State *L ) {
	tb_present();
	return 0;
}

static int lua_tb_set_cursor( lua_State *L ) {
	tb_set_cursor( luaL_checkint( L, 1 ), luaL_checkint( L, 2 ));
	return 0;
}

static int lua_tb_set_cell( lua_State *L ) {
	int x = luaL_checkint( L, 1 ), y = luaL_checkint( L, 2 ), len = 0;
	const char *str = luaL_checkstring( L, 3 );
	uint16_t fg = lua_isnumber( L, 4 ) ? lua_tonumber( L, 4 ) : TB_DEFAULT;
	uint16_t bg = lua_isnumber( L, 5 ) ? lua_tonumber( L, 5 ) : TB_DEFAULT;
	while ( *str ) {
		uint32_t uni;
		str += tb_utf8_char_to_unicode( &uni, str );
		tb_change_cell( x++, y, uni, fg, bg );
		len++;
	}
	lua_pushinteger( L, len );
	return 1;
}

static int lua_tb_select_input_mode( lua_State *L ) {
	lua_pushinteger( L, tb_select_input_mode( luaL_checkint( L, 1 )));
	return 1;
}

static int lua_tb_select_output_mode( lua_State *L ) {
	lua_pushinteger( L, tb_select_output_mode( luaL_checkint( L, 1 )));
	return 1;
}

static int lua_tb_get_cell( lua_State *L ) {
	uint16_t x = luaL_checkint( L, 1 ), y = luaL_checkint( L, 2 );
	if (x < tb_width() && y < tb_height()) {
		struct tb_cell *cell = (tb_cell_buffer() + y * tb_width() + x);
		lua_pushinteger( L, cell->ch );
		lua_pushinteger( L, cell->fg );
		lua_pushinteger( L, cell->bg );
		return 3;
	} else {
		luaL_error( L, "coordinates out of bounds" );
		return 0;
	}
}

#define LUA_TB_CALL(event) \
	case event: \
lua_pushlightuserdata( L, (void *) &ltbstate->event ## _ ); \
lua_gettable( L, LUA_REGISTRYINDEX ); \
if ( lua_isfunction( L, -1 )) {

#define LUA_TB_RETURN(event,inV,outV) \
	if ( lua_pcall( L, (inV), (outV), 0) != 0 ) { \
		luaL_error( L, "error calling '%s': %s", # event, lua_tostring( L, -1 )); \
	} \
} \
return 0; \

static int lua_tb_peek_event( lua_State *L ) {
	int event_type = 0;
	struct lua_tb_State *ltbstate;
	struct tb_event *event_struct;

	lua_pushlightuserdata( L, L );
	lua_gettable( L, LUA_REGISTRYINDEX );
	ltbstate = lua_touserdata( L, -1 );
	event_struct = &ltbstate->event;
	if ( lua_isnumber( L, 1 ) ) {
		event_type = tb_peek_event( event_struct, (int) lua_tonumber( L, 1 ));
	} else {
		event_type = tb_poll_event( event_struct );
	}

	switch ( event_type ) {
		LUA_TB_CALL( TB_EVENT_KEY )
		if ( event_struct->ch ) {
			char buffer[8] = {0};
			tb_utf8_unicode_to_char( buffer, event_struct->ch );
			lua_pushstring( L, buffer );
			lua_pushinteger( L, event_struct->ch );
		} else {
			lua_pushstring( L, "" );
			lua_pushinteger( L, event_struct->key );
		}
		lua_pushinteger( L, event_struct->mod );
		LUA_TB_RETURN( TB_EVENT_KEY, 3, 0 )

		LUA_TB_CALL( TB_EVENT_RESIZE )
		lua_pushinteger( L, event_struct->w );
		lua_pushinteger( L, event_struct->h );
		LUA_TB_RETURN( TB_EVENT_RESIZE, 2, 0 )

		LUA_TB_CALL( TB_EVENT_MOUSE )
		lua_pushinteger( L, event_struct->x );
		lua_pushinteger( L, event_struct->y );
		lua_pushinteger( L, event_struct->key );
		LUA_TB_RETURN( TB_EVENT_MOUSE, 3, 0 )
	}

	return 0;
}

#undef LUA_TB_CALL
#undef LUA_TB_RETURN

#define LUA_TB_CALLBACK(event) \
	case event: { \
								lua_pushlightuserdata( L, (void *) &ltbstate->event ## _ ); \
								lua_pushvalue( L, 2 ); \
								lua_settable( L, LUA_REGISTRYINDEX ); \
								break; \
							}

static int lua_tb_set_callback( lua_State *L ) {
	int event_type;
	struct lua_tb_State *ltbstate;
	lua_pushlightuserdata( L, L );
	lua_gettable( L, LUA_REGISTRYINDEX );
	ltbstate = lua_touserdata( L, -1 );
	event_type = luaL_checkint( L, 1 );
	if ( lua_isfunction( L, 2 )) {
		switch ( event_type ) {
			LUA_TB_CALLBACK( TB_EVENT_KEY );
			LUA_TB_CALLBACK( TB_EVENT_RESIZE );
			LUA_TB_CALLBACK( TB_EVENT_MOUSE );
		}
	}
	return 0;
}

#undef LUA_TB_CALLBACK

#define LUA_TB_CONST(k,v) lua_pushinteger(L,(v)); lua_setfield(L,-2,(k))

static void lua_tb_const( lua_State *L ) {
	LUA_TB_CONST( "F1", TB_KEY_F1 );
	LUA_TB_CONST( "F2", TB_KEY_F2 );
	LUA_TB_CONST( "F3", TB_KEY_F3 );
	LUA_TB_CONST( "F4", TB_KEY_F4 );
	LUA_TB_CONST( "F5", TB_KEY_F5 );
	LUA_TB_CONST( "F6", TB_KEY_F6 );
	LUA_TB_CONST( "F7", TB_KEY_F7 );
	LUA_TB_CONST( "F8", TB_KEY_F8 );
	LUA_TB_CONST( "F9", TB_KEY_F9 );
	LUA_TB_CONST( "F10", TB_KEY_F10 );
	LUA_TB_CONST( "F11", TB_KEY_F11 );
	LUA_TB_CONST( "F12", TB_KEY_F12 );
	LUA_TB_CONST( "INSERT", TB_KEY_INSERT );
	LUA_TB_CONST( "DELETE", TB_KEY_DELETE );
	LUA_TB_CONST( "HOME", TB_KEY_HOME );
	LUA_TB_CONST( "END", TB_KEY_END );
	LUA_TB_CONST( "PGUP", TB_KEY_PGUP );
	LUA_TB_CONST( "PGDN", TB_KEY_PGDN );
	LUA_TB_CONST( "UP", TB_KEY_ARROW_UP );
	LUA_TB_CONST( "DOWN", TB_KEY_ARROW_DOWN );
	LUA_TB_CONST( "LEFT", TB_KEY_ARROW_LEFT );
	LUA_TB_CONST( "RIGHT", TB_KEY_ARROW_RIGHT );
	LUA_TB_CONST( "BACKSPACE", TB_KEY_BACKSPACE );
	LUA_TB_CONST( "BACKSPACE2", TB_KEY_BACKSPACE2 );
	LUA_TB_CONST( "ENTER", TB_KEY_ENTER );
	LUA_TB_CONST( "ESC", TB_KEY_ESC );
	LUA_TB_CONST( "SPACE", TB_KEY_SPACE );
	LUA_TB_CONST( "MOUSE_LEFT", TB_KEY_MOUSE_LEFT );
	LUA_TB_CONST( "MOUSE_RIGHT", TB_KEY_MOUSE_RIGHT );
	LUA_TB_CONST( "MOUSE_MIDDLE", TB_KEY_MOUSE_MIDDLE );
	LUA_TB_CONST( "MOUSE_RELEASE", TB_KEY_MOUSE_RELEASE );
	LUA_TB_CONST( "MOUSE_WHEEL_UP", TB_KEY_MOUSE_WHEEL_UP );
	LUA_TB_CONST( "MOUSE_WHEEL_DOWN", TB_KEY_MOUSE_WHEEL_DOWN );
	LUA_TB_CONST( "INPUT_CURRENT", TB_INPUT_CURRENT );
	LUA_TB_CONST( "INPUT_ESC", TB_INPUT_ESC );
	LUA_TB_CONST( "INPUT_ALT", TB_INPUT_ALT );
	LUA_TB_CONST( "INPUT_MOUSE", TB_INPUT_MOUSE );
	LUA_TB_CONST( "OUTPUT_CURRENT", TB_OUTPUT_CURRENT );
	LUA_TB_CONST( "OUTPUT_NORMAL", TB_OUTPUT_NORMAL );
	LUA_TB_CONST( "OUTPUT_256", TB_OUTPUT_256 );
	LUA_TB_CONST( "OUTPUT_216", TB_OUTPUT_216 );
	LUA_TB_CONST( "OUTPUT_GRAYSCALE", TB_OUTPUT_GRAYSCALE );
	LUA_TB_CONST( "EVENT_NONE", 0 );
	LUA_TB_CONST( "EVENT_KEY", TB_EVENT_KEY );
	LUA_TB_CONST( "EVENT_RESIZE", TB_EVENT_RESIZE );
	LUA_TB_CONST( "EVENT_MOUSE", TB_EVENT_MOUSE );
	LUA_TB_CONST( "DEFAULT", TB_DEFAULT);
	LUA_TB_CONST( "BLACK", TB_BLACK );
	LUA_TB_CONST( "RED", TB_RED);
	LUA_TB_CONST( "GREEN", TB_GREEN );
	LUA_TB_CONST( "YELLOW", TB_YELLOW );
	LUA_TB_CONST( "BLUE", TB_BLUE );
	LUA_TB_CONST( "MAGENTA", TB_MAGENTA );
	LUA_TB_CONST( "CYAN", TB_CYAN );
	LUA_TB_CONST( "WHITE", TB_WHITE );
	LUA_TB_CONST( "BOLD", TB_BOLD );
	LUA_TB_CONST( "UNDERLINE", TB_UNDERLINE );
	LUA_TB_CONST( "REVERSE", TB_REVERSE );
}

#undef LUA_TB_CONST

static const luaL_Reg lua_tblib[] = {
	{"init", lua_tb_init},
	{"shutdown", lua_tb_shutdown},
	{"present", lua_tb_present},
	{"width", lua_tb_width},
	{"height", lua_tb_height},
	{"clear", lua_tb_clear},
	{"setcell", lua_tb_set_cell},
	{"getcell", lua_tb_get_cell},
	{"selectinput", lua_tb_select_input_mode},
	{"selectoutput", lua_tb_select_output_mode},
	{"peek", lua_tb_peek_event},
	{"setcursor", lua_tb_set_cursor},
	{"setcallback", lua_tb_set_callback},
	{NULL, NULL},
};

#ifdef _WIN32
__declspec (dllexport)
#endif
int luaopen_termbox( lua_State *L ) {
	LUA_TB_LUAL_NEWLIB( L, lua_tblib );
	lua_tb_const( L );
	return 1;
}

#endif // ISL_TERMBOX_LUA
