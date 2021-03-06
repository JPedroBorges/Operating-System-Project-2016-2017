//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

typedef struct {
								int minute;
								int max_population;
								int start_time;
								int end_time;
								int capacity;
								int queue;
								int vip;
								int person_frequency;
								int max_waiting_time;
} s_simulator;
typedef struct {
								int id;
								int vip;
								int current_place;
								int duration;
								int arrival_time;
								int exit_time;

} s_cliente;

/********************************* Global Variables **************************************/

int static sockfd, newsockfd;
int static aquapark_open;
int static attraction_open;
int static clients_prio_tobogan;
int static clients_norm_tobogan;
s_simulator static simulator;
s_cliente static cliente[267785];
/************************** Threads, Mutex & Semaphores **********************************/
pthread_t t_aquapark;
//pthread_t t_swimming_pool;
pthread_t t_toboggan;
pthread_t t_race;
//pthread_t t_sunbath;
pthread_t t_cliente[267785];

sem_t s_aquapark;
sem_t s_pool;
sem_t s_client_tobogan;
sem_t s_client_tobogan_prio;
sem_t s_client_tobogan_no_prio;
sem_t s_tobogan;
sem_t s_end_tobogan;
sem_t s_mid_tobogan;
pthread_mutex_t t_tobogan;

