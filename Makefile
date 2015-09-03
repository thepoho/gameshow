CC=g++
CFLAGS=-Wall -std=c++0x -pthread

ifeq ($(HOSTTYPE), arm)
  DFLAGS=-D _RASPI -lwiringPi
endif

GAMEINCLUDE = 	./include
GAMESOURCE = 	./src/*.cpp ./src/*.c

#PINLIBINC = 	./pinlib/include
#PINLIBSRC = 	./pinlib/src/*.cpp 


#READLINESRC  =		./readline/*.c
#LIB = readline


#pinlib.o : $(PINLIBINC) $(PINLIBSRC)
#	$(CC) $(CFLAGS) -I $(PINLIBINC) $(PINLIBSRC)


gameshow : $(GAMEINCLUDE) $(GAMESOURCE)
	$(CC) $(CFLAGS) -D _DEBUG -D _LINUX $(DFLAGS) -iquote $(GAMEINCLUDE) $(GAMESOURCE) -o gameshow

clean:
	$(RM) gameshow

