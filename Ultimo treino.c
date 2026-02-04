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
	float preco;
	int quantidade;
	int status;
}Produto; 

FILE* abrirArquivo(char* filename) {
	FILE* arq = fopen(filename, "rb+");
		if(!arq)
			arq = fopen(filename, "wb+");
		if(!arq) {
			printf("O programa nao conseguiu abrir o arquivo\n");
			return 0;
		}
	return arq;
}

int interface(){
	printf("\n==================================TABELINHA DE VENDAS===================================\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar produto\n");
	printf("2 - Listar produtos\n");
	printf("3 - Editar produtos\n");
	printf("4 - Remover produto\n");
	printf("5 - Ordenar tabela por nome\n");
	printf("6 - Ordenar tabela por preco\n");
	printf("7 - Ordenar tabela por quantidade\n");
	
	int opc;
	printf("\n Escolha uma opcao: ");
	scanf("%d", &opc);
	return opc;
}

void setProduto(FILE* arq) {
	Produto p;
	
	fseek(arq, 0, SEEK_END);
	printf("Digite o nome do produto: ");
	scanf(" %[^\n]", p.nome); 
	printf("Digite o preco do produto: ");
	scanf("%f", &p.preco);
	printf("Digite a quantidade que voce vai querer: ");
	scanf("%d", &p.quantidade);
	
	p.id = (ftell(arq) / sizeof(Produto)) + 1;
	p.status = 1;
	
	if(fwrite(&p, sizeof(Produto), 1, arq)) {
		fflush(arq);
		printf("Produto registrado!\n");
	}
	
}

void getProduto(FILE* arq) {
	Produto p;
	fseek(arq, 0, SEEK_SET); 
	
	printf("\n========================================================================================\n");
	printf("%-15s %-15s %-15s %-15s %-10s\n", 
	"ID", "Nome", "Preco", "Quantidade", "Fardo");
	while(fread(&p, sizeof(Produto), 1, arq)) {
		if(p.status == 1) {
			printf("%-15d %-15s %-15.2f %-15d %-10.2f\n", 
			p.id, p.nome, p.preco, p.quantidade, (p.preco * p.quantidade));
		}
	}
	printf("========================================================================================\n");
}

int getId() {
	int id;
	printf("Digite o id do produto: ");
	scanf("%d", &id);
	return id;
}

void editarProduto(FILE* arq, int id){
	Produto p;
	int valido = 0;
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Produto), 1, arq)) {
		if(p.id == id && p.status == 1) {
			
			printf("Novo nome: ");
			scanf(" %[^\n]", p.nome);
			
			printf("Novo Preco: ");
			scanf("%f", &p.preco);
			
			printf("Nova quantidade: ");
			scanf("%d", &p.quantidade); 
			
			fseek(arq, -sizeof(Produto), SEEK_CUR);
			if(fwrite(&p, sizeof(Produto), 1, arq)) {
				fflush(arq);
				printf("Edicao feita com sucesso!");
				valido = 1;
				break;
			}
		}
	}
	if(!valido)
		printf("Digite um id valido!\n");
}

void removerProduto(FILE* arq, int id){
	Produto p;
	int valido = 0;
	fseek(arq, 0, SEEK_SET);
	
	while(fread(&p, sizeof(Produto), 1, arq)) {
		if(p.id == id && p.status == 1) {
			p.status = 0;
			
			fseek(arq, -sizeof(Produto), SEEK_CUR);
			
			if(fwrite(&p, sizeof(Produto), 1, arq)) {
				fflush(arq);
				printf("Produto apagado com sucesso!");
				valido = 1;
				break;
			}
		}
	}
	if(!valido)
		printf("Digite um id valido!\n");
		
}

void ordenarNome(FILE* arq){
	fseek(arq, 0, SEEK_END);
	int size = (ftell(arq) / sizeof(Produto));
	Produto listaP[size];
	
	fseek(arq, 0, SEEK_SET);
	fread(listaP, sizeof(Produto), size, arq);
	//bubble sort
	Produto aux;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size-i-1; j++) {
			if(strcmp(listaP[j].nome, listaP[j+1].nome) > 0) {
				aux = listaP[j];
				listaP[j] = listaP[j+1];
				listaP[j+1] = aux;
			}
		}
	}
	
	fseek(arq, 0, SEEK_SET);
	fwrite(listaP, sizeof(Produto), size, arq);
	fflush(arq);
	printf("Ordenacao realizada com sucesso!");
}

void ordenarPreco(FILE* arq){
	fseek(arq, 0, SEEK_END);
	int T = ftell(arq) / sizeof(Produto);
	Produto lista[T];
	
	fseek(arq, 0, SEEK_SET);
	fread(lista, sizeof(Produto), T, arq);
	Produto aux;
	for(int i = 0; i < T; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(lista[j].preco < lista[j+1].preco) {
				aux = lista[j];
				lista[j] = lista[j+1];
				lista[j+1] = aux;
			}
		}
	}
	
	fseek(arq, 0, SEEK_SET);
	fwrite(lista, sizeof(Produto), T, arq);
	printf("Ordenacao por preco realizada com sucesso!");

}

void ordenarQuant(FILE* arq) {
	fseek(arq, 0, SEEK_END);
	int T = ftell(arq) / sizeof(Produto);
	Produto listaP[T];
	
	fseek(arq, 0, SEEK_SET);
	fread(listaP, sizeof(Produto), T, arq);
	Produto aux;
	for(int i = 0; i < T; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(listaP[j].quantidade < listaP[j+1].quantidade) {
				aux = listaP[j];
				listaP[j] = listaP[j+1];
				listaP[j+1] = aux;
			}
		}
	}
	fseek(arq, 0, SEEK_SET);
	fwrite(listaP, sizeof(Produto), T, arq);
	printf("Ordenacao por quantidade realizada com sucesso!");
}

int main() {
	
	FILE* arq = abrirArquivo("Ultimo treino.dat");
	
	do {
		switch(interface()) {
			case 1:
				setProduto(arq);
				break;
			case 2:
				getProduto(arq);
				break;
			case 3:
				editarProduto(arq, getId());
				break;
			case 4:
				removerProduto(arq, getId());
				break;
			case 5:
				ordenarNome(arq);
				break;
			case 6:
				ordenarPreco(arq);
				break;
			case 7:
				ordenarQuant(arq);
				break;
			case 0:
				printf("Programa encerrado!");
				return 0;
				break;	
			default:
				printf("Digite uma opcao valida!\n");
		}
		
	}while(1);
	
}


