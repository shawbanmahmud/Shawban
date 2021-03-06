mes: mess.o wraplib.o wrapsock.o wrapstdio.o wrapunix.o tcp_listen.o error.o wrappthread.o writen.o readline.o
	cc -o mes mess.o wraplib.o wrapsock.o wrapstdio.o wrapunix.o error.o tcp_listen.o wrappthread.o writen.o readline.o -lpthread

mess.o: mess.c acc.h
	cc -c mess.c

wraplib.o: wraplib.c acc.h
	cc -c wraplib.c

wrapsock.o: wrapsock.c acc.h
	cc -c wrapsock.c

wrapstdio.o: wrapstdio.c acc.h
	cc -c wrapstdio.c

wrapunix.o: wrapunix.c acc.h
	cc -c wrapunix.c

tcp_listen.o: tcp_listen.c acc.h
	cc -c tcp_listen.c

error.o: error.c acc.h
	cc -c error.c

wrappthread.o: wrappthread.c acc.h
	cc -c wrappthread.c

writen.o: writen.c acc.h
	cc -c writen.c

readline.o: readline.c acc.h
	cc -c readline.c
