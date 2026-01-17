/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
	char nome[100];
	int idade;
	float altura;
}Pessoa;

int interface() {
	printf("\n=================================MENU=======================================\n");
	printf("1 - Cadastrar uma nova pessoa: \n");
	printf("2 - Verificar pessoas cadastradas: \n");
	printf("3 - Excluir pessoas cadastradas \n");
	printf("0 - Encerrar programa\n");
	printf("\nQual vc vai escolher? ");
	int opc; 
	scanf("%d", &opc);
	return opc; 
}

FILE* openfile(char* filename) {
	FILE* arq = fopen(filename,"rb+"); 
	if(!arq)
		arq = fopen(filename, "wb+"); 
	if(!arq) {
		printf(" o programa nao conseguiu abrir o arquivo");
		return 0;
	 }
	 return arq;
}


void next() {
	while(getchar() != '\n');
	getchar();
	system("clear");
}

void setPessoa(FILE* arq){
	Pessoa p; 
	
	fseek(arq, 0, SEEK_END);
	printf("Digite o nome da pessoa: ");
	scanf(" %[^\n]s", p.nome);
	printf("Digite a idade da pessoa: ");
	scanf("%d", &p.idade); 
	printf("Digite a altura da pessoa: "); 
	scanf("%f", &p.altura);
	
	if(fwrite(&p,sizeof(Pessoa),1,arq)){
		fflush(arq);
		printf("\nPessoa Registrada!\n");
	}
}

void listarPessoas(FILE* arq){
	Pessoa p; 
	
	rewind(arq);
	
	while(fread(&p, sizeof(Pessoa), 1, arq))
		printf("\nNome: %s\nIdade: %d\nAltura: %.2f\n", p.nome, p.idade, p.altura);
}

void excluirPessoa(FILE* arq) {
	
}

int main() {
    
	FILE* myf = openfile("Pessoas.txt");
    
    do {
		switch(interface()){
			case 1: 
				setPessoa(myf);
				break;
			case 2: 
				listarPessoas(myf);
				break;
			case 0: 
				fclose(myf);
				printf("Programa encerrado\n");
				return 0;
			default:
				printf("Digite uma opcao valida! ");
		}
	}while(1);
	
    //the destroyer of codes
}


