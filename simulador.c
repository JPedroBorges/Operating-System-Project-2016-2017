//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

int main(int argc, char **argv){

	int *configuration_values = read_method(argc, argv[1]);

	if(DEBUG){
		int i;
		for(int i=0;i<10;i++) printf("%d\n", configuration_values[i]);
	}
}
