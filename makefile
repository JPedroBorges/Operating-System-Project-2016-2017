#*****************************************************************
#			Sistemas Operativos		- Projecto 2016/2017
# (●̮̮̃•̃)		João Borges				-
# /█\		Nuno Rodrigues			-
# .Π.		Vitor Paixão			-
#*****************************************************************
#x-terminal-emulator -e "bash -c $(RUNSI);bash"; clear; $(RUNMO);
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
	x-terminal-emulator -e "bash -c $(RUNSI);bash"; $(RUNMO);

clean:
	rm -f *.o *~ simulador
	rm -f *.o *~ monitor
