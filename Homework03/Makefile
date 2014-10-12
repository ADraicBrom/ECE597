TOOLS_CFLAGS	:= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
		   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
		   -W -Wundef -Wmissing-prototypes
#
# Programs
#
all:	tempReader

tempReader:  tempReader.o gpio-utils.o
	$(CC) $(LDFLAGS) -o $@ $^

#etchasketch:	etchasketch.o gpio-utils.o
#	$(CC) $(LDFLAGS) -o $@ $^

#ncurses:	ncurses.c
#	gcc ncurses.c -lncurses -o ncurses

#
# Objects
#

%.o: %.c
	$(CC) $(CFLAGS) $(TOOLS_CFLAGS) -c $< -o $@

clean:
	rm gpio-utils.o tempReader.o tempReader
