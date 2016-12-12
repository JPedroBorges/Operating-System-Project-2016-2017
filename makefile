#*****************************************************************
#			Sistemas Operativos		- Projecto 2016/2017
# (●̮̮̃•̃)		João Borges				-
# /█\		Nuno Rodrigues			-
# .Π.		Vitor Paixão			-
#*****************************************************************

RUNMO = ./monitor
RUNSI = ./simulador
CC = gcc -o
CFLAGS = -g
LIBS = -lns -lnsl
LIBS = -lnsl -lpthread

all: clean monitor simulador runm

monitor: monitor.o util.o util_monitor.o
	$(CC) -g -o monitor monitor.o  util.o util_monitor.o $(LIBS)

simulador: simulador.o util.o util_simulador.o
	$(CC) -g -o simulador simulador.o util.o util_simulador.o $(LIBS)\

runm:
	x-terminal-emulator --geometry "5x5" -e "bash -c $(RUNSI);bash"; resize -s 37 80; clear; $(RUNMO);

clean:
	rm -f *.o *~ simulador
	rm -f *.o *~ monitor
