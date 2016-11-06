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
