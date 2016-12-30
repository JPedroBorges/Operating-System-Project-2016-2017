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
	int current_place;
	int duration;
	int arrival_time;
	int exit_time;
	int max_waiting_time;
} s_cliente;
/********************************* Global Variables **************************************/

int static sockfd, newsockfd;
int static aquapark_open;
int static attraction_open;
s_simulator static simulator;
s_cliente static cliente[267785];
/************************** Threads, Mutex & Semaphores **********************************/
pthread_t t_aquapark;
pthread_t t_swimming_pool;
pthread_t t_toboggan;
pthread_t t_race;
pthread_t t_sunbath;
pthread_t t_cliente[267785];

sem_t s_aquapark;
sem_t s_pool;

pthread_mutex_t t_comunicate;
/*********************************** Functions *******************************************/
void sunbath( int id){
	//sends the information that the client entered to the sunbath
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,5,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
	printf("[%s] The client %d went to the sunbath.\n",make_hours(simulator.minute),id);
	sleep(cliente[id].duration);
	//sends the information that the client exited to the sunbath
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,25,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
}
void swimming_pool( int id){
	//sends the information that the client is on the line to the swiming pool
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,2,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
	//waits in the line
	sem_wait(&s_pool);
	//sends the information that the client entered to the swiming pool
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,12,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
	printf("[%s] The client %d went to the swiming pool.\n",make_hours(simulator.minute),id);
	sleep(cliente[id].duration);
	//sends the information that the client exited to the swiming pool
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,22,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
	sem_post(&s_pool);
}
void * toboggan(){ // leaves when 2 or 4 clients are ready waiting at least 3 minute for each departure
	printf("[%s] The tobogan is now open!\n", make_hours(simulator.minute));
	
	while(attraction_open){
		//printf("[%s] The tobogan is ready to get more costumers!\n", make_hours(simulator.minute));
		//whaits for 2 costumres then departures
		//printf("[%s] The tobogan is departing!\n", make_hours(simulator.minute));
		sleep(3);
		// waits a minute so the constumers get to the end
	}
	printf("[%s] The tobogan is now closed!\n", make_hours(simulator.minute));
}
void * race(){ // leves evary minute
	printf("[%s] The Race tobogan is now open!\n", make_hours(simulator.minute));
	
	while(attraction_open){
		//printf("[%s] The Race tobogan is ready to get more costumers!\n", make_hours(simulator.minute));
		sleep(1);
		// waits a minute
		//printf("[%s] The Race tobogan is departing!\n", make_hours(simulator.minute));
	}
	printf("[%s] The Race tobogan is now closed!\n", make_hours(simulator.minute));
}
void select_where_to_go(int id){
	// inicializes random
	time_t t;
	srand((unsigned) time(&t));
	//gets a random time to go if its needed
	cliente[id].duration = (rand() % 10) + 2;

	//selects where to go
	switch(cliente[id].current_place){
		case 0: 
		case 1: 
			swimming_pool(id);
			break;
		case 2:
		case 3:  
			printf("[%s] The client %d went to the tobogan.\n",make_hours(simulator.minute),id);
			break;
		case 4:
		case 5:
			printf("[%s] The client %d went to the race tobogan.\n",make_hours(simulator.minute),id);
			break;
		case 6:
		case 7: 
			sunbath(id);
			break;
		case 8: 
			printf("[%s] The client %d went out.\n",make_hours(simulator.minute),id);break;
		default: printf("Error selecting whero to go.\n");break;
	}
	sleep(2);
}

int * handle_client(int id){
	//inicialization of variables
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,1,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
	// check ocupation
	sem_wait(&s_aquapark);
	// enters aquapark
	cliente[id].current_place=7;
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,11,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);

	// inicializes random
	time_t t;
	srand((unsigned) time(&t));
	// function that gets a diferant than the previous number
	int getRandom(){
		int myRandom = (rand() % 9) + 1;
		if (cliente[id].current_place != myRandom){
			return myRandom;
		}
		else{
			getRandom();
		}
	}

	for (;simulator.minute < simulator.end_time - 15;){
		if (cliente[id].current_place <= 8){
			select_where_to_go(id);

			cliente[id].current_place = getRandom();
			printf("current current_place %d\n",cliente[id].current_place);
		}else{
			break;
		}
		
	}
	sem_post(&s_aquapark);
	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,21,id);
	usleep(300000);
	pthread_mutex_unlock(&t_comunicate);
	return 0;
}
int * create_client(){
	int i;
	int finaltimeforarrival = simulator.end_time-30;

	for(i=0; i<=simulator.max_population && simulator.minute < finaltimeforarrival; i++){
		if(i<simulator.max_population){
			if(pthread_create(&(t_cliente[i]), NULL ,(void *)&handle_client,i) != 0){
				printf("Error creating thread\n");
				exit(1);
			}
			printf("[%s] A person arrived to the Park entrance\n", make_hours(simulator.minute));
			sleep(1);
		}else printf("[%s] There is no more people living in Madeira\n", make_hours(simulator.minute));
	}
}
int * aquapark(){
	aquapark_open=1;
	attraction_open=1;

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
		}
		sleep(1);
		simulator.minute++;
	}
	aquapark_open = 0;
}
int main(int argc, char **argv){

	/***************************** Read configuration file ***********************************/
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

	/****************************** Semaphores and mutex init ********************************/

	sem_init(&s_aquapark,0,10);
	sem_init(&s_pool,0,3);

	pthread_mutex_init(&t_comunicate,NULL);
	
	/************************************ Socket *********************************************/
	int clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) printf("ERROR opening socket\n");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons((rand()%9999)+1024);
	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) printf("ERROR on binding\n");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd<0) printf("ERROR on accept\n");
	bzero(buffer,256);

	do{
		n = read(newsockfd,buffer,255);
		if(n<0) printf("ERROR reading from socket\n");
	}while(strcmp(buffer,"100"));

	printf("Simulation started\n");

	/*********************************** creates threads **********************************/

	if(pthread_create(&(t_aquapark), NULL ,(void *)&aquapark,NULL) != 0){ //thread sunbath
		printf("Error creating thread\n");
		exit(1);
	}

	create_client();

	//closes in the next departure
	pthread_join(t_race , NULL);
	pthread_join(t_toboggan , NULL);

	//pthread_join(t_cliente[] , NULL);  // falta ver isto
	// closes aquapark
	pthread_join(t_sunbath , NULL);
	pthread_join(t_swimming_pool , NULL);
	printf("[%s] The Aquapark is now closed!\n", make_hours(simulator.minute));

	pthread_mutex_lock(&t_comunicate);
	send_message(newsockfd,simulator.minute,101,-1);
	pthread_mutex_unlock(&t_comunicate);


	do{
		n = read(newsockfd,buffer,255);
		if(n<0) printf("ERROR reading from socket\n");
	}while(strcmp(buffer,"101"));

	close(sockfd);
}
