//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"
int max_person_aqua = 10000;
int max_person_pool = 100;

int real_time_log[24][3]={{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
void fill_realtimelog(int hour, int state, int client_id){
	int i;
	for(i=24;i>1;i--){
		real_time_log[(i-1)][0]=real_time_log[i][0];
		real_time_log[(i-1)][1]=real_time_log[i][1];
		real_time_log[(i-1)][2]=real_time_log[i][2];
	}
	real_time_log[i][0]=hour;
	real_time_log[i][1]=state;
	real_time_log[i][2]=client_id;
}

int write_log(int hour, int state, int client_id){
	FILE *file_log = fopen("simulation.log", "a");
	if(file_log == NULL){
		printf("Error: opening simulation.log\n");
		return 0;
	}

	switch(state) {
		case 1: fprintf(file_log,"[%s] ❤ Client %d arrived to AquaPark.\n", make_hours(hour), client_id);break;
		case 2: fprintf(file_log,"[%s] ➤ Client %d arrived to swimming pool.\n", make_hours(hour), client_id); break;
		case 3: fprintf(file_log,"[%s] ➤ Client %d arrived to Toboggan.\n", make_hours(hour), client_id); break;
		case 4: fprintf(file_log,"[%s] ➤ Client %d arrived to Race.\n", make_hours(hour), client_id); break;
		case 5: fprintf(file_log,"[%s] ➤ Client %d arrived to Sunbath\n", make_hours(hour), client_id); break;
		case 11: fprintf(file_log,"[%s] ☀ Client %d entered to AquaPark.\n", make_hours(hour), client_id); break;
		case 12: fprintf(file_log,"[%s] ☀ Client %d entered to swimming pool.\n", make_hours(hour), client_id); break;
		case 13: fprintf(file_log,"[%s] ☀ Client %d entered to Toboggan.\n", make_hours(hour), client_id); break;
		case 14: fprintf(file_log,"[%s] ☀ Client %d entered to Race.\n", make_hours(hour), client_id); break;
		case 15: fprintf(file_log,"[%s] ☀ Client %d entered to Sunbath\n", make_hours(hour), client_id); break;
		case 21: fprintf(file_log,"[%s] ★ Client %d went out of AquaPark.\n", make_hours(hour), client_id); break;
		case 22: fprintf(file_log,"[%s] ⚫ Client %d went out of swimming pool.\n", make_hours(hour), client_id); break;
		case 23: fprintf(file_log,"[%s] ⚫ Client %d went out of Toboggan.\n", make_hours(hour), client_id); break;
		case 24: fprintf(file_log,"[%s] ⚫ Client %d went out of Race.\n", make_hours(hour), client_id); break;
		case 25: fprintf(file_log,"[%s] ⚫ Client %d went out of Sunbath\n", make_hours(hour), client_id); break;
		case 31: fprintf(file_log,"[%s] ❌ Client %d gave up on AquaPark, was waiting for too long\n", make_hours(hour), client_id); break;
		case 32: fprintf(file_log,"[%s] ❌ Client %d gave up on swimming pool, was waiting for too long\n", make_hours(hour), client_id); break;
		case 33: fprintf(file_log,"[%s] ❌ Client %d gave up on Toboggan, was waiting for too long\n", make_hours(hour), client_id); break;
		case 34: fprintf(file_log,"[%s] ❌ Client %d gave up on Race, was waiting for too long\n", make_hours(hour), client_id); break;
		case 35: fprintf(file_log,"[%s] ❌ Client %d gave up on Sunbath, was waiting for too long\n", make_hours(hour), client_id); break;
		case 100: fprintf(file_log,"[%s] ⛬ Simulation started.\n", make_hours(hour)); break;
		case 101: fprintf(file_log,"[%s] ⛬ Simulation is over.\n", make_hours(hour)); break;
		default: fprintf(file_log,"[%s] Error: didnt get what you mean", make_hours(hour)); break;
	}
	fclose(file_log);
	return 1;
}

int write_report(){
	FILE *file_report = fopen("statistics.txt", "w");
	if(file_report == NULL){
		printf("Erro ao abrir o ficheiro Relatorio.txt\n");
		return 0;
	}

	fprintf(file_report,"%s","---------------------------Simulation statistics--------------------------\n");
	fprintf(file_report,"%s","Clientes:\n");
	fprintf(file_report,"	%s : %d\n","Total clients on AquaPark", 2);
	fprintf(file_report,"	%s : %d\n","Total clients on swimming pool", 1);
	fprintf(file_report,"	%s : %d\n","Total clients on Toboggan", 0);
	fprintf(file_report,"	%s : %d\n","Total clients on Race", 0);
	fprintf(file_report,"	%s : %d\n","Total clients on Sunbath", 0);
	fprintf(file_report,"	%s : %d\n","Average of VIP clients on AquaPark", 0);
	fprintf(file_report,"	%s : %d\n","Average of VIP clients on swimming pool", 0);
	fprintf(file_report,"	%s : %d\n","Average of VIP clients on Toboggan", 0);
	fprintf(file_report,"	%s : %d\n","Average of VIP clients on Race", 0);
	fprintf(file_report,"	%s : %d\n","Average of VIP clients on Sunbath", 0);
	fprintf(file_report,"%s","Drops:\n");
	fprintf(file_report,"	%s : %d\n","Total drops on queue",0);
	fprintf(file_report,"	%s : %d\n","Drops on AquaPark",0);
	fprintf(file_report,"	%s : %d\n","Drops on swimming pool",1);
	fprintf(file_report,"	%s : %d\n","Drops on Toboggan",0);
	fprintf(file_report,"	%s : %d\n","Drops on  Race",0);
	fprintf(file_report,"	%s : %d\n","Drops on  Sunbath",0);
	fprintf(file_report,"%s","Average time:\n");
	fprintf(file_report,"	%s : %f\n","Average time on AquaPark",0.0);
	fprintf(file_report,"	%s : %f\n","Average time on swimming pool",0.0);
	fprintf(file_report,"	%s : %f\n","Average time on Toboggan",0.0);
	fprintf(file_report,"	%s : %f\n","Average time on Race",0.0);
	fprintf(file_report,"	%s : %f\n","Average time on Sunbath",0.0);
	fprintf(file_report,"%s","Max time:\n");
	fprintf(file_report,"	%s : %f\n","Max time on AquaPark",0.0);
	fprintf(file_report,"	%s : %f\n","Max time on swimming pool",0.0);
	fprintf(file_report,"	%s : %f\n","Max time on Toboggan",0.0);
	fprintf(file_report,"	%s : %f\n","Max time on Race",0.0);
	fprintf(file_report,"	%s : %f\n","Max time on Sunbath",0.0);
	fprintf(file_report,"%s","\n--------------------------------------------------------------------------\n");
	fclose(file_report);

	return 1;
}

int * decode (char str[28]){
	char s_hours[4];
	char s_state[3];
	char s_client_id[4];
	int static final[3];
	stpcpy(s_hours, strtok(str,","));
	stpcpy(s_state, strtok(NULL,","));
	strcpy(s_client_id, strtok(NULL,","));
	final[0] = atoi(s_hours);
	final[1] = atoi(s_state);
	final[2] = atoi(s_client_id);
	return final;
}

void write_decoder(int final[3]) {
	int state = final[1];

	switch(state) {
		case 1: printf("   │  [%s] ❤ Client %d arrived to AquaPark.                               │\n", make_hours(final[0]), final[2]);break;
		case 2: printf("   │  [%s] ➤ Client %d arrived to swimming pool.                          │\n", make_hours(final[0]), final[2]); break;
		case 3: printf("   │  [%s] ➤ Client %d arrived to Toboggan.                               │\n", make_hours(final[0]), final[2]); break;
		case 4: printf("   │  [%s] ➤ Client %d arrived to Race.                                   │\n", make_hours(final[0]), final[2]); break;
		case 5: printf("   │  [%s] ➤ Client %d arrived to Sunbath.                                │\n", make_hours(final[0]), final[2]); break;
		case 11: printf("   │  [%s] ☀ Client %d entered to AquaPark.                               │\n", make_hours(final[0]), final[2]); break;
		case 12: printf("   │  [%s] ☀ Client %d entered to swimming pool.                          │\n", make_hours(final[0]), final[2]); break;
		case 13: printf("   │  [%s] ☀ Client %d entered to Toboggan.                               │\n", make_hours(final[0]), final[2]); break;
		case 14: printf("   │  [%s] ☀ Client %d entered to Race.                                   │\n", make_hours(final[0]), final[2]); break;
		case 15: printf("   │  [%s] ☀ Client %d entered to Sunbath                                 │\n", make_hours(final[0]), final[2]); break;
		case 21: printf("   │  [%s] ★ Client %d went out of AquaPark.                              │\n", make_hours(final[0]), final[2]); break;
		case 22: printf("   │  [%s] ⚫ Client %d went out of swimming pool.                         │\n", make_hours(final[0]), final[2]); break;
		case 23: printf("   │  [%s] ⚫ Client %d went out of Toboggan.                              │\n", make_hours(final[0]), final[2]); break;
		case 24: printf("   │  [%s] ⚫ Client %d went out of Race.                                  │\n", make_hours(final[0]), final[2]); break;
		case 25: printf("   │  [%s] ⚫ Client %d went out of Sunbath                                │\n", make_hours(final[0]), final[2]); break;
		case 31: printf("   │  [%s] ❌ Client %d gave up on AquaPark, was waiting for too long      │\n", make_hours(final[0]), final[2]); break;
		case 32: printf("   │  [%s] ❌ Client %d gave up on swimming pool, was waiting for too long │\n", make_hours(final[0]), final[2]); break;
		case 33: printf("   │  [%s] ❌ Client %d gave up on Toboggan, was waiting for too long      │\n", make_hours(final[0]), final[2]); break;
		case 34: printf("   │  [%s] ❌ Client %d gave up on Race, was waiting for too long          │\n", make_hours(final[0]), final[2]); break;
		case 35: printf("   │  [%s] ❌ Client %d gave up on Sunbath, was waiting for too long       │\n", make_hours(final[0]), final[2]); break;
		case 100: printf("   │  [%s] ⛬ Simulation started.                                          │\n", make_hours(final[0])); break;
		case 101: printf("   │  [%s] ⛬ Simulation is over.                                          │\n", make_hours(final[0])); break;
		case -1: printf("   │                                                                         │\n"); break;
		default: printf("   │  [%s] Error: didnt get what you mean                                 │\n", make_hours(final[0])); break;
	}
}
void fill_empty(int qto){
	int i=0;
	for(i=0;i<qto;i++) printf("   │                                                                         │\n");
}
void print_header(int tab, int hour){
	// cria cabeçalho
	printf("   ┌─────────────────────────────────────────────────────────────────────────┐\n   │                      Sistemas Operativos 2015/2016                      │\n   └─────────────────────────────────────────────────────────────────────────┘\n ┌────────────────┌────────────────────────────────────────────────────────────┐\n");
	switch(tab){
		case 1: printf(" │      Log       │  ■ 1- Log  ■ 2- Statistics  ■ 3- Graph    ■ 4- About       │\n"); break;
		case 2: printf(" │   Statistics   │  ■ 1- Log  ■ 2- Statistics  ■ 3- Graph    ■ 4- About       │\n"); break;
		case 3: printf(" │     Graph      │  ■ 1- Log  ■ 2- Statistics  ■ 3- Graph    ■ 4- About       │\n"); break;
		case 4: printf(" │     About      │  ■ 1- Log  ■ 2- Statistics  ■ 3- Graph    ■ 4- About       │\n"); break;
		case 0: printf(" │     Start      │  ■ 1- Log  ■ 2- Statistics  ■ 3- Graph    ■ 4- About       │\n"); break;
	   default: printf(" │     UPS!!      │  ■ 1- Log  ■ 2- Statistics  ■ 3- Graph    ■ 4- About       │\n"); break;
	}
	printf(" └─┬──────────────┘──────────────────────────────────────────────────────────┬─┘\n");
	if(hour>-1) printf("   ├─────────────────────────────[ ·∙   %s  ∙· ]──────────────────────────┤\n", make_hours(hour));
	else printf("   ├─────────────────────────────[ ·∙   wait!  ∙· ]──────────────────────────┤\n");
}

void creat_graph(/*int aqua, int pool, int race, int race_status, int tobogan, int tobogan_status*/){

	// int percent_aqua = ((aqua*20)/max_person_aqua);
	 //printf("%d", percent_aqua);
	 printf("   │                             ┌──────────────────────────────────────────┐│\n   │ ┌───────────────────────────┤             Real time events             ││\n   │ │        Aquapark     Pool  └┬────────────────────────────────────────┬┘│\n   │ │                            │                  Race                  │ │\n");
	 printf("   │ │100 % ┫                     │ ┌────────────────────────────────────┐ │ │\n");
	 printf("   │ │      ┃                     │ │               Waiting              │ │ │\n");
	 printf("   │ │ 90 % ┫                     │ ├─────────────────┰──────────────────┤ │ │\n");
	 printf("   │ │      ┃                     │ │        0        ╏                  │ │ │\n");
	 printf("   │ │ 80 % ┫                     │ │       /█\\       ╏                  │ │ │\n");
	 printf("   │ │      ┃    ██               │ │       .Π.       ╏                  │ │ │\n");
   printf("   │ │ 70 % ┫    ██               │ │╸╸╸╸╸╸╸╸╸╸╸╸╸╸╸╸╸╏╺╺╺╺╺╺╺╺╺╺╺╺╺╺╺╺╺╺│ │ │\n");
   printf("   │ │      ┃    ██               │ │                 ╏                  │ │ │\n");
   printf("   │ │ 60 % ┫    ██               │ │                 ╏                  │ │ │\n");
   printf("   │ │      ┃    ██               │ │                 ╏                  │ │ │\n");
   printf("   │ │ 50 % ┫    ██               │ └─────────────────┸──────────────────┘ │ │\n");
   printf("   │ │      ┃    ██         ██    ├────────────────────────────────────────┤ │\n");
   printf("   │ │ 40 % ┫    ██         ██    │                Tobogan                 │ │\n");
   printf("   │ │      ┃    ██         ██    │ ┌────────────────────────────────────┐ │ │\n");
   printf("   │ │ 30 % ┫    ██         ██    │ │              On going              │ │ │\n");
   printf("   │ │      ┃    ██         ██    │ ├─────────────────┰──────────────────┤ │ │\n");
   printf("   │ │ 20 % ┫    ██         ██    │ │        0        ╏                  │ │ │\n");
   printf("   │ │      ┃    ██         ██    │ │       /█\\       ╏                  │ │ │\n");
   printf("   │ │ 10 % ┫    ██         ██    │ │       .Π.       ╏                  │ │ │\n");
   printf("   │ │      ┃    ██         ██    │ └─────────────────┸──────────────────┘ │ │\n");
   printf("   │ │      ┛                     │                                        │ │\n");
   printf("   │ └────────────────────────────┴────────────────────────────────────────┘ │\n");
	//for(i=0; i<20; i++){
		//if(i<percent_aqua) printf("██         \n", );
	}

	void creat_stats (/*int Numero_Entradas_Discoteca,int Numero_Entradas_Sala_Rock,int Numero_Entradas_Sala_Comercial,int Numero_Entradas_Sala_House,int Numero_Entradas_Sala_Sofas,int Total_Clientes_Normais_Discoteca,int Total_Clientes_Normais_Sala_Rock,int Total_Clientes_Normais_Sala_Comercial,int Total_Clientes_Normais_Sala_House,int Total_Clientes_Normais_Sala_Sofas,int Total_Clientes_VIPS_Discoteca,int Total_Clientes_VIPS_Sala_Rock,int Total_Clientes_VIPS_Sala_Comercial,int Total_Clientes_VIPS_Sala_House,int Total_Clientes_VIPS_Sala_Sofas,int Numero_Desistencias_Fila_Discoteca,int Numero_Desistencias_Fila_Sala_Rock,int Numero_Desistencias_Fila_Sala_Comercial,int Numero_Desistencias_Fila_Sala_House,int Numero_Desistencias_Fila_Sala_Sofas,float Tempo_Medio_Espera_Fila_Antes_Entrar_Discoteca,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_Rock,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_Comercial,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_House,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_Sofas,float Tempo_Medio_Espera_Fila_Antes_Desistir_Discoteca,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_Rock,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_Comercial,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_House,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_Sofas,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Discoteca,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_Rock,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_Comercial,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_House,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_Sofas, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Discoteca, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_Rock, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_Comercial, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_House, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_Sofas*/ ){
		//char * recebido = "0";
	//	int Total_Desistencia_Filas=Numero_Desistencias_Fila_Discoteca+Numero_Desistencias_Fila_Sala_Rock+Numero_Desistencias_Fila_Sala_Comercial+Numero_Desistencias_Fila_Sala_House+Numero_Desistencias_Fila_Sala_Sofas;//Soma de todas as desistencias
		printf("   │   ■─[ Clientes ]────────────────────────────────────────────────────┐   │\n");
		printf("   │   │   Number of clients have been in Aquapark :               %s   │   │\n",three_digit_number(60));
		printf("   │   │   number of VIP clients have been in pool :               %s   │   │\n",three_digit_number(67));
		printf("   │   │   Number of clients have been in Race :                   %s   │   │\n",three_digit_number(54));
		printf("   │   │   Number of clients have been in Tobogan :                %s   │   │\n",three_digit_number(34));
		printf("   │   │   Number of clients have been in Sunbath :                %s   │   │\n",three_digit_number(20));
		printf("   │   │   Number of clients have been in Slow River :             %s ┌─┤   │\n",three_digit_number(60));
	  printf("   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
		printf("   │   ■─[ Desistencias ]────────────────────────────────────────────────┐   │\n");
		printf("   │   │   Total number of drops in queue :                        %s   │   │\n",three_digit_number(50));
		printf("   │   │   Number of drops in Aquapark :                           %s   │   │\n",three_digit_number(69));
		printf("   │   │   Number of drops in Pool :                               %s   │   │\n",three_digit_number(6));
		printf("   │   │   Number of drops in Race :                               %s   │   │\n",three_digit_number(89));
		printf("   │   │   Number of drops in Tobogan :                            %s   │   │\n",three_digit_number(5));
		printf("   │   │   Number of drops in Slow River :                         %s ┌─┤   │\n",three_digit_number(45));
	  printf("   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
		printf("   │   ■─[ Tempos Medios ]───────────────────────────────────────────────┐   │\n");
		printf("   │   │   Average time in queue to get in Aquapark :            %s   │   │\n",three_digit_number(2));
		printf("   │   │   Average time in queue to get in Pool :                %s   │   │\n",three_digit_number(4));
		printf("   │   │   Average time in queue to get in Race :                %s   │   │\n",three_digit_number(3));
		printf("   │   │   Average time in queue to get in Tobogan :             %s   │   │\n",three_digit_number(2));
		printf("   │   │   Average time in queue to get in Slow River :          %s ┌─┤   │\n",three_digit_number(1));

		printf("   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");

	}

void print_body(int state){
	int i;
	int a[3]={1,1,1};
	switch(state){
		case 0:
			fill_empty(12);
			printf("   │                          PRESS ENTER TO START                           │\n");
			fill_empty(13);
			break;
		case 1:
			fill_empty(1);
			for(i=0; i<24;i++) write_decoder(a);
			fill_empty(1);
			break;
		case 2: creat_stats(); break;
		case 3: creat_graph(); break;
		case 4:
			printf("   │                                                                         │\n   │   ■─[ Joao Borges ]─────────────────────────────────────────────────┐   │\n   │   │                                                                 │   │\n   │   │   2016311                                                     ┌─┤   │\n   │   └───────────────────────────────────────────────────────────────┴─┘   │\n   │                                                                         │\n   │   ■─[ Nuno Rodrigues ]──────────────────────────────────────────────┐   │\n   │   │                                                                 │   │\n   │   │   2044009                                                     ┌─┤   │\n   │   └───────────────────────────────────────────────────────────────┴─┘   │\n   │                                                                         │\n   │   ■─[ Vitor Paixao ]────────────────────────────────────────────────┐   │\n   │   │                                                                 │   │\n   │   │   2023212                                                     ┌─┤   │\n   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
			fill_empty(11);
			break;
		default: print_body(1); break;
	}
}
void print_footer(){
	printf("   └─────────────────────────────────────────────────────────────────────────┘\n   ┌─────────────────────────────────────────────────────────────────────────┐\n   │  Aquapark Simulation                                        ■ 5 - Exit  │\n");
}
