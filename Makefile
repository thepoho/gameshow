##### Makefile for GAMESHOW #####
## If building on rpi, ensure export HOSTTYPE is included in your .bashrc ##
######


CC=g++
CFLAGS=-Wall -std=c++0x -pthread

#DFLAGS=-D GAMESHOW_BUILD_RASPI -I/.wiring_pi/include -L/.wiring_pi/lib  -Wl,--start-group /.wiring_pi/lib/libwiringPi.so -Wl,--end-group -l
#DFLAGS=-D GAMESHOW_BUILD_RASPI -lwiringpi


ifeq ($(shell echo $(HOSTTYPE)), arm)
  DFLAGS=-D GAMESHOW_BUILD_RASPI -lwiringpi
endif

ARMCC=arm-linux-gnueabihf-g++
ARMDFLAGS=-D GAMESHOW_BUILD_RASPI -I./wiring_pi/include -L./wiring_pi/lib_arm  -Wl,--start-group ./wiring_pi/lib_arm/libWiringPi.so -Wl,--end-group

GAMEINCLUDE = 	./include
GAMESOURCE = 	./src/*.cpp ./src/*.c

#PINLIBINC = 	./pinlib/include
#PINLIBSRC = 	./pinlib/src/*.cpp 


#READLINESRC  =		./readline/*.c
#LIB = readline


#pinlib.o : $(PINLIBINC) $(PINLIBSRC)
#	$(CC) $(CFLAGS) -I $(PINLIBINC) $(PINLIBSRC)


gameshow :
	$(CC) $(CFLAGS) -D _DEBUG -D _LINUX $(DFLAGS) -iquote $(GAMEINCLUDE) $(GAMESOURCE) -o gameshow

arm : 
	$(ARMCC) $(CFLAGS) -D _DEBUG -D _LINUX $(ARMDFLAGS) -iquote $(GAMEINCLUDE) $(GAMESOURCE) -o gameshow_arm

arm_cc: 
	make arm && scp gameshow_arm pi@192.168.0.14:/home/pi/gs_arm && rsync -avz public_html pi@192.168.0.14:/home/pi/gs_arm && ssh 192.168.0.14 -lpi -t 'sudo /bin/bash -c "cd /home/pi/gs_arm && /home/pi/gs_arm/gameshow_arm"'


clean:
	$(RM) gameshow
clean_arm:
	$(RM) gameshow_arm

