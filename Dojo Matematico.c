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
#include "input.h"

#define OP 2

typedef struct {
	char nome[100];
	int tempo;
	int ranking;
}Jogador;

FILE* openFile(char* filename){
	FILE* arq = fopen(filename, "rb+");
	if(!arq) 
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa não conseguiu abrir o arquivo");
		return 0;
	}
	return arq;
		
}

int interface() {
	printf("\n=================MENU=================\n");
	printf("1 - Jogar\n");
	printf("2 - Ranking\n");
	printf("3 - Encerrar programa");
	
	int opc;
	
	input(INT, "\nEscolha uma opção: ", &opc);
	return opc;
	
}

void sum(){
	int n1, n2, resp, result;
	fseek(arq, 0, SEEK_SET);
	for(int i = 0; i < OP; i++) {
		n1 = 1 + rand() % 100;
		n2 = 1 + rand() % 100;
		printf("%d + %d = ", n1, n2);
		result = n1 + n2;
		scanf(" %d", &resp);
		if(resp == result) {
			
		}

	}
}

void init(FILE* arq){
	int t1, t2;
	t1 = time(NULL);
	sum();
	t2 = time(NULL);
}


void setJogador(FILE* arq){
	Jogador j;
	fseek(arq, 0, SEEK_SET);
	j.ranking = 0;
	
	input(STR, "Digite o nome do jogador: ", j.nome);
	if(fwrite(&j, sizeof(Jogador), 1, arq)) {
		fflush(arq);
		return;
	}
		
}


int main() {
	
    srand(time(NULL));
    

    
    do {
		
		switch(interface()){
			case 1:
				sum();
				break;
		}
		
		
	}while(1);
   

    //the destroyer of codes
}


