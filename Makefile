LUA ?= lua5.1

lua:
	cc -O3 -DISL_TERMBOX_IMPLEMENTATION -DISL_TERMBOX_LUA -I/usr/include/$(LUA) -c -Wall -Werror -fPIC -o termbox.o isl_termbox.c
	cc -O3 -shared -o termbox.so termbox.o
