/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum {R = 1, D = 2};


typedef struct {
	int id;
	char descricao[100];
	float valor;
	char tipo;
	int dia;
	int status;
}Lancamento;

FILE* openFile(char* filename) {
	FILE* arq = fopen(filename, "rb+");
	if(!arq)
		arq = fopen(filename, "wb+");
	if(!arq) {
		printf("O programa nao conseguiu acessar o arquivo!");
		return 0;
	}
	return arq;
}

int menu() {
	printf("\n==========MENU==========\n");
	printf("0 - Sair\n");
	printf("1 - Cadastrar Receita\n");
	printf("2 - Cadastrar despesa\n");
	printf("3 - Pagar despesa\n");
	printf("4 - Extrato mensal\n");
	int opc;
	
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opc);
	return opc;
}


void cadastro(FILE* arq, int opc) {
	Lancamento lc;
	fseek(arq, 0, SEEK_END);
	
	if(opc == R) {
		lc.tipo = 'R';
		printf("Digite a descricao dessa receita: ");
		scanf(" %[^\n]s", lc.descricao);
		
		printf("Digite o valor da receita: ");
		scanf("%f", &lc.valor);
		
		printf("Digite o dia do mes da receita: ");
		scanf("%d", &lc.dia);
		
		lc.id = (ftell(arq) / sizeof(Lancamento)) + 1;
		lc.status = 1;
		
		
		if(fwrite(&lc, sizeof(Lancamento), 1, arq)) {
			fflush(arq);
			printf("Receita registrada!");
		}
	}
	else if(opc == D) {
		lc.tipo = 'D';
		printf("Digite a descricao dessa despesa: ");
		scanf(" %[^\n]s", lc.descricao);
		
		printf("Digite o valor da despesa: ");
		scanf("%f", &lc.valor);
		
		printf("Digite o dia do mes da despesa: ");
		scanf("%d", &lc.dia);
		
		lc.id = (ftell(arq) / sizeof(Lancamento)) + 1;
		lc.status = 0;
		
		if(fwrite(&lc, sizeof(Lancamento), 1, arq)) {
			fflush(arq);
			printf("Despesa cadastrada!");
		}
	}
}

void pagarDespesas(FILE* arq){
	fseek(arq, 0, SEEK_END);
	int size = ftell(arq) / sizeof(Lancamento);
	
	Lancamento lista[size];
	
	fseek(arq, 0, SEEK_SET);
	fread(lista, sizeof(Lancamento), size, arq);
	Lancamento temp;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size - i - 1; j++) {
			if(lista[j].dia > lista[j+1].dia) {
				temp = lista[j];
				lista[j] = lista[j+1];
				lista[j+1] = temp;
			}
		}
	}
	printf("\n%-4s %-6s %-5s %-16s %-10s %-10s\n",
       "ID", "Tipo", "Dia", "Descricao", "Status", "Valor");
	
	for(int i = 0; i < size; i++) { 
		if(lista[i].tipo == 'D' && lista[i].status == 0) {
			printf("%-4d %-6c %-5d %-16s %-10s R$ %-8.2f\n",
			lista[i].id,
			lista[i].tipo,
			lista[i].dia,
			lista[i].descricao,
			"X",
			lista[i].valor);
		}
	}
	
	int id;
	printf("\nDigite o ID da Despesa que deseja quitar: ");
	scanf("%d", &id);
	
	int flag = 0;
	fseek(arq, 0, SEEK_SET);
	while(fread(lista, sizeof(Lancamento), 1, arq))
		if(lista->id == id && lista->status == 0) {
			lista->status = 1;
			
			fseek(arq, -sizeof(Lancamento), SEEK_CUR);
			if(fwrite(lista, sizeof(Lancamento), 1, arq)) {
				fflush(arq);
				printf("\nDespesa quitada");
				flag = 1;
				break;
			}
		}
	if(!flag)
		printf("Digite um id valido!");
}

void extratoMensal(FILE* arq){
	fseek(arq, 0, SEEK_END);
	int T = ftell(arq) / sizeof(Lancamento);
	
	Lancamento lista[T];
	fseek(arq, 0, SEEK_SET);
	fread(lista, sizeof(Lancamento), T, arq);
	Lancamento lcaux;
	
	//ordenar pelo dia
	for(int i = 0; i < T; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(lista[j].dia > lista[j+1].dia) {
				lcaux = lista[j];
				lista[j] = lista[j+1];
				lista[j+1] = lcaux;
			}
		}
	}
	//ordenar pelo tipo
	for(int i = 0; i < T; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(lista[j].tipo == 'D' && lista[j+1].tipo == 'R') {
			lcaux = lista[j];
			lista[j] = lista[j+1];
			lista[j+1] = lcaux;
			}
		}
	}
	
	printf("\n%-6s %-5s %-20s %-10s %-10s\n",
	"TIPO", "Dia", "Descricao", "Status", "Valor");
	
	float sumR = 0, sumD = 0, despPagas = 0;
	for(int i = 0; i < T; i++) {
		if(lista[i].tipo == 'R')  {
			sumR += lista[i].valor;
		}
		else if(lista[i].tipo == 'D') {
			if(!lista[i].status)
				sumD += lista[i].valor;
			else 
				despPagas += lista[i].valor;
		}
		
		printf("%-6c %-5d %-20s %-10s %-10.2f\n",
		lista[i].tipo, lista[i].dia, lista[i].descricao, lista[i].status ? "V" : "X",
		lista[i].valor);
		
	}
	printf("\nTotal de Receitas: %.2f", sumR);
	printf("\nDespesas a pagar: %.2f", sumD);
	printf("\nDespesas pagas: %.2f", despPagas);
	printf("\nSaldo disponivel: %.2f\n", sumR - despPagas - sumD);
}
int main() {
    
    FILE* arq = openFile("UltimoDojo.dat");
    
	do {
		switch(menu()){
			case 1:
				cadastro(arq, R);
				break;
			case 2:
				cadastro(arq, D);
				break;
			case 3:
				pagarDespesas(arq);
				break;
			case 4:
				extratoMensal(arq);
				break;
			case 0:
				fclose(arq);
				return 0;
			default:
				printf("Escolha uma opcao valida!");
		}
	}while(1);

    //the destroyer of codes
}


