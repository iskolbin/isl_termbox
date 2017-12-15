lua:
	cp isl_termbox.h isl_termbox.c
	cc -O3 -DISL_TERMBOX_IMPLEMENTATION -DISL_TERMBOX_LUA -c -Wall -Werror -fPIC -o termbox.o isl_termbox.c
	cc -O3 -shared -o termbox.so termbox.o -llua
	rm termbox.o isl_termbox.c

lua51:
	cp isl_termbox.h isl_termbox.c
	cc -O3 -DISL_TERMBOX_IMPLEMENTATION -DISL_TERMBOX_LUA -I/usr/include/lua5.1 -c -Wall -Werror -fPIC -o termbox.o isl_termbox.c
	cc -O3 -shared -o termbox.so termbox.o
	rm termbox.o isl_termbox.c

lua52:
	cp isl_termbox.h isl_termbox.c
	cc -O3 -DISL_TERMBOX_IMPLEMENTATION -DISL_TERMBOX_LUA -I/usr/include/lua5.2 -c -Wall -Werror -fPIC -o termbox.o isl_termbox.c
	cc -O3 -shared -o termbox.so termbox.o
	rm termbox.o isl_termbox.c
