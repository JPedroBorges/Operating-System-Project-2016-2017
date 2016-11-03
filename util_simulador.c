//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

int * read_method(){
	int retorna [CONFIGURATION_PARAMS_NUMBER];
	FILE *configuration_file = fopen("configuration.cfg", "r");
	if(configuration_file == NULL){
		printf("Error: opening configuration file\n");
		return -1;
	}

	int configurations[CONFIGURATION_PARAMS_NUMBER];
	int value;
	char param[30];
	while(fscanf(configuration_file, "%s : %d", param, &value)!=EOF){
		printf("%s\n", param);
		if(!strcmp("simulation_time",param))retorna[0] = value;
		else if(!strcmp("simulation_population",param))retorna[1] = value;
		else if(!strcmp("aquapark_start",param))retorna[2] = value;
		else if(!strcmp("aquapark_close",param))retorna[3] = value;
		else if(!strcmp("aquapark_capacity",param))retorna[4] = value;
		else if(!strcmp("aquapark_queue",param))retorna[5] = value;
		else if(!strcmp("person_vip",param))retorna[6] = value;
		else if(!strcmp("person_max_waiting_time",param))retorna[7] = value;
		else if(!strcmp("family_chance",param))retorna[8] = value;
		else if(!strcmp("couple_chance",param))retorna[9] = value;
		else printf("Error: Not a valid configuration file\n");
	}

	fclose(configuration_file);
	return retorna;
}
