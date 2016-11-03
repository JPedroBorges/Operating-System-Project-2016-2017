#*****************************************************************
#			Sistemas Operativos		- Projecto 2016/2017
# (●̮̮̃•̃)		João Borges				-
# /█\		Nuno Rodrigues			-
# .Π.		Vitor Paixão			-
#*****************************************************************

RUNMO = ./monitor
CC = gcc
CFLAGS = -g
LIBS = -lns -lnsl
LIBS = -lnsl -lpthread

all: clean monitor simulador

monitor: monitor.o util.o util_monitor.o
	$(CC) -g -o monitor monitor.o  util.o util_monitor.o $(LIBS)

simulador: simulador.o util.o util_simulador.o
	$(CC) -g -o simulador simulador.o util.o util_simulador.o $(LIBS)\

runm:
	gnome-terminal; clear;

clean:
	rm -f *.o *~ simulador
	rm -f *.o *~ monitor
