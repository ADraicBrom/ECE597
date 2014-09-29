TOOLS_CFLAGS	:= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
		   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
		   -W -Wundef -Wmissing-prototypes
#
# Programs
#
all:	Buttons-and-LEDs etchasketch

Buttons-and-LEDs:  Buttons-and-LEDs.o gpio-utils.o
	$(CC) $(LDFLAGS) -o $@ $^

etchasketch:	etchasketch.o gpio-utils.o
	$(CC) $(LDFLAGS) -o $@ $^

#ncurses:	ncurses.c
#	gcc ncurses.c -lncurses -o ncurses

#
# Objects
#

%.o: %.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

clean:
	rm gpio-utils.o etchasketch.o Buttons-and-LEDs.o Buttons-and-LEDs etchasketch
