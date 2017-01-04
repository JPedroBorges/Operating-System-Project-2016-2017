//*****************************************************************
//			Sistemas Operativos		- Projecto 2016/2017
// (●̮̮̃•̃)		João Borges				-
// /█\		Nuno Rodrigues			-
// .Π.		Vitor Paixão			-
//*****************************************************************

#include "unix.h"



typedef struct geral{
	char nome[5];
		int ID;
		int chegada;
		int entrada;
		int saida;
		int desistencia;
		struct geral *next;
}geral;



/*typedef struct s_swimming {
	int ID;
	int chegada;
	int entrada;int
	int saida;
	int desistencia;
	struct s_swimming *next;
}s_swimming;*/
//------------------------------------------
struct geral aquapark;
struct geral swimming_pool;

geral *inicio_aqua = NULL;
geral *inicio_swim = NULL;

//int activity[5];
int num_clients_aqua = 0;
int num_desistencia_aqua = 0;
int num_clients_swimming = 0;

pthread_mutex_t t_teste;

char name[10];
int teste;
int hora_chegada;
int hora_entrada;
int hora_saida;
int hora_desistencia;

int chega_a;
int entra_a;
float total_a;

int chega_s;
int entra_s;
float total_s;

int final_swimm = 0;
int ola_swimm = 1;
float dif_swimm = 0;

int final_aqua = 0;
int ola_aqua = 1;
float dif_aqua = 0;


int max_person_aqua = 10000;
int max_person_pool = 100;

