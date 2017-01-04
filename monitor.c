//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

int static sockfd;
pthread_t t_monitor;
pthread_t t_reader;
int static simulation=0;
int static tab=0;
int static hour=0;
int static monitor_on=0;
int ola = 0;

int print_screen(int hour, int state, int client_id){
	if(simulation==0 && monitor_on==0) tab=0;
	printf("\n");
	print_header(tab,hour);
	print_body(tab);
	print_footer();
	printf("$");
}
int * reader(){
	// this should go to the reader at some point
	int choice;
	while(monitor_on){
		scanf("%d",&choice);
		switch(choice){
			case 1:
				tab=1;
				break;
			case 2:
				tab=2;
				break;
			case 3:
				tab=3;
				break;
			case 4:
				tab=4;
				break;
			case 5:
				simulation=0;
				monitor_on=0;
				break;
			default:
				tab = 6;
				break;
		}
		printf("\n");
		print_header(tab,hour);
		print_body(tab);
		print_footer();
		printf("$");
	}
}
int main(){
	srand(time(NULL));
	printf("%s\n", "Running monitor");

	FILE *file_log = fopen("simulation.log", "w");
	fprintf(file_log,"-------------------------------Monitor Log-------------------------------\n");
	fclose(file_log);

//adicionar ---------------------------- no final do ficheiro
/************************************ Socket *********************************************/
	int n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
    char buffer[256];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0) printf("ERROR opening socket\n");
	server = gethostbyname("localhost");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons((rand()%9999)+1024);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
		printf("ERROR connecting\n");
		return 0;
	}

	bzero(buffer,256);
	//fgets(buffer,255,stdin);

	print_screen(-1,0,0);
	char enter;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }

	strcpy(buffer,"100");
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,256);

	simulation=1;
	tab=1;
	monitor_on=1;

	if(pthread_create(&(t_reader), NULL ,(void *)&reader,NULL) != 0){ //thread sunbath
		printf("Error creating thread\n");
		exit(1);
	}

	while(simulation){
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if(n<0) printf("ERROR reading from socket\n");
		int* info = decode(buffer);
		if(info[1]==101) simulation=0;
		hour=info[0];
		save_info(info[0],info[1],info[2]);
		fill_realtimelog(info[0],info[1],info[2]);
		write_log(info[0],info[1],info[2]);
		print_screen(info[0],info[1],info[2]);
		//calc_stats();

	//	calc_stat_average_swimm();
	}

	pthread_join(t_reader , NULL);
	pthread_join(t_monitor , NULL);

	strcpy(buffer,"101");
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,256);

	close(sockfd);
	clear_memory();
}
