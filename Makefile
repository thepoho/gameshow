#need to have libreadline-dev

CC=g++
CFLAGS=-Wall

GAMEINCLUDE = 	./game/include
GAMESOURCE = 	./game/src/*.cpp

PINLIBINC = 	./pinlib/include
PINLIBSRC = 	./pinlib/src/*.cpp 


#READLINESRC  =		./readline/*.c
LIB = readline


#pinlib.o : $(PINLIBINC) $(PINLIBSRC)
#	$(CC) $(CFLAGS) -I $(PINLIBINC) $(PINLIBSRC)

gameshow : $(GAMEINCLUDE) $(GAMESOURCE)
	$(CC) $(CFLAGS) -D _DEBUG -D _LINUX -iquote $(GAMEINCLUDE) -iquote $(PINLIBINC) $(PINLIBSRC) $(GAMESOURCE) -l${LIB}  -o main 