int real_time_log[24][3]={{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
void fill_realtimelog(int hour, int state, int client_id){
	int i;
	for(i=1;i<24;i++){
		real_time_log[(i-1)][0]=real_time_log[i][0];
		real_time_log[(i-1)][1]=real_time_log[i][1];
		real_time_log[(i-1)][2]=real_time_log[i][2];
	}
	real_time_log[23][0]=hour;
	real_time_log[23][1]=state;
	real_time_log[23][2]=client_id;
}

void calc_stat_average_aqua(){
//int total1 = 0;
dif_aqua = 0;
int total_aqua = 0;

		geral *aux2 = &*inicio_aqua;

				while (aux2 != NULL){
					//geral *aux1 = inicio_aqua;

					if(aux2 -> entrada != 0){
						//aux1 -> entrada = hour;
						chega_a = aux2 -> chegada;
						entra_a = aux2 -> entrada;
						total_a = 0;
						total_a = (entra_a - chega_a);
						total_aqua++;
					}
					aux2 = aux2 -> next;
					dif_aqua = dif_aqua + total_a;
				}
				ola_aqua = (int)(dif_aqua / total_aqua);
				final_aqua = (int)round(ola_aqua);


	}

void calc_stat_average_swimm(){
	dif_swimm = 0;
	int total_swimm = 0;

			geral *aux3 = &*inicio_swim;

					while (aux3 != NULL){
						//geral *aux1 = inicio_aqua;

						if(aux3 -> entrada != 0){
							//aux1 -> entrada = hour
							chega_s = aux3 -> chegada;
							entra_s = aux3 -> entrada;
							total_s = 0;
							total_s = (entra_s - chega_s);
							total_swimm++;
						}
						aux3 = aux3 -> next;
						dif_swimm = dif_swimm + total_s;
					}
					ola_swimm = (int)(dif_swimm / total_swimm);
					final_swimm = (int)round(ola_swimm);
}


void insert_struct(struct geral *a, int hour, int client_id, geral *estr){

			a = (struct geral*) malloc(sizeof(struct geral));

			geral *ola = &*estr;
			if(ola == inicio_aqua){
				a->nome[5] = 'A';
			}else if(ola == inicio_swim){
				a->nome[5] = 'S';
			}
			a->ID = client_id;
			a->chegada = hour;
			a->entrada = 0;
			a->saida = 0;
			a->desistencia = 0;
			a->next = NULL;


			name[10] = a -> nome[5];
			teste = a -> ID;
			hora_chegada = a -> chegada;
			hora_entrada = a -> entrada;
			hora_saida = a -> saida;
			hora_desistencia = a -> desistencia;


					geral *ola1 = &*estr;

						//geral *ola1 = inicio_swim;

						if( ola1 == NULL){
							//ola1 = a;
							if(ola1 == inicio_aqua){
								inicio_aqua = a;
								ola1 = a;
							}else
							if (ola1 == inicio_swim){
								inicio_swim = a;
								ola1 = a;
							}
							//inicio_aqua = a;
						}
						else{

										while(ola1 -> next != NULL){
												ola1 = ola1 -> next;
										}
								ola1 -> next = a;
						}
		//	}}
}

void out_activity(int hour, int client_id, geral *estr){


geral *aux1 = &*estr;

	while (aux1 != NULL){
		//geral *aux1 = inicio_aqua;
		if(aux1 -> ID == client_id){
			aux1 -> saida = hour;

			name[10] = aux1 -> nome[5];
			teste = aux1 -> ID;
			hora_chegada = aux1 -> chegada;
			hora_entrada = aux1 -> entrada;
			hora_saida = aux1 -> saida;
			hora_desistencia = aux1 -> desistencia;

		}
		aux1 = aux1 -> next;
	}

}



void entry_activity(int hour, int client_id, geral *estr){

geral *aux1 = &*estr;
	while (aux1 != NULL){
		//geral *aux1 = inicio_aqua;
		if(aux1 -> ID == client_id){
			aux1 -> entrada = hour;

			teste = aux1 -> ID;
			hora_chegada = aux1 -> chegada;
			hora_entrada = aux1 -> entrada;
			hora_saida = aux1 -> saida;
			hora_desistencia = aux1 -> desistencia;

		}
		aux1 = aux1 -> next;
	}

//}}
}



void save_info(int hour, int state, int client_id){
pthread_mutex_lock(&t_teste);
calc_stat_average_aqua();
pthread_mutex_unlock(&t_teste);
pthread_mutex_lock(&t_teste);
calc_stat_average_swimm();
pthread_mutex_unlock(&t_teste);

	switch(state){
		case 1:
					pthread_mutex_lock(&t_teste);
					insert_struct(&aquapark, hour, client_id, &*inicio_aqua);
					num_clients_aqua ++;

					pthread_mutex_unlock(&t_teste);
					break;
		case 11:
					pthread_mutex_lock(&t_teste);
					entry_activity(hour, client_id, &*inicio_aqua);
//calc_stat_average_aqua();

					pthread_mutex_unlock(&t_teste);
					break;
		case 21:
					pthread_mutex_lock(&t_teste);
					out_activity(hour, client_id, &*inicio_aqua);

					pthread_mutex_unlock(&t_teste);
					break;
		case 2:
					pthread_mutex_lock(&t_teste);
					insert_struct(&swimming_pool, hour, client_id, &*inicio_swim);
					num_clients_swimming ++;

					pthread_mutex_unlock(&t_teste);
					break;
		case 12:
					pthread_mutex_lock(&t_teste);
					entry_activity(hour, client_id, &*inicio_swim);
				//	calc_stat_average_swimm();

					pthread_mutex_unlock(&t_teste);
					break;
		case 22:
					pthread_mutex_lock(&t_teste);
					out_activity(hour, client_id, &*inicio_swim);

					pthread_mutex_unlock(&t_teste);
					break;
		default:
		break;
	}
}


	/*
	s_aquapark *aux1 = inicio_aqua;
	if(state == 1 ){
		struct s_aquapark *pAquapark = (struct s_aquapark*) malloc(sizeof(struct s_aquapark));
		//activity[1] = *pAquapark;
		pAquapark -> ID = client_id;
		pAquapark -> chegada = hour;
		pAquapark -> entrada = 0;hora_chegada
		pAquapark -> saida = 0;
		pAquapark -> desistencia = 0;
		pAquapark -> next = NULL;

		num_clients_aqua ++;

		teste = pAquapark -> ID;
		hora_chegada = pAquapark -> chegada;
		hora_entrada = pAquapark -> entrada;
		hora_saida = pAquapark -> saida;
		hora_desistencia = pAquapark -> desistencia;


		if( inicio_aqua == NULL){
			inicio_aqua = pAquapark;
		}
		else{
			s_aquapark *aux = inicio_aqua;
			while(aux -> next != NULL){
					aux = aux -> next;
			}
			aux-> next = pAquapark;
		}
	}
	else if (state == 11){
		//activity[1] = *aux1;
		while (aux1 != NULL){
			if(aux1 -> ID == client_id){
				aux1 -> entrada = hour;

				teste = aux1 -> ID;
				hora_chegada = aux1 -> chegada;
				hora_entrada = aux1 -> entrada;
				hora_saida = aux1 -> saida;
				hora_desistencia = aux1 -> desistencia;

			}
			aux1 = aux1 -> next;
		}
	}
	else if(state == 21){
		while (aux1 != NULL){
			if(aux1 -> ID == client_id){
				aux1 -> saida = hour;

				teste = aux1 -> ID;
				hora_chegada = aux1 -> chegada;
				hora_entrada = aux1 -> entrada;
				hora_saida = aux1 -> saida;bb
				hora_desistencia = aux1 -> desistencia;

			}
			aux1 = aux1 -> next;
		}
	}
	else if(state == 31){
		num_desistencia_aqua ++;
		while (aux1 != NULL){int ola = hour;
				teste = aux1 -> ID;
				hora_chegada = aux1 -> chegada;
				hora_entrada = aux1 -> entrada;
				hora_saida = aux1 -> saida;
				hora_desistencia = aux1 -> desistencia;

			}
			aux1 = aux1 -> next;
		}
	}

*/








int write_log(int hour, int state, int client_id){
	FILE *file_log = fopen("simulation.log", "a");
	if(file_log == NULL){
		printf("Error: opening simulation.log\n");
		return 0;
	}

	switch(state) {
		case 1: fprintf(file_log,"[%s] ❤ Client %d arrived to AquaPark.\n", make_hours(hour), client_id);break;
		case 2: fprintf(file_log,"[%s] ➤ Client %d arrived to swimming pool.\n", make_hours(hour), client_id); break;
		case 3: fprintf(file_log,"[%s] ➤ Cli   00:00 ient %d entered to AquaPark.\n", make_hours(hour), client_id); break;
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
		case 33: fprintf(file_log,"[%s] ❌ Client %d gave up on Tobogan, was waiting for too long\n", make_hours(hour), client_id); break;
		case 34: fprintf(file_log,"[%s] ❌ Client %d gave up on Race, was waiting for too long\n", make_hours(hour), client_id); break;
		case 35: fprintf(file_log,"[%s] ❌ Client %d gave up on Sunbath, was waiting for too long\n", make_hours(hour), client_id); break;

		case 43: fprintf(file_log,"[%s] ➤ Toboggan wooooooo.\n", make_hours(hour)); break;
		case 44: fprintf(file_log,"[%s] ➤ Race wooooooo.\n", make_hours(hour)); break;
		case 53: fprintf(file_log,"[%s] ➤ Toboggan trip is over.\n", make_hours(hour)); break;
		case 54: fprintf(file_log,"[%s] ➤ Race trip is over.\n", make_hours(hour)); break;

		case 100: fprintf(file_log,"[%s] ⛬ Simulation started.\n", make_hours(hour)); break;
		case 101: fprintf(file_log,"[%s] ⛬ Simulation is over.\n", make_hours(hour)); break;
		default: fprintf(file_log,"[%s] Error: didnt get what you mean", make_hours(hour)); break;
	}
	fclose(file_log);
	return 1;
}
   //00:00
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

void write_decoder(int hour, int state, int client_id) {
	switch(state) {
		case 1: printf("   │  [%s] ❤ Client",make_hours(hour)); printf(" %s arrived to AquaPark.                              │\n", three_digit_number(client_id)); break;
		case 2: printf("   │  [%s] ➤ Client",make_hours(hour)); printf(" %s arrived to swimming pool.                         │\n", three_digit_number(client_id)); break;
		case 3: printf("   │  [%s] ➤ Client",make_hours(hour)); printf(" %s arrived to Toboggan.                              │\n", three_digit_number(client_id)); break;
		case 4: printf("   │  [%s] ➤ Client",make_hours(hour)); printf(" %s arrived to Race.                                  │\n", three_digit_number(client_id)); break;
		case 5: printf("   │  [%s] ➤ Client",make_hours(hour)); printf(" %s arrived to Sunbath.                               │\n", three_digit_number(client_id)); break;
		case 11: printf("   │  [%s] ☀ Client",make_hours(hour)); printf(" %s entered to AquaPark.                              │\n", three_digit_number(client_id)); break;
		case 12: printf("   │  [%s] ☀ Client",make_hours(hour)); printf(" %s entered to swimming pool.                         │\n", three_digit_number(client_id)); break;
		case 13: printf("   │  [%s] ☀ Client",make_hours(hour)); printf(" %s entered to Toboggan.                              │\n", three_digit_number(client_id)); break;
		case 14: printf("   │  [%s] ☀ Client",make_hours(hour)); printf(" %s entered to Race.                                  │\n", three_digit_number(client_id)); break;
		case 15: printf("   │  [%s] ☀ Client",make_hours(hour)); printf(" %s entered to Sunbath                                │\n", three_digit_number(client_id)); break;
		case 21: printf("   │  [%s] ★ Client",make_hours(hour)); printf(" %s went out of AquaPark.                             │\n", three_digit_number(client_id)); break;
		case 22: printf("   │  [%s] ⚫ Client",make_hours(hour)); printf(" %s went out of swimming pool.                        │\n", three_digit_number(client_id)); break;
		case 23: printf("   │  [%s] ⚫ Client",make_hours(hour)); printf(" %s went out of Toboggan.                             │\n", three_digit_number(client_id)); break;
		case 24: printf("   │  [%s] ⚫ Client",make_hours(hour)); printf(" %s went out of Race.                                 │\n", three_digit_number(client_id)); break;
		case 25: printf("   │  [%s] ⚫ Client",make_hours(hour)); printf(" %s went out of Sunbath                               │\n", three_digit_number(client_id)); break;
		case 31: printf("   │  [%s] ❌ Client",make_hours(hour)); printf(" %s gave up on AquaPark, was waiting for too long     │\n", three_digit_number(client_id)); break;
		case 32: printf("   │  [%s] ❌ Client",make_hours(hour)); printf(" %s gave up on swimming pool, was waiting for too long│\n", three_digit_number(client_id)); break;
		case 33: printf("   │  [%s] ❌ Client",make_hours(hour)); printf(" %s gave up on Toboggan, was waiting for too long     │\n", three_digit_number(client_id)); break;
		case 34: printf("   │  [%s] ❌ Client",make_hours(hour)); printf(" %s gave up on Race, was waiting for too long         │\n", three_digit_number(client_id)); break;
		case 35: printf("   │  [%s] ❌ Client",make_hours(hour)); printf(" %s gave up on Sunbath, was waiting for too long      │\n", three_digit_number(client_id)); break;

		case 43: break;
		case 44: break;
		case 53: break;
		case 54: break;

		case 100: printf("   │  [%s] ⛬ Simulation started.                                          │\n", make_hours(hour)); break;
		case 101: printf("   │  [%s] ⛬ Simulation is over.                                          │\n", make_hours(hour)); break;
		case -1: printf("   │                                                                         │\n"); break;
		default: printf("   │  [%s] Error: didnt get what you mean                                 │\n", make_hours(hour)); break;
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

	void creat_stats (int num_aqua, int num_swim, int chegada, int entrada, int saida, int desistencia, int fin_aqua, int fin_swimm, char a /*int Numero_Entradas_Discoteca,int Numero_Entradas_Sala_Rock,int Numero_Entradas_Sala_Comercial,int Numero_Entradas_Sala_House,int Numero_Entradas_Sala_Sofas,int Total_Clientes_Normais_Discoteca,int Total_Clientes_Normais_Sala_Rock,int Total_Clientes_Normais_Sala_Comercial,int Total_Clientes_Normais_Sala_House,int Total_Clientes_Normais_Sala_Sofas,int Total_Clientes_VIPS_Discoteca,int Total_Clientes_VIPS_Sala_Rock,int Total_Clientes_VIPS_Sala_Comercial,int Total_Clientes_VIPS_Sala_House,int Total_Clientes_VIPS_Sala_Sofas,int Numero_Desistencias_Fila_Discoteca,int Numero_Desistencias_Fila_Sala_Rock,int Numero_Desistencias_Fila_Sala_Comercial,int Numero_Desistencias_Fila_Sala_House,int Numero_Desistencias_Fila_Sala_Sofas,float Tempo_Medio_Espera_Fila_Antes_Entrar_Discoteca,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_Rock,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_Comercial,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_House,float Tempo_Medio_Espera_Fila_Antes_Entrar_Sala_Sofas,float Tempo_Medio_Espera_Fila_Antes_Desistir_Discoteca,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_Rock,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_Comercial,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_House,float Tempo_Medio_Espera_Fila_Antes_Desistir_Sala_Sofas,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Discoteca,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_Rock,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_Comercial,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_House,int Tempo_Estadia_Maximo_Fila_Antes_Entrar_Sala_Sofas, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Discoteca, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_Rock, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_Comercial, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_House, int Tempo_Estadia_Maximo_Fila_Antes_Desistir_Sala_Sofas*/ ){
		//char * recebido = "0";
	//	int Total_Desistencia_Filas=Numero_Desistencias_Fila_Discoteca+Numero_Desistencias_Fila_Sala_Rock+Numero_Desistencias_Fila_Sala_Comercial+Numero_Desistencias_Fila_Sala_House+Numero_Desistencias_Fila_Sala_Sofas;//Soma de todas as desistencias
		printf("   │   ■─[ Clientes ]────────────────────────────────────────────────────┐   │\n");
		printf("   │   │   Number of clients have been in Aquapark :               %s   │   │\n",three_digit_number(num_aqua));
		printf("   │   │   number of VIP clients have been in pool :               %s   │   │\n",three_digit_number(num_swim));
		printf("   │   │   Number of clients have been in Race :                   %s   │   │\n",make_hours(chegada));
		printf("   │   │   Number of clients have been in Tobogan :                %s   │   │\n",make_hours(entrada));
		printf("   │   │   Number of clients have been in Sunbath :                %s   │   │\n",make_hours(saida));
		printf("   │   │   Number of clients have been in Slow River:              %c ┌─┤   │\n",a);
	  printf("   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
	  printf("   │                                                                         │\n");
		printf("   │   ■─[ Desistencias ]────────────────────────────────────────────────┐   │\n");
		printf("   │   │   Total number of drops in queue :                        %s   │   │\n",three_digit_number(50));
		printf("   │   │   Number of drops in Aquapark :                           %s   │   │\n",three_digit_number(69));
		printf("   │   │   Number of drops in Pool :                               %s   │   │\n",three_digit_number(6));
		printf("   │   │   Number of drops in Race :                               %s   │   │\n",three_digit_number(89));
		printf("   │   │   Number of drops in Tobogan :                            %s   │   │\n",three_digit_number(5));
		printf("   │   │   Number of drops in Slow River :                         %s ┌─┤   │\n",three_digit_number(45));
	  printf("   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
	  printf("   │                                                                         │\n");
		printf("   │   ■─[ Tempos Medios ]───────────────────────────────────────────────┐   │\n");
		printf("   │   │   Average time in queue to get in Aquapark :              %s   │   │\n",make_hours(fin_aqua));
		printf("   │   │   Average time in queue to get in Pool :                  %s   │   │\n",make_hours(fin_swimm));
		printf("   │   │   Average time in queue to get in Race :                  %s   │   │\n",three_digit_number(0));
		printf("   │   │   Average time in queue to get in Tobogan :               %s   │   │\n",three_digit_number(0));
		printf("   │   │   Average time in queue to get in Slow River :            %s ┌─┤   │\n",three_digit_number(0));

		printf("   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
		printf("   │                                                                         │\n");

	}

void print_body(int tab){
	int i;
	switch(tab){
		case 0:
			fill_empty(12);
			printf("   │                          PRESS ENTER TO START                           │\n");
			fill_empty(13);
			break;
		case 1:
			fill_empty(1);
			for(i=0; i<24;i++) write_decoder(real_time_log[i][0], real_time_log[i][1], real_time_log[i][2]);
			fill_empty(1);
			break;
		case 2: creat_stats(num_clients_aqua, num_clients_swimming, hora_chegada, hora_entrada, hora_saida, hora_desistencia, final_aqua, final_swimm, name[10]); break;
		case 3: creat_graph(); break;
		case 4:
			printf("   │                                                                         │\n   │   ■─[ Joao Borges ]─────────────────────────────────────────────────┐   │\n   │   │                                                                 │   │\n   │   │   2016311                                                     ┌─┤   │\n   │   └───────────────────────────────────────────────────────────────┴─┘   │\n   │                                                                         │\n   │   ■─[ Nuno Rodrigues ]──────────────────────────────────────────────┐   │\n   │   │                                                                 │   │\n   │   │   2044009                                                     ┌─┤   │\n   │   └───────────────────────────────────────────────────────────────┴─┘   │\n   │                                                                         │\n   │   ■─[ Vitor Paixao ]────────────────────────────────────────────────┐   │\n   │   │                                                                 │   │\n   │   │   2023212                                                     ┌─┤   │\n   │   └───────────────────────────────────────────────────────────────┴─┘   │\n");
			fill_empty(11);
			break;
		default: print_body(1);break;
	}
}
void print_footer(){
	printf("   └─────────────────────────────────────────────────────────────────────────┘\n   ┌─────────────────────────────────────────────────────────────────────────┐\n   │  Aquapark Simulation                                        ■ 5 - Exit  │\n");
}

void clear_memory(struct geral *geral){

  while (geral != NULL)
    {
      struct geral *next = geral -> next;
      free (geral -> ID);
			free (geral -> chegada);
			free (geral -> entrada);
			free (geral -> saida);
			free (geral -> desistencia);
      free (geral);
      geral = next;
			}
		if(geral == NULL){
			printf("tá lá!!");
		}
		else{
			printf("alguma coisa está mal!");
		}
}
