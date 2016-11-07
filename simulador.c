//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

/************************** Threads, Mutex & Semaphores **********************************/
pthread_t t_swimming_pool;
pthread_t t_toboggan;
pthread_t t_race;
pthread_t t_sunbath;



void * sunbath(){
	printf("The Solario is now open!\n");
	sleep(20);
	//aquapark is closing
	printf("The Solario will close in 30 minuts!\n");
	sleep(10);
	//after 30 minuts
	printf("The Solario is now closed!\n");
}


void * swimming_pool(){
	printf("The Swimming Pool is now open!\n");
	sleep(20);
	//aquapark is closing
	printf("The he Swimming Pool will close in 30 minuts!\n");
	sleep(10);
	//after 30 minuts
	printf("The he Swimming Pool is now closed!\n");
}

void * toboggan(){ // leaves when 2 or 4 clients are ready waiting at least a minute for each departure
	printf("The tobogan is now open!\n");
;

	while(aquapark_open){
		printf("The tobogan is ready to get more costumers!\n");
		//whaits for 2 costumres then departures
		printf("The tobogan is departing!\n");	
		sleep(10);
		// waits a minute so the constumers get to the end 
	}
	printf("The tobogan is now closed!\n");
}

void * race(){ // leves evary minute
	printf("The Race tobogan is now open!\n");

	while(aquapark_open){
		printf("The Race tobogan is ready to get more costumers!\n");
		sleep(10);
		// waits a minute
		printf("The Race tobogan is departing!\n");	 
	}
	printf("The Race tobogan is now closed!\n");
}




int main(int argc, char **argv){

	int *configuration_values = read_method(argc, argv[1]);


	// Open the aquapark



	//thread sunbath
	if(pthread_create(&(t_sunbath), NULL ,(void *)&sunbath,NULL) != 0){
			printf("Erro na criacao da tarefa\n");
			exit(1);
		}

	//thread swimming pool
	if(pthread_create(&(t_swimming_pool), NULL ,(void *)&swimming_pool,NULL) != 0){
			printf("Error creating thread\n");
			exit(1);
		}

	//thread toboggan
	if(pthread_create(&(t_toboggan), NULL ,(void *)&toboggan,NULL) != 0){
			printf("Error creating thread\n");
			exit(1)
		}

	//thread race
	if(pthread_create(&(t_race), NULL ,(void *)&race,NULL) != 0){
			printf("Erro na criacao da tarefa\n");
			exit(1);
		}

}
