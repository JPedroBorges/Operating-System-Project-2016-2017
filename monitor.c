//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

int static sockfd;
pthread_t t_monitor;
int static simulation=0;
int static tab=0;
int static hour=0;
int static monitor_on=0;

int * monitor(){
	if(simulation==0) tab=0;
	print_header(tab,-1);
	print_body(tab);
	print_footer();

	while(monitor_on==0){}
	while(tab!=5){
		print_header(tab,hour);
		print_body(tab);
		print_footer();
		tab=5;
	}
}
int main(){
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

	if(pthread_create(&(t_monitor), NULL ,(void *)&monitor,NULL) != 0){ //thread sunbath
		printf("Error creating thread\n");
		exit(1);
	}

	bzero(buffer,256);
	//fgets(buffer,255,stdin);

	char enter;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }

	strcpy(buffer,"100");
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,256);

	simulation=1;
	tab=1;
	monitor_on=1;

	while(simulation){
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if(n<0) printf("ERROR reading from socket\n");
		int* info = decode(buffer);
		if(info[1]==101) simulation=0;
		hour=info[0];
		write_decoder(info);
		write_log(info[0],info[1],info[2]);
	}

	pthread_join(t_monitor , NULL);

	strcpy(buffer,"101");
	n = write(sockfd,buffer,strlen(buffer));
	bzero(buffer,256);

	close(sockfd);
}
