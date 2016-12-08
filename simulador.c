//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

typedef struct{
	int minute;
	int max_population;
	int start_time;
	int end_time;
	int capacity;
	int queue;
	int vip;
} s_simulator;
typedef struct{
	int id;
	int vip;
	int state;
	int arrival_time;
	int exit_time;
	int max_waiting_time;
} s_cliente;
/********************************* Global Variables **************************************/
int aquapark_open;
int attraction_open;
s_simulator simulator;
s_cliente cliente[267785];
/************************** Threads, Mutex & Semaphores **********************************/
pthread_t t_aquapark;
pthread_t t_swimming_pool;
pthread_t t_toboggan;
pthread_t t_race;
pthread_t t_sunbath;
pthread_t t_cliente[267785];
/*********************************** Functions *******************************************/
void * sunbath(){
	printf("[%s] The Solario is now open!\n", make_hours(simulator.minute));
	while(aquapark_open){
		// recives clients
	}
	printf("[%s] The Solario is now closed!\n", make_hours(simulator.minute));
}
void * swimming_pool(){
	printf("[%s] The Swimming Pool is now open!\n", make_hours(simulator.minute));
	while(aquapark_open){
		// recives clients
	}
	printf("[%s] The he Swimming Pool is now closed!\n", make_hours(simulator.minute));
}
void * toboggan(){ // leaves when 2 or 4 clients are ready waiting at least 3 minute for each departure
	printf("[%s] The tobogan is now open!\n", make_hours(simulator.minute));
	while(attraction_open){
		printf("[%s] The tobogan is ready to get more costumers!\n", make_hours(simulator.minute));
		//whaits for 2 costumres then departures
		printf("[%s] The tobogan is departing!\n", make_hours(simulator.minute));
		sleep(3);
		// waits a minute so the constumers get to the end
	}
	printf("[%s] The tobogan is now closed!\n", make_hours(simulator.minute));
}
void * race(){ // leves evary minute
	printf("[%s] The Race tobogan is now open!\n", make_hours(simulator.minute));
	while(attraction_open){
		printf("[%s] The Race tobogan is ready to get more costumers!\n", make_hours(simulator.minute));
		sleep(1);
		// waits a minute
		printf("[%s] The Race tobogan is departing!\n", make_hours(simulator.minute));
	}
	printf("[%s] The Race tobogan is now closed!\n", make_hours(simulator.minute));
}
int * trata_clientes(){

}
int * create_client(){
	int i;
	for(i=0; i<=simulator.max_population && simulator.minute < simulator.end_time; i++){
		if(i<simulator.max_population){
			if(pthread_create(&(t_cliente[i]), NULL ,(void *)&trata_clientes,NULL) != 0){
				printf("Error creating thread\n");
				exit(1);
			}
			printf("[%s] A person arrived to the Park entrance\n", make_hours(simulator.minute));
			sleep(2);
		}else printf("[%s] There is no more people living in Madeira\n", make_hours(simulator.minute));
	}
}
int * aquapark(){
	if(pthread_create(&(t_sunbath), NULL ,(void *)&sunbath,NULL) != 0){ //thread sunbath
		printf("Error creating thread\n");
		exit(1);
	}
	if(pthread_create(&(t_swimming_pool), NULL ,(void *)&swimming_pool,NULL) != 0){ //thread swimming pool
		printf("Error creating thread\n");
		exit(1);
	}
	if(pthread_create(&(t_toboggan), NULL ,(void *)&toboggan,NULL) != 0){ //thread toboggan
		printf("Error creating thread\n");
		exit(1);
	}
	if(pthread_create(&(t_race), NULL ,(void *)&race,NULL) != 0){ //thread race
		printf("Error creating thread\n");
		exit(1);
	}

	while(simulator.minute < (simulator.end_time)){
		if(((simulator.end_time)-30) == simulator.minute){
			printf("[%s] The Aquapark is closing in 30 minuts!\n", make_hours(simulator.minute));
			attraction_open=0;
			//closes in the next departure
			pthread_join(t_race , NULL);
			pthread_join(t_toboggan , NULL);
		}
		sleep(1);
		simulator.minute++;
	}
	aquapark_open = 0;

	// closes aquapark
	pthread_join(t_sunbath , NULL);
	pthread_join(t_swimming_pool , NULL);
	printf("[%s] The Aquapark is now closed!\n", make_hours(simulator.minute));
}
int main(int argc, char **argv){
	int *configuration_values = read_method(argc, argv[1]);

	DEBUG = configuration_values[0];

	simulator.max_population = configuration_values[1];
	simulator.start_time = configuration_values[2]*60;
	simulator.minute = simulator.start_time;
	simulator.end_time = configuration_values[3]*60;
	simulator.capacity = configuration_values[4];
	simulator.queue = configuration_values[5];
	simulator.vip = configuration_values[6];
	if(DEBUG) printf("max_population:%d\tstart_time:%d\tminute:%d\nend_time:%d\tcapacity:%d\tqueue:%d\tvip:%d\n", simulator.max_population,	simulator.start_time,simulator.minute,simulator.end_time,simulator.capacity,simulator.queue,simulator.vip);

/************************************ Socket **********************************************/
	int sockfd, newsockfd, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) printf("ERROR opening socket\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(1024);
	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) printf("ERROR on binding\n");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd<0) printf("ERROR on accept\n");
	bzero(buffer,256);

	n = read(newsockfd,buffer,255);
	if(n<0) printf("ERROR reading from socket\n");

	if(pthread_create(&(t_aquapark), NULL ,(void *)&aquapark,NULL) != 0){ //thread sunbath
		printf("Error creating thread\n");
		exit(1);
	}
	create_client();





	close(sockfd);
}
