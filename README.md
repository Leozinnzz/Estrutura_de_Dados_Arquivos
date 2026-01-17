💾 Persistência de Dados em Arquivos (C)

A persistência em arquivos permite salvar dados em disco, garantindo que as informações continuem disponíveis mesmo após o programa ser encerrado.
Em C, isso é feito utilizando ponteiros para arquivos (FILE *) e funções da biblioteca <stdio.h>.

🧰 Principais Comandos de Arquivos em C

fopen() → abre ou cria um arquivo

fclose() → fecha o arquivo

fprintf() → escreve texto formatado em arquivo

fscanf() → lê texto formatado de um arquivo

fwrite() → grava dados binários (ex: structs)

fread() → lê dados binários

feof() → verifica fim do arquivo

🧱 Exemplo de Struct com Persistência em Arquivo

Exemplo simples salvando e lendo uma struct em arquivo binário:

```c
#include <stdio.h>

struct Pessoa {
    char nome[50];
    int idade;
    float altura;
};

int main() {
    struct Pessoa p1 = {"João", 20, 1.75};
    struct Pessoa p2;

    FILE *arquivo;

    // Escrita no arquivo
    arquivo = fopen("pessoas.dat", "wb");
    fwrite(&p1, sizeof(struct Pessoa), 1, arquivo);
    fclose(arquivo);

    // Leitura do arquivo
    arquivo = fopen("pessoas.dat", "rb");
    fread(&p2, sizeof(struct Pessoa), 1, arquivo);
    fclose(arquivo);

    printf("Nome: %s\n", p2.nome);
    printf("Idade: %d\n", p2.idade);
    printf("Altura: %.2f\n", p2.altura);

    return 0;
}

```

📝 Modos de Abertura de Arquivos
Modo	Descrição
"r"	Leitura
"w"	Escrita (apaga o conteúdo)
"a"	Escrita (adiciona no final)
"rb"	Leitura binária
"wb"	Escrita binária
"ab"	Escrita binária em modo append
🎯 Por que usar Arquivos com Structs?

💾 Armazenar dados permanentemente

📊 Simular bancos de dados simples

📁 Trabalhar com grandes volumes de informação

🧠 Aprender conceitos fundamentais usados no mercado
