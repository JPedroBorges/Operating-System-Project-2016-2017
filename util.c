//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"

char * make_hours(int input){
	int hr = 0;
	int min = 0;
	static char string[5];
	while(input>0){
		if(input>=60){
			hr++;
			input=input-60;
		}
		if(input<60){
			min = input;
			input = -1;
		}
	}
	if(hr>=10) sprintf(string,"%d",hr);
	else sprintf(string,"0%d",hr);

	if(min>=10) sprintf(string,"%s:%d",string,min);
	else sprintf(string,"%s:0%d",string,min);

	return string;
}
void send_message(int sockfd, int hour, int state, int client_id){
	int i;
	char str[27];
	sprintf(str, "I got your message %d times", i);
	int n = write(sockfd,str,28);
	if(n<0) printf("ERROR writing to socket\n");
}
char * read_message(int newsockfd){
	char buffer[256];
	bzero(buffer,256);
	int n = read(newsockfd,buffer,255);
	if(n<0) printf("ERROR reading from socket\n");

	return buffer;
}
