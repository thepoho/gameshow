CC=g++
CFLAGS=-Wall

ifeq ($(HOSTTYPE), arm)
  DFLAGS=-D _RASPI
endif

GAMEINCLUDE = 	./include
GAMESOURCE = 	./src/*.cpp

#PINLIBINC = 	./pinlib/include
#PINLIBSRC = 	./pinlib/src/*.cpp 


#READLINESRC  =		./readline/*.c
#LIB = readline


#pinlib.o : $(PINLIBINC) $(PINLIBSRC)
#	$(CC) $(CFLAGS) -I $(PINLIBINC) $(PINLIBSRC)


gameshow : $(GAMEINCLUDE) $(GAMESOURCE)
	$(CC) $(CFLAGS) -D _DEBUG -D _LINUX $(DFLAGS) -lwiringPi -iquote $(GAMEINCLUDE) $(GAMESOURCE) -o gameshow

clean:
	$(RM) gameshow

