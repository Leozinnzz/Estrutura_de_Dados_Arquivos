/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char nome[100];
	int idade;
	float altura;
	int ativo;
}Pessoa;

FILE* openfile(char* filename) {
	FILE* arq = fopen(filename, "rb+");
	if(!arq)
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa nao conseguiu encontrar o arquivo");
		return 0;
	}
	
	return arq;
}

int interface() {
	printf("\n===============Menu==============\n");
	printf("1- registrar\n");
	printf("2- Listar pessoas\n");
	printf("3- Editar pessoa\n");
	printf("4- Ordenar pessoas\n");
	
	int opc; 
	printf("\nEscolha: ");
	scanf("%d", &opc);
	
	return opc;

}

void setPessoa(FILE* arq) {
	Pessoa p;
	
	fseek(arq, 0, SEEK_END);
	printf("Digite o nome do individuo: ");
	scanf(" %[^\n]", p.nome);
	printf("Digite a idade do individuo: ");
	scanf("%d", &p.idade);
	printf("Digite a altura do individuo: ");
	scanf("%f", &p.altura);
	p.id = (ftell(arq) / sizeof(Pessoa)) + 1;
	
	if(fwrite(&p, sizeof(Pessoa), 1, arq))
		fflush(arq);
	
}

void getPessoa(FILE* arq) {
	Pessoa p;
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Pessoa), 1, arq)) 
		if(p.ativo)
			printf("\nId: %d\nNome: %s\nIdade: %d\nAltura%.2f\n", p.id, p.nome, p.idade, p.altura);
}

void editarPessoa(FILE* arq, int cod) {
	Pessoa p;
	int valido = 0;
	
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Pessoa), 1, arq)){
		if(p.id == cod && p.ativo) {
			
			printf("Novo nome: ");
			scanf(" %[^\n]", p.nome);
			
			printf("Nova idade: ");
			scanf("%d", &p.idade);
			
			printf("Nova altura: ");
			scanf("%f", &p.altura);
			
			//voltar o cursor uma vez
			fseek(arq, -sizeof(Pessoa),SEEK_CUR);
			//escrever no arquivo
			if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
				fflush(arq);
				valido = 1;
				break;
			}
		}
	}
	if(!valido) 
		printf("Pessoa nao encontrada! Digite um id valido!");
}

int getId() {
	int id;
	printf("Digite o id do individuo: ");
	scanf("%d", &id);
	return id;
}

//ordenaçao em arquivos
void ordenarPessoa(FILE* arq) {
	fseek(arq, 0, SEEK_END);
	int T = ftell(arq) / sizeof(Pessoa);
	Pessoa lista[T];
	fseek(arq, 0, SEEK_SET);
	
	fread(lista, T*sizeof(Pessoa), 1, arq);
	Pessoa aux;
	for(int i = 0; i < T; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(strcmp(lista[j].nome,lista[j+1].nome) > 0) {
				aux = lista[j];
				lista[j] = lista[j+1];
				lista[j+1] = aux;
			}
		}
	}
	
	fseek(arq, 0, SEEK_SET);
	fwrite(lista, sizeof(Pessoa), T, arq);
	fflush(arq);
}

int main() {
	
	FILE* arq = openfile("Return.dat");
	
	do {
		switch(interface()) {
			case 1:
				setPessoa(arq);
				break;
			case 2:
				getPessoa(arq);
				break;
			case 3:
				editarPessoa(arq, getId());
				break;
			case 4:
				ordenarPessoa(arq);
				break;
			case 0:
				fclose(arq);
				return 0;
			default:
				printf("Digite uma opcao valida!\n");
			
		}
	}while(1);
	
    //the destroyer of codes
}


