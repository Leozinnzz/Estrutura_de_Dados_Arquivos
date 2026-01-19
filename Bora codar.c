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
	int modelo;
	char marca[100];
	char nome[100];
	float valor;
	int ano; 
	int flag;
}Carro;

void next() {
	while(getchar() != '\n');
	getchar();
	system("clear");
}

int menu(){
	printf("\n============================================MENU========================================\n");
	printf("0 - Encerrar Programa\n");
	printf("1 - Registrar um carro\n");
	printf("2 - Listar carros registrados\n");
	printf("3 - Excluir um carro\n");
	printf("4 - Editar um carro\n");		
	int opc;

	printf("\nEscolha uma opcao: ");
	scanf("%d", &opc);
	
	return opc;
}

FILE* openfile(char* filename) {
	FILE* arq = fopen(filename, "rb+");
	if(!arq)
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa nao conseguiu abrir o arquivo\n");
		return 0;
	}
	
	return arq;
}

void setCarro(FILE* arq){
	 Carro c; 
	 fseek(arq, 0, SEEK_END);
	 
	 printf("Digite a marca do carro: ");
	 scanf(" %[^\n]s", c.marca); 
	 printf("Digite o nome do carro: ");
	 scanf(" %[^\n]s", c.nome);
	 printf("Digite o preco de fabrica do carro: ");
	 scanf("%f", &c.valor);
	 printf("Digite o ano do carro: ");
	 scanf("%d", &c.ano);
	 c.flag = 1;
	 c.modelo = (ftell(arq) / sizeof(Carro)) + 1;
	
	 if(fwrite(&c,sizeof(Carro), 1, arq)) {
		fflush(arq);
		printf("Carro registrado!");
	}
}

void getCarro(FILE* arq){
	Carro c;
	
	rewind(arq);
	while(fread(&c, sizeof(Carro), 1, arq)) {
		if(c.flag == 1) {
			printf("\nmodelo: %d\n", c.modelo);
			printf("Marca: %s\n", c.marca);
			printf("Nome: %s\n", c.nome);
			printf("Ano: %d\n", c.ano);
		}
	}
}

int getId(){
	int id;
	printf("Digite o ID do carro para exclusao: ");
	scanf("%d", &id);
	return id;
}

void deleteCar(FILE* arq, int id){
	Carro aux;
	int encontrado = 0;
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&aux, sizeof(Carro), 1, arq))  {
		if(aux.modelo == id && aux.flag == 1) {
			aux.flag = 0;
			fseek(arq, -sizeof(Carro), SEEK_CUR);
			
			if(fwrite(&aux, sizeof(Carro), 1, arq)) {
				fflush(arq);
				printf("\nexclusao realizada com sucesso!");
				encontrado = 1;
				break;
			}
		}	
	}
	if(!encontrado)
		printf("Usuario inexistente!");
	
}

void updateCar(FILE* arq, int cod) {
	Carro c; 
	int encontrado = 0;
	
	fseek(arq, 0, SEEK_SET);
	while(fread(&c, sizeof(Carro), 1, arq)) {
		if(c.modelo == cod && c.flag == 1) {
			printf("\n====================Editar o carro por ID====================\n");
			
			printf("Nova marca: ");
			scanf(" %[^\n]s", c.marca);
			
			printf("Novo nome: ");
			scanf(" %[^\n]s", c.nome);
			
			printf("Novo preco de fabrica: ");
			scanf("%f", &c.valor);
			
			printf("Novo ano: ");
			scanf("%d", &c.ano);
			
			fseek(arq, -sizeof(Carro), SEEK_CUR);
			fwrite(&c, sizeof(Carro), 1, arq);
			fflush(arq);
			
			printf("\nCarro editado com sucesso!");
			encontrado = 1;
			break;
		}
	}
	if(!encontrado) {
		printf("\nCarro nao encontrtado! Tente novamente... ");
		next();
	}
}

int main() {
	
	FILE* arq = openfile("boraCodar.txt");
	
	do {
		switch(menu()) {
			case 1: 
				setCarro(arq);
				break;
			case 2: 
				getCarro(arq);
				break;
			case 3: 
				deleteCar(arq, getId());
				break;
			case 4:
				updateCar(arq, getId());
				break;
			case 0:
				printf("\nPrograma encerrado!");
				fclose(arq);
				return 0;
			default:
				printf("\nOpcao invalida! Tente novamente... ");
				next();
		}
	}while(1);

}


