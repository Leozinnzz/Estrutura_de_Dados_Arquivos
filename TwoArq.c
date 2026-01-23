/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int id;
	char nome[100];
	int idade;
	int ativo;
}Pessoa;

typedef struct{
	int id;
	char marca[100];
	char nome[100];
	float valor;
	int idPessoa;
	int ativo;
}Carro;

FILE* openfile(char* filename){
	FILE* arq = fopen(filename, "rb+");
	if(!arq)
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa nao conseguiu abrir o arquivo\n");
		return 0;
	}
	return arq;
}

int interface() {
	printf("\n------------------------------PESSOA------------------------------\n");
	printf("1 - Cadastrar pessoa\n");
	printf("2 - Listar pessoas\n");
	printf("3 - Excluir Pessoas\n");
	printf("4 - Editar uma Pessoa\n");
	printf("\n------------------------------CARRO------------------------------\n");
	printf("5 - Cadastrar um carro\n");
	printf("6 - Listar carros\n");
	printf("7 - Excluir um carro\n");
	printf("8 - Editar um carro\n");
	printf("0 - Sair\n");
	
	int opc;
	printf("Escollha uma opcao: ");
	scanf("%d", &opc);

	return opc;
}

void setPessoa(FILE* arq) {
	Pessoa p;
	
	fseek(arq, 0, SEEK_END);
	printf("Digite o nome da pessoa: ");
	scanf(" %[^\n]", p.nome);
	printf("Digite a idade da pessoa: ");
	scanf("%d", &p.idade);
	p.id = (ftell(arq) / sizeof(Pessoa)) + 1;
	p.ativo = 1;
	
	if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
		fflush(arq);
		printf("\nPessoa Registrada!\n");
	}
}

void getPessoa(FILE* arq) {
	Pessoa p;
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Pessoa), 1, arq)) 
		if(p.ativo)
			printf("\nId %d\nNome: %s\nIdade %d\n", p.id, p.nome, p.idade);
}

int getId() {
	int id;
	printf("\nDigite o id: ");
	scanf("%d", &id);
	return id;
}

void excluirPessoa(FILE* arq,int cod) {
	Pessoa p;
	int encontrado = 0;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&p, sizeof(Pessoa), 1, arq)) {
		if(p.id == cod && p.ativo) {
			p.ativo = 0;
			fseek(arq, -sizeof(Pessoa), SEEK_CUR);
			if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
				fflush(arq);
				encontrado = 1;
				printf("exclusao realizada com sucesso!\n");
				break;
			}
		}
	}
	if(!encontrado) {
		printf("Pessoa inexistente!\n");
	}
}

void editarPessoa(FILE* arq, int id) {
	Pessoa p;
	int encontrado = 0;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&p, sizeof(Pessoa), 1, arq)) {
		if(p.id == id && p.ativo) {
			printf("\n=============================Editar Usuario Cadastrado=============================\n");
			
			printf("Novo nome: "); 
			scanf(" %[^\n]", p.nome);
			
			printf("Nova idade: ");
			scanf("%d", &p.idade);
			
			//voltar cursor
			fseek(arq, -sizeof(Pessoa), SEEK_CUR);
			//sobrescrever
			if(fwrite(&p, sizeof(Pessoa), 1, arq)) {
				fflush(arq);
				encontrado = 1;
				printf("edicao realizada com sucesso!\n");
				break;
			}
		}
	}
	if(!encontrado) {
		printf("Usuario inexistente!");
	}
}

void setCarro(FILE* arq){ 
	Carro c; 
	
	fseek(arq, 0, SEEK_SET);
	printf("Digite a marca do carro: ");
	scanf(" %[^\n]", c.marca);
	
	printf("Digita o nome do carro: ");
	scanf(" %[^\n]", c.nome);
	
	printf("Digite o preco do carro: ");
	scanf("%f", &c.valor);
	
	//terminar amanha
}


int main() {
	
	FILE* arqP = openfile("Pessoas.dat");
	FILE* arqC = openfile("Carros.dat");
  
  do {
	  switch(interface()) {
		case 1:
			setPessoa(arqP);
			break;
		case 2:
			getPessoa(arqP);
			break;
		case 3:
			excluirPessoa(arqP, getId());
			break;
		case 4:
			editarPessoa(arqP, getId());
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 0:
			return 0;
		default:
			printf("Digite uma opcao valida!");
		  
	  }
	  
  }while(1);


}


