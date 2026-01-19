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
	int id;
	char nome[100];
	int idade;
	float altura;
	int ativo;
}Pessoa;

int interface() {
	printf("\n=================================MENU=======================================\n");
	printf("1 - Cadastrar uma nova pessoa: \n");
	printf("2 - Verificar pessoas cadastradas: \n");
	printf("3 - Excluir pessoas cadastradas \n");
	printf("4 - Editar pessoas cadastradas \n");
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
	p.id = (ftell(arq) / sizeof(Pessoa)) + 1;
	p.ativo = 1;
	
	if(fwrite(&p,sizeof(Pessoa),1,arq)){
		fflush(arq);
		printf("\nPessoa Registrada!\n");
	}
}

void listarPessoas(FILE* arq){
	Pessoa p; 
	rewind(arq);
	while(fread(&p, sizeof(Pessoa), 1, arq))
		if(p.ativo)
			printf("\nID: %d\nNome: %s\nIdade: %d\nAltura: %.2f\n", p.id, p.nome, p.idade, p.altura);
}

int getId(){
	int id; 
	printf("Digite o ID para do usuario: ");
	scanf("%d", &id);
	return id;
}

void excluirPessoa(FILE* arq, int id) {
	Pessoa p;
	int encontrado = 0; 
	
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Pessoa), 1, arq)) {
		if(p.id == id && p.ativo) {
			p.ativo = 0;
			fseek(arq, -sizeof(Pessoa), SEEK_CUR);
			if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
				fflush(arq);
				encontrado = 1;
				printf("\nExclusao realizada com sucesso!");
				break;
			}
		}
			
	}
	if(!encontrado){
		printf("Usuario inexistente! Tente novamente... ");
		next();
	}
}

void editarPessoa(FILE* arq, int cod){
	Pessoa p;
	int valido = 0;
	
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Pessoa), 1, arq)){
		if(p.id == cod && p.ativo == 1) {
			
			printf("\n====================Editar usuario cadastrado====================\n");
			
			printf("Novo nome: ");
			scanf(" %[^\n]s", p.nome);
			
			printf("Nova idade: ");
			scanf("%d", &p.idade);
			
			printf("Nova altura: ");
			scanf("%f", &p.altura);
			
			fseek(arq, -sizeof(Pessoa), SEEK_CUR);
			if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
				fflush(arq);
				valido = 1;
				printf("\nEdicao realizada com sucesso!");
				break;
			}
		}
	}
	if(!valido) {
		printf("Usuario nao encontrado! Tente novamente... ");
		next();
	}
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
			case 3: 
				excluirPessoa(myf, getId());
				break;
			case 4:
				editarPessoa(myf, getId());
				break;
			case 0: 
				fclose(myf);
				printf("Programa encerrado\n");
				return 0;
			default:
				printf("Digite uma opcao valida! Tenter novamente... ");
				next();
		}
	}while(1);
	
    //the destroyer of codes
}