pthread_mutex_t t_comunicate;
/*********************************** Functions *******************************************/
void sunbath( int id){
								//sends the information that the client entered to the sunbath
								pthread_mutex_lock(&t_comunicate);
								printf("[%s] The client %d arrived on the sunbath.\n",make_hours(simulator.minute),id);
								send_message(newsockfd,simulator.minute,5,id);
								usleep(150000);
								pthread_mutex_unlock(&t_comunicate);

								pthread_mutex_lock(&t_comunicate);
								printf("[%s] The client %d entered on the sunbath.\n",make_hours(simulator.minute),id);
								send_message(newsockfd,simulator.minute,15,id);
								usleep(150000);
								pthread_mutex_unlock(&t_comunicate);


								sleep(cliente[id].duration);
								//sends the information that the client exited to the sunbath
								pthread_mutex_lock(&t_comunicate);
								printf("[%s] The client %d went out of the sunbath.\n",make_hours(simulator.minute),id);
								send_message(newsockfd,simulator.minute,25,id);
								usleep(150000);
								pthread_mutex_unlock(&t_comunicate);
}
void swimming_pool( int id){
								//sends the information that the client is on the line to the swiming pool
								pthread_mutex_lock(&t_comunicate);
								printf("[%s] The client %d arrived to the swiming pool.\n",make_hours(simulator.minute),id);
								send_message(newsockfd,simulator.minute,2,id);
								usleep(150000);
								pthread_mutex_unlock(&t_comunicate);

								//waits in the line
								cliente[id].arrival_time = simulator.minute;
								sem_wait(&s_pool);
								if (simulator.max_waiting_time > (simulator.minute - cliente[id].arrival_time) && simulator.minute<=(simulator.end_time-30)) { // give up because of time
																//sends the information that the client entered to the swiming pool
																pthread_mutex_lock(&t_comunicate);
																printf("[%s] The client %d went to the swiming pool.\n",make_hours(simulator.minute),id);
																send_message(newsockfd,simulator.minute,12,id);
																usleep(150000);
																pthread_mutex_unlock(&t_comunicate);

																sleep(30);
																//sends the information that the client exited to the swiming pool
																pthread_mutex_lock(&t_comunicate);
																printf("[%s] The client %d went out of the swiming pool.\n",make_hours(simulator.minute),id);
																send_message(newsockfd,simulator.minute,22,id);
																usleep(150000);
																pthread_mutex_unlock(&t_comunicate);
								}else{
																pthread_mutex_lock(&t_comunicate);
																printf("[%s] The client %d  give up the swiming pool.\n",make_hours(simulator.minute),id);
																send_message(newsockfd,simulator.minute,32,id);
																usleep(150000);
																pthread_mutex_unlock(&t_comunicate);
								}

								sem_post(&s_pool);
}
void * toboggan(){              // leaves when 2 clients are ready for departure
								int i;

								printf("[%s] The tobogan is now open!\n", make_hours(simulator.minute));
								while(attraction_open) {

																printf("[%s] The tobogan is ready to get more costumers!\n", make_hours(simulator.minute));
																int number_inside = 0;

																while(number_inside<2) { //fills tobogan
																								sem_wait(&s_client_tobogan);
																								number_inside++;
																}
																if (simulator.minute < simulator.end_time) { // atractions closed)
																								pthread_mutex_lock(&t_tobogan);
																								//printf("clients_prio_tobogan %d\n", clients_prio_tobogan);
																								for (i = 0; i < number_inside; ++i) { // tells clients to start
																																if (clients_prio_tobogan>=1) {
																																								sem_post(&s_client_tobogan_prio);
																																								clients_prio_tobogan--;
																																}else{
																																								sem_post(&s_client_tobogan_no_prio);
																																								clients_norm_tobogan--;
																																}
																								}
																								pthread_mutex_unlock(&t_tobogan);

																								pthread_mutex_lock(&t_comunicate);
																								printf("[%s] The tobogan started.\n",make_hours(simulator.minute));
																								send_message(newsockfd,simulator.minute,43,1);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);

																								sleep(4); // duration of the tobogan

																								for (i = 0; i < number_inside; ++i) {
																																sem_post(&s_end_tobogan); //tells clients that where inside that it ended
																								}

																								pthread_mutex_lock(&t_comunicate);
																								printf("[%s] The tobogan ended.\n",make_hours(simulator.minute));
																								send_message(newsockfd,simulator.minute,53,1);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);
																}else{
																								for (i = 0; i <= number_inside; ++i) { // frees clients becous atraction has ended
																																sem_post(&s_end_tobogan);
																								}
																}
								}
								pthread_mutex_lock(&t_tobogan);
								for (i = 0; i <= clients_prio_tobogan; ++i) { // frees clients becous atraction has ended
																sem_post(&s_client_tobogan_prio);
								}
								for (i = 0; i <= clients_norm_tobogan; ++i) { // frees clients becous atraction has ended
																sem_post(&s_client_tobogan_no_prio);
								}
								pthread_mutex_unlock(&t_tobogan);
								printf("[%s] The tobogan is now closed!\n", make_hours(simulator.minute));
}
void * race(){ // leves evary minute
								/*printf("[%s] The Race tobogan is now open!\n", make_hours(simulator.minute));

								   while(attraction_open){
								   //printf("[%s] The Race tobogan is ready to get more costumers!\n", make_hours(simulator.minute));
								   sleep(1);
								   // waits a minute
								   //printf("[%s] The Race tobogan is departing!\n", make_hours(simulator.minute));
								   }
								   printf("[%s] The Race tobogan is now closed!\n", make_hours(simulator.minute));*/
}
void select_where_to_go(int id){
								// inicializes random
								time_t t;
								srand((unsigned) time(&t));
								//gets a random time to go if its needed
								cliente[id].duration = (rand() % 8) + 2; // tempo de duração dentro das atividades

								//selects where to go
								switch(cliente[id].current_place) {
								case 0:
								case 1:
																sunbath(id);
																break;
								case 2:
								case 3:
																cliente[id].arrival_time = simulator.minute;
																pthread_mutex_lock(&t_comunicate);
																printf("[%s] The client %d went to the tobogan. vip :%d \n",make_hours(simulator.minute),id,cliente[id].vip);
																send_message(newsockfd,simulator.minute,3,id);
																usleep(150000);
																pthread_mutex_unlock(&t_comunicate);

																pthread_mutex_lock(&t_tobogan);
																if (cliente[id].vip) {
																								clients_prio_tobogan++;
																}else{
																								clients_norm_tobogan++;
																}

																sem_post(&s_client_tobogan);

																if (cliente[id].vip) {
																								pthread_mutex_unlock(&t_tobogan);
																								sem_wait(&s_client_tobogan_prio);
																}
																else{
																								pthread_mutex_unlock(&t_tobogan);
																								sem_wait(&s_client_tobogan_no_prio);
																}
																if (simulator.max_waiting_time > (simulator.minute - cliente[id].arrival_time) && simulator.minute<=(simulator.end_time-30)) { // give up because of time

																								pthread_mutex_lock(&t_comunicate);
																								printf("[%s] The client %d is riding on the tobogan.\n",make_hours(simulator.minute),id);
																								send_message(newsockfd,simulator.minute,13,id);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);

																								sem_wait(&s_end_tobogan);

																								pthread_mutex_lock(&t_comunicate);
																								printf("[%s] The client %d  leaves the tobogan.\n",make_hours(simulator.minute),id);
																								send_message(newsockfd,simulator.minute,23,id);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);
																}else{
																								pthread_mutex_lock(&t_comunicate);
																								printf("[%s] The client %d  give up the tobogan.\n",make_hours(simulator.minute),id);
																								send_message(newsockfd,simulator.minute,33,id);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);
																}
																break;
								case 4:;
								case 5:
																//printf("[%s] The client %d went to the race tobogan.\n",make_hours(simulator.minute),id);
																//sleep(2);
																break;
								case 6:
								case 7:
																swimming_pool(id);
																break;

								case 8:
																break;
								default: printf("Error selecting whero to go.\n"); break;
								}

}

