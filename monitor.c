//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

int main(){
	printf("%s\n", "Running monitor");

	FILE *file_log = fopen("simulation.log", "w");
	fprintf(file_log,"-------------------------------Monitor Log-------------------------------\n");
	fclose(file_log);

	write_log(0,1,1);
	write_log(1,2,1);
	write_log(1,12,1);
	write_log(2,1,2);
	write_log(2,2,2);
	write_log(4,32,2);
	write_log(4,21,2);
	write_log(5,21,1);
}
