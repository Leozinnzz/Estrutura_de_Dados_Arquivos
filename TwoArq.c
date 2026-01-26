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


void next() {
	while(getchar() != '\n');
	getchar();
	system("clear");
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
	printf("7 - Editar um carro\n");
	printf("8 - Excluir um carro\n");
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
		next();
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
				printf("exclusao realizada com sucesso! \n");
				next();
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
				encontrado = printf("edicao realizada com sucesso! \n");
				next();
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
	
	fseek(arq, 0, SEEK_END);
	printf("Digite a marca do carro: ");
	scanf(" %[^\n]", c.marca);
	
	printf("Digita o nome do carro: ");
	scanf(" %[^\n]", c.nome);
	
	printf("Digite o preco do carro: ");
	scanf("%f", &c.valor);
	
	c.id = (ftell(arq) / sizeof(Carro)) + 1;
	
	if(fwrite(&c, sizeof(Carro), 1, arq)) {
		fflush(arq);
		printf("Carro registrado! ");
		next();
	}

}

void getCarro(FILE* arq) {
	Carro c;
	
	fseek(arq, 0, SEEK_SET); 
	while(fread(&c, sizeof(Carro), 1, arq)) 
		if(c.ativo)
			printf("\nID: %d\nMarca: %s\nNome: %s\nPreco: %.2f\n", c.id, c.marca, c.nome, c.valor);
	
}


void editarCarro(FILE* arq, int id) {
	Carro c;
	int flag = 0;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&c, sizeof(Carro), 1, arq)) {
		if(c.id == id && c.ativo) {
			
			printf("Nova marca: ");
			scanf(" %[^\n]", c.marca);
			
			printf("Novo nome: ");
			scanf(" %[^\n]", c.nome);
			
			printf("Novo valor: ");
			scanf("%f", &c.valor);
			
			//voltar cursor
			fseek(arq, -sizeof(Carro), SEEK_CUR);
			//escrever no arquivo
			if(fwrite(&c, sizeof(Carro), 1, arq)) {
				fflush(arq);
				flag = 1; 
				printf("Edicao realizada com sucesso! ");
				next();
				break;
			}
		}
	}
	if(!flag)
		printf("/nCarro nao encontrado!");
	
}

void excluirCarro(FILE* arq, int cod) {
	Carro c;
	int encontrado = 0;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&c, sizeof(Carro), 1, arq)) {
		if(c.id == cod && c.ativo) {
			c.ativo = 0;
			//voltar cursor
			fseek(arq, -sizeof(Carro), SEEK_CUR);
			//escrever no arquivo
			if(fwrite(&c, sizeof(Carro), 1, arq)) {
				fflush(arq);
				encontrado = 1;
				printf("Exclusao concluida com sucesso! ");
				next();
				break;
			}
		}
	}
	if(!encontrado) 
		printf("\nCarro inexistente!");
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
			setCarro(arqC);
			break;
		case 6:
			getCarro(arqC);
			break;
		case 7:
			editarCarro(arqC, getId());
			break;
		case 8:
			excluirCarro(arqC, getId());
			break;
		case 0:
			printf("Programa encerrado!");
			fclose(arqP);
			fclose(arqC);
			return 0;
		default:
			printf("Digite uma opcao valida!");
		  
	  }
	  
  }while(1);


}


