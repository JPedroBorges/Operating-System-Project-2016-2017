//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

int static sockfd;

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
    serv_addr.sin_port = htons(1024);
	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
		printf("ERROR connecting\n");
		return 0;
	}

	printf("press enter to start\n");
	bzero(buffer,256);
	//fgets(buffer,255,stdin);

	char enter;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }

	strcpy(buffer,"100");
	n = write(sockfd,buffer,strlen(buffer));




	while(1){
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if(n<0) printf("ERROR reading from socket\n");
		printf("%s\n",buffer);
	}





	close(sockfd);
}
