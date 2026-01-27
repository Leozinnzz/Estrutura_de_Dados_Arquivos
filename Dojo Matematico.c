/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 10
#define MAX 100

typedef struct {
	char nome[100];
	int tempo;
}Player;

FILE* openfile(char* filename) {
	FILE* arq = fopen(filename, "rb+"); 
	if(!arq)
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa nao conseguiu acessar o arquivo"); 
		return 0;
	}
	return arq;
}


int menu() {
	printf("\n=======================MENU=======================\n");
	printf("1 - Jogar\n");
	printf("2 - Ranking\n");
	printf("0 - Sair\n");
	int opc; 
	printf("Escolha uma opcao: ");
	scanf("%d", &opc);
	
	return opc;
}

void game(FILE* arq){
	Player pl;
	time_t inicio, fim;
	int a, b, correta, resp;
	char op;
	
	printf("Digite seu nome: ");
	scanf(" %[^\n]", pl.nome);
	
	
	inicio = time(NULL); 

	for( int i = 0; i < TOTAL; i++) {
		
		if(i < 2) { //soma
 			a = 1 + rand() % 100;
 			b = 1 + rand() % 100;
 			op = '+';
 			correta = a + b;
		}
		
		else if(i < 4){ // subtracao
			a = 1 + rand() % 100;
 			b = 1 + rand() % 100;
 			op = '-';
 			correta = a - b;
		}
		
		else if(i < 6){ //multiplicacao
			a = 1 + rand() % 100;
			b = 1 + rand() % 100;
			op = '*';
 			correta = a * b;
		}
		
		else if(i < 8){ //divisao
			a = 1 + rand() % 100;
 			b = 1 + rand() % 100;
 			a = correta * b;
 			op = '/';
		}
		
		
		else { //porcentagem
			a = 1 + (rand() % 9) * 10;
			b = 1 + rand() % 100; 
			op = '%'; 
			correta = (a * b) / 100;
		}
		
		if(op == '%') 
			printf("Pergunta %d: Quanto eh %d%% de %d? ", i+1, a, b);
		else 
			printf("Pergunta %d: %d %c %d = ", i+1, a, op, b);
	
		scanf("%d", &resp);
		
	}
	
	fim = time(NULL);
	pl.tempo = (int)(fim - inicio);
	
	fseek(arq, 0, SEEK_END);
	fwrite(&pl, sizeof(Player), 1, arq);
	fflush(arq);
	
	printf("Tempo total: %d segundos\n", pl.tempo);
}

int loadPlayers(FILE* arq, Player lista[]) {
	int T;
	fseek(arq, 0, SEEK_END);
	T = ftell(arq) / sizeof(Player);
	fseek(arq, 0, SEEK_SET); 
	fread(lista, sizeof(Player), T, arq);
	return T;
}

void sortPlayer(Player lista[], int n){
	Player aux;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n-i-1; j++) {
			if(lista[j].tempo > lista[j+1].tempo) {
				aux = lista[j];
				lista[j] = lista[j+1]; 
				lista[j+1] = aux;
			}
		}
	}
}

void ranking(FILE* arq) {
	Player v[MAX];
	int n = loadPlayers(arq, v);
	
	sortPlayer(v, n);
	
	printf("\n=========== RANKING (MENOR TEMPO) ===========\n");
	printf("Nome                 Tempo(s)\n");
	printf("---------------------------------\n");
	
	for(int i = 0; i < n; i++) {
		printf("%-20s %d\n", v[i].nome, v[i].tempo);
	}
	
}
int main() {
	FILE* arq = openfile("DojoMatematico.dat");
	
	srand(time(NULL));

	do {
		switch(menu()) {
			case 1:
				game(arq);
				break;
			case 2:
				ranking(arq);
				break;
			case 0:
				fclose(arq);
				return 0;
			default:
				printf("Digite uma escolha valida!");
			}
	}while(1);
	
	
}
