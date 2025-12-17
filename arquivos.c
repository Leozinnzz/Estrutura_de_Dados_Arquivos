/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>

//fseek(f, 0, SEEK_END);
//fflush(f);
//fwrite
//ftell


typedef struct {
	char nome[100];
	char email[100];
	int idade;
}Pessoa;

int interface() {
	printf("1 - Cadastrar usuario: ");
	printf("2 - Listar Usuarios: ");
	printf("3 - excluir usuario: ");
	printf("0 - Sair");
	
	int opc; 
	
	printf("Digite uma opção: ");
	scanf(" %d", &opc);
	return opc;
}

Pessoa setPessoa(FILE* f) {
	Pessoa p ;
	//int size = ftell(f);
	//fseek(f);
	printf("Digite o nome: ");
	scanf(" %[^\n]s", p.nome);
	printf("Digite o email: ");
	scanf(" %[^\n]s", p.email);
	printf("Digite a idade: ");
	scanf(" %d", &p.idade);
	return p;
}

FILE* openFile(char* filename) {
	FILE* arquivo = fopen(filename, "rb+");
	if(!arquivo)
		arquivo = fopen(filename, "wb+");
	if(!arquivo)
		printf("Falha na abertura do arquivo");
	return arquivo;
}

int main() {
    int num = 100;
  
    FILE* myf = openFile("MyFile.txt");
    if(!myf)
		printf("Deu errado!");
	
	
	fwrite(&num, sizeof(int), 1,myf);
	
	
    switch(interface()) {
		case 1:
			
			
	}
}


