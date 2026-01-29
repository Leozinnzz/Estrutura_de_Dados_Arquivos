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
	float salario;
	int idade;
	int ativo;
}Pessoa;

FILE* openFile(char filename[]) {
	FILE* arq = fopen(filename, "rb+");
	if(!arq)
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa nao conseguiu abrir o arquivo");
		return 0;
	}
	return arq;
}

int menu() {
	printf("\n===============MENU======================\n");
	printf("0 - Sair\n");
	printf("1 - Registrar pessoas\n");
	printf("2 - Listar pessoas\n");
	printf("3 - Deletar pessoas\n");
	printf("4 - Ordenar lista\n");
	int opc;
	
	printf("\nEscolha: ");
	scanf("%d", &opc);
	return opc;
}

void registrarPessoa(FILE* arq){
	Pessoa p;
	
	fseek(arq, 0, SEEK_END);
	printf("Digite o nome da pessoa: ");
	scanf(" %[^\n]", p.nome); 
	
	printf("Digite o salario da pessoa: "); 
	scanf("%f", &p.salario);
	 
	printf("Digite a idade da pessoa: "); 
	scanf("%d", &p.idade);

	//autoincremento
	p.id = (ftell(arq) / sizeof(Pessoa)) + 1;
	p.ativo = 1;
	
	//salvar no arquivo
	if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
		fflush(arq);
		printf("\nPessoa registrada!\n");
	}
	
}

void listarPessoa(FILE* arq){
	Pessoa p;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&p, sizeof(Pessoa), 1, arq)) 
		if(p.ativo)
			printf("\nID: %d\nNome: %s\nSalario: %.2f\nIdade %d\n", p.id, p.nome, p.salario, p.idade);
}

int getId() {
	int id;
	printf("Digite o id do usuario: ");
	scanf("%d", &id);
	return id;
}

void excluirPessoa(FILE* arq, int cod){
	Pessoa p;
	int valido = 0;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&p, sizeof(Pessoa), 1, arq)) {
		if(p.id == cod && p.ativo) {
			p.ativo  = 0;
			
			fseek(arq, -sizeof(Pessoa), SEEK_CUR);
			if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
				fflush(arq);
				valido = 1;
				printf("\nPessoa excluida com sucesso!\n");
			}
		}
	}
	if(!valido) 
		printf("\nId nao encontrado!\n");
}

void ordenarPessoa(FILE* arq) {
	fseek(arq, 0, SEEK_END);
	int T = ftell(arq) / sizeof(Pessoa);
	Pessoa lista[T];
	
	fseek(arq, 0, SEEK_SET);
	fread(lista, sizeof(Pessoa), T, arq);
	
	Pessoa temp;
	for(int i = 0; i < T-1; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(strcmp(lista[j].nome, lista[j+1].nome) > 0) {
				temp = lista[j];
				lista[j] = lista[j+1];
				lista[j+1] = temp;
			}
		}
	}
	fseek(arq, 0, SEEK_SET);
	fwrite(lista, sizeof(Pessoa), T, arq);
}

int main() {
	
	FILE* arq = openFile("Pessoa.dat");
	
	do {
		switch(menu()) {
			case 1:
				registrarPessoa(arq);
				break;
			case 2:
				listarPessoa(arq);
				break;
			case 3:
				excluirPessoa(arq, getId());
				break;
			case 4:
				ordenarPessoa(arq);
				break;
			case 0:
				printf("\nPrograma encerrado: ");
				return 0;
			default:
				printf("\nDigite uma opcao valida!");
		}
		
	}while(1);

    //the destroyer of codes
}


