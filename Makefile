CC=g++
CFLAGS=-Wall -std=c++0x -pthread

ifeq ($(shell echo $(GAMESHOW_CROSSCOMPILE)), true)
  CC=arm-linux-gnueabihf-g++
  DFLAGS=-D GAMESHOW_BUILD_RASPI -I/home/poho/git/gameshow/arm_libraries/include -L/home/poho/git/gameshow/arm_libraries/lib  -Wl,--start-group /home/poho/git/gameshow/arm_libraries/lib/libWiringPi.so -Wl,--end-group
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

