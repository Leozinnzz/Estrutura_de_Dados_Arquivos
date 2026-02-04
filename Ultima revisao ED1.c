/*
============= Leozinzz =================
============= CachyOS --%d/%m/%Y-- =================
============= LI4ever ======================
============= Made-by-Leozinzz-Desktop ===============
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {R=1, D=2};


typedef struct {
	int id;
	char descricao[100];
	float valor;
	int tipo;
	int dia;
	int status;
}Lancamento;


FILE* openFile(char* filename) {
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
	printf("\n========================MENU========================\n");
	printf("1 - Cadastrar Receita\n");
	printf("2 - Cadastrar Despesa\n");
	printf("3 - Pagar Despesa\n");
	printf("4 - Extrato Mensal\n");
	int opc;
	printf("Digite uma opcao: ");
	scanf("%d", &opc);
	return opc;
}


void cadastro(FILE* arq, int tipo) {
	Lancamento lanc;
	fseek(arq, 0, SEEK_END);
	
	if(tipo == R) {
		lanc.tipo = 'R';
		printf("\nDigite a descricao dessa receita: ");
		scanf(" %[^\n]", lanc.descricao);
		printf("Digite o valor da receita: ");
		scanf("%f", &lanc.valor);
		printf("Digite o dia da receita: ");
		scanf("%d", &lanc.dia);
		
		lanc.id = (ftell(arq) / sizeof(Lancamento)) + 1;
		lanc.status = 1;
		
		if(fwrite(&lanc, sizeof(Lancamento), 1, arq)) {
			fflush(arq);
			printf("Receita registrada!\n");
		}
	}
	
	else if(tipo == D) {
		lanc.tipo = 'D';
		printf("\nDigite a descricao dessa despesa: ");
		scanf(" %[^\n]", lanc.descricao);
		printf("Digite o valor da despesa: ");
		scanf("%f", &lanc.valor);
		printf("Digite o dia de vencimento da despesa: ");
		scanf("%d", &lanc.dia);
		
		lanc.id = (ftell(arq) / sizeof(Lancamento)) + 1;
		lanc.status = 0;
		
		if(fwrite(&lanc, sizeof(Lancamento), 1, arq)) {
			fflush(arq);
			printf("Despesa registrada!\n");
		}
	} 
}

void pagarDespesa(FILE* arq) {
	fseek(arq, 0, SEEK_END);
	int T = ftell(arq) / sizeof(Lancamento);
	Lancamento list[T];
	
	fseek(arq, 0, SEEK_SET);
	fread(list, sizeof(Lancamento), T, arq);
	//ordenar
	for(int i = 0; i < T; i++) {
		for(int j = 0; j < T-i-1; j++) {
			if(list[j].dia > list[j+1].dia) {
				Lancamento aux;
				aux = list[j];
				list[j] = list[j+1];
				list[j+1] = aux;
			}
		}
	}
	
	printf("\n%-4s %-6s %-8s %-16s %-10s %-10s\n",
	"ID", "Dia", "TIPO", "Descricao", "Status", "Valor");
	for(int i = 0; i < T; i++) 
		if(list[i].tipo == 'D' && list[i].status == 0) {
			printf("%-4d %-6d %-8c %-16s %-10s %-8.2f\n",
			list[i].id,
			list[i].dia,
			list[i].tipo,
			list[i].descricao,
			"X",
			list[i].valor);
		}
		
		
	int id;
	printf("\nDigite o id da despesa que queira pagar: ");
	scanf("%d", &id);
	
	int encontrado = 0;
	fseek(arq, 0, SEEK_SET);
	while(fread(list, sizeof(Lancamento), 1, arq)) {
		if(list->id == id && list->status == 0) {
			list->status = 1;
			
			fseek(arq, -sizeof(Lancamento), SEEK_CUR); 
			if(fwrite(list, sizeof(Lancamento), 1, arq)) {
				printf("Despesa paga!\n");
				fflush(arq);
				encontrado = 1;
				break;
			}
		}
	}
	if(!encontrado)
		printf("Despesa nao encontrada! Digite um id valido!\n");
}

void extratoMensal(FILE* arq) {
	fseek(arq, 0, SEEK_END);
	int tam = ftell(arq) / sizeof(Lancamento); 
	Lancamento papeis[tam];
	
	fseek(arq, 0, SEEK_SET);
	fread(papeis, sizeof(Lancamento), tam, arq);
	Lancamento ajuda;
	//pelo dia
	for(int i = 0; i < tam; i++) {
		for(int j = 0; j < tam-i-1; j++) {
			if(papeis[j].dia > papeis[j+1].dia) {
				ajuda = papeis[j];
				papeis[j] = papeis[j+1];
				papeis[j+1] = ajuda;
			}
		}
	}
	
	//ordenar pelo tipo
	for(int i = 0; i < tam; i++) {
		for(int j = 0; j < tam-i-1; j++) {
			if(papeis[j].tipo == 'D' && papeis[j+1].tipo == 'R') {
				ajuda = papeis[j];
				papeis[j] = papeis[j+1];
				papeis[j+1] = ajuda;
			}
		}
	}
	
	printf("%-6s %-8s %-16s %-10s %-8s\n", 
	"TIPO", "Dia", "Descricao", "Status", "Valor");
	
	float totalR = 0, totalD = 0, despPagas = 0; 
	for(int i = 0; i < tam; i++) {
		if(papeis[i].tipo == 'R') {
			totalR += papeis[i].valor;
		}
		else if(papeis[i].tipo == 'D') {
			if(!papeis[i].status)
				totalD += papeis[i].valor;
			else
				despPagas += papeis[i].valor;
		}
		
		printf("%-6c %02d      %-16s %-10s %-8.2f\n", 
		papeis[i].tipo,
		papeis[i].dia,
		papeis[i].descricao,
		papeis[i].status ? "V" : "X",
		papeis[i].valor);
	}
	
	printf("\nTotal de receitas: %.2f\n", totalR);
	printf("Despesas a pagar: %.2f\n", totalD);
	printf("Despesas pagas: %.2f\n", despPagas);
	printf("Saldo disponivel: %.2f\n", totalR - totalD - despPagas);
	
}



int main() {
	
	FILE* arq = openFile("Ultima_revisao.dat");
	
	do {
		switch(menu()) {
			case 1:
				cadastro(arq, R);
				break;
			case 2:
				cadastro(arq, D);
				break;
			case 3:
				pagarDespesa(arq);
				break;
			case 4:
				extratoMensal(arq);
				break;
			case 0:
				printf("Programa encerrado!\n");
				fclose(arq);
				return 0;
			default:
				printf("Digite uma opcao valida!\n");
		}
	}while(1);

    //the destroyer of codes
}