int * handle_client(int id){

								// inicializes random
								time_t t;
								srand((unsigned) time(&t));
								// function that gets a diferant than the previous number
								int getRandom(int max, int min){
																//srand((unsigned) time(&t));
																int myRandom = (rand() % max) + min;
																//printf("random\n" );
																if (cliente[id].current_place != myRandom) {
																								return myRandom;
																}
																else{
																								getRandom(max,min);
																}
								}

								pthread_mutex_lock(&t_comunicate);
								printf("[%s] ⚫ The client %d arrived to the Park entrance", make_hours(simulator.minute),id);
								send_message(newsockfd,simulator.minute,1,id);
								usleep(150000);
								pthread_mutex_unlock(&t_comunicate);


								if((rand() % 100)<simulator.vip) {
																cliente[id].vip = 1;
																printf(" and it is an VIP\n");
								}else {
																cliente[id].vip = 0;
																printf(" and it's not a VIP\n");
								}
								if (simulator.minute < simulator.end_time - 30) { // atractions closed
																// check ocupation
																cliente[id].arrival_time = simulator.minute;
																sem_wait(&s_aquapark);
																if (simulator.max_waiting_time > (simulator.minute - cliente[id].arrival_time)) { // give up because of time

																								pthread_mutex_lock(&t_comunicate);
																								send_message(newsockfd,simulator.minute,11,id);
																								printf("[%s] ⚫ The client %d entered the Park\n", make_hours(simulator.minute),id);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);
																								// enters aquapark
																								cliente[id].current_place = 0; // sunbath



																								for (; simulator.minute < simulator.end_time - 30; ) {
																																if (cliente[id].current_place < 8) {
																																								select_where_to_go(id);
																																								cliente[id].current_place = getRandom(9,1);
																																}else{
																																								//printf("[%s] The client %d wants to leave.\n",make_hours(simulator.minute),id);
																																								break;
																																}

																								}
																}else{
																								pthread_mutex_lock(&t_comunicate);
																								printf("[%s] The client %d  give up the Aquapark.\n",make_hours(simulator.minute),id);
																								send_message(newsockfd,simulator.minute,31,id);
																								usleep(150000);
																								pthread_mutex_unlock(&t_comunicate);
																}
																sem_post(&s_aquapark);

																pthread_mutex_lock(&t_comunicate);
																printf("[%s] The client %d went out of the Aquapark.\n",make_hours(simulator.minute),id);
																send_message(newsockfd,simulator.minute,21,id);
																usleep(150000);
																pthread_mutex_unlock(&t_comunicate);
								}else{
																pthread_mutex_lock(&t_comunicate);
																printf("[%s] The client %d went home the Aquapark was closed.\n",make_hours(simulator.minute),id);
																send_message(newsockfd,simulator.minute,31,id);
																usleep(150000);
																pthread_mutex_unlock(&t_comunicate);
								}
								return 0;
}
int create_client(){
								int i,number_clients=0;
								int finaltimeforarrival = simulator.end_time-30;
								time_t t;
								srand((unsigned) time(&t));

								for(i=1; i<=simulator.max_population && simulator.minute < finaltimeforarrival; i++) {

																if(i<simulator.max_population) {
																								int random = (rand()%100);
																								if(random>simulator.person_frequency) i--;
																								else{
																																if(pthread_create(&(t_cliente[i]), NULL,(void *)&handle_client,i) != 0) {
																																								printf("Error creating thread\n");
																																								exit(1);
																																}
																																number_clients++;
																								}
																}else printf("[%s] There is no more people living in Madeira\n", make_hours(simulator.minute));
																sleep(1);
								}
								return number_clients;
}
int * aquapark(){

								while(aquapark_open) {
																if(((simulator.end_time)-15) == simulator.minute) {
																								printf("[%s] The Aquapark is closing in 30 minuts!\n", make_hours(simulator.minute));
																								attraction_open=0;
																}
																usleep(400000);
																simulator.minute++;
								}

}
int main(int argc, char **argv){
								srand(time(NULL));

								int *configuration_values = read_method(argc, argv[1]);

								DEBUG = configuration_values[0];

								simulator.max_population = configuration_values[1];
								simulator.start_time = configuration_values[2]*60;
								simulator.minute = simulator.start_time;
								simulator.end_time = configuration_values[3]*60;
								simulator.capacity = configuration_values[4];
								simulator.queue = configuration_values[5];
								simulator.vip = configuration_values[6];
								simulator.max_waiting_time = configuration_values[7];
								simulator.person_frequency = configuration_values[8];
								if(DEBUG) printf("max_population:%d\tstart_time:%d\tminute:%d\nend_time:%d\tcapacity:%d\tqueue:%d\tvip:%d\n", simulator.max_population, simulator.start_time,simulator.minute,simulator.end_time,simulator.capacity,simulator.queue,simulator.vip);

								/****************************** Semaphores and mutex init ********************************/

								sem_init(&s_aquapark,0,simulator.capacity);
								sem_init(&s_pool,0,15);
								sem_init(&s_end_tobogan,0,0);
								sem_init(&s_client_tobogan,0,0);
								sem_init(&s_client_tobogan_prio,0,0);
								sem_init(&s_client_tobogan_no_prio,0,0);

								pthread_mutex_init(&t_comunicate,NULL);


								/**************************** Initializes global variables *******************************/
								aquapark_open = 1;
								attraction_open = 1;
								clients_norm_tobogan = 0;
								clients_prio_tobogan = 0;

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

								do {
																n = read(newsockfd,buffer,255);
																if(n<0) printf("ERROR reading from socket\n");
								} while(strcmp(buffer,"100"));

								printf("Simulation started\n");

								/*********************************** creates threads **********************************/

								if(pthread_create(&(t_aquapark), NULL,(void *)&aquapark,NULL) != 0) { //thread sunbath
																printf("Error creating thread\n");
																exit(1);
								}

								if(pthread_create(&(t_toboggan), NULL,(void *)&toboggan,NULL) != 0) { //thread toboggan
																printf("Error creating thread\n");
																exit(1);
								}

								/*if(pthread_create(&(t_race), NULL,(void *)&race,NULL) != 0) { //thread race
								        printf("Error creating thread\n");
								        exit(1);
								   }*/

								int created_clients = create_client();
								//printf("created_clients : %d\n",created_clients );

								//closes in the next departure
								//pthread_join(t_race , NULL);
								pthread_join(t_toboggan, NULL);
								//waits that all clients are over
								int i;
								for (i = 1; i < created_clients; ++i)
								{
																pthread_join(t_cliente[i], NULL); // falta ver isto
								}
								aquapark_open = 0;

								printf("[%s] The Aquapark is now closed!\n", make_hours(simulator.minute));

								pthread_mutex_lock(&t_comunicate);
								send_message(newsockfd,simulator.minute,101,-1);
								pthread_mutex_unlock(&t_comunicate);

								do {
																n = read(newsockfd,buffer,255);
																if(n<0) printf("ERROR reading from socket\n");
								} while(strcmp(buffer,"101"));

								close(sockfd);
}
