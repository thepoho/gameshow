#need to have libreadline-dev

CC=g++
CFLAGS=-fpermissive

GAMEINCLUDE = 	./include
GAMESOURCE = 	./src/*.cpp

#PINLIBINC = 	./pinlib/include
#PINLIBSRC = 	./pinlib/src/*.cpp 


#READLINESRC  =		./readline/*.c
#LIB = readline


#pinlib.o : $(PINLIBINC) $(PINLIBSRC)
#	$(CC) $(CFLAGS) -I $(PINLIBINC) $(PINLIBSRC)


gameshow : $(GAMEINCLUDE) $(GAMESOURCE)
	$(CC) $(CFLAGS) -D _DEBUG -D _LINUX -D _RASPI -lwiringPi -iquote $(GAMEINCLUDE) $(GAMESOURCE) -o gameshow

clean:
	$(RM) gameshow

