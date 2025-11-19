#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include <ctype.h>


//Função "Deseja Continuar?"// Usada em laços de repetição como condição de parada.
int desejaContinuar() {
    char resposta;
    do {
        printf("Deseja Continuar? (S/N): ");
        scanf("%c", &resposta);
        resposta = toupper(resposta);
        getchar();

        if(resposta == 'S')
            return 1;
        else if( resposta == 'N')
            return 0;
        else
            printf("Opção invalida! Digite S ou N. \n");

    } while (1);
    getchar();
}

// Lê os dados de um produto pelo teclado e armazena em uma struct Produto. Usa ponteiro.
void lerProduto(Produto *p) {
        
   char entrada[100]; // buffer temporário para leitura

    printf("Digite o código: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // remove o \n
    p->codigo = atoi(entrada); // converte string para int

    printf("Digite a descrição: ");
    fgets(p->descricao, sizeof(p->descricao), stdin);
    p->descricao[strcspn(p->descricao, "\n")] = '\0'; // remove o \n

    printf("Digite a quantidade: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';
    p->quantidade = atoi(entrada);

    printf("Digite o preço: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';
    p->preco = atof(entrada); // converte string para float
}

// Função para escrever o produto no arquivo
void cadastrarProduto(const char *nomeArquivo){
    Produto p;

    lerProduto(&p);

    //Adiciona com append no arquivo
    FILE *arq = fopen(nomeArquivo, "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s!\n", nomeArquivo);
        return;
    }

    // Grava o produto no arquivo CSV
    fprintf(arq, "%d,%s,%d,%.2f\n",
            p.codigo, p.descricao, p.quantidade, p.preco);

    fclose(arq);

    printf("\nProduto cadastrado com sucesso!\n");
}

// Função para consultar o produto
void consultarProduto(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int codigoBusca;
    printf("Digite o código do produto a consultar: ");
    scanf("%d", &codigoBusca);
    getchar(); // limpa o \n

    Produto p;
    int encontrado = 0;

    // Lê linha por linha do CSV
    while (fscanf(fp, "%d,%49[^,],%d,%f\n", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
        if (p.codigo == codigoBusca) {
            printf("\n=== Produto Encontrado ===\n");
            printf("Código: %d\n", p.codigo);
            printf("Descrição: %s\n", p.descricao);
            printf("Quantidade: %d\n", p.quantidade);
            printf("Preço: %.2f\n", p.preco);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nProduto com código %d não encontrado.\n", codigoBusca);
    }

    fclose(fp);
}

//consultar produtos

void removerProduto(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        return;
    }

    int codigoRemover;
    printf("Digite o código do produto a remover: ");
    scanf("%d", &codigoRemover);
    getchar(); // limpar \n

    Produto p;
    int encontrado = 0;

    // Lê linha por linha do arquivo original
    while (fscanf(fp, "%d,%49[^,],%d,%f\n",
                  &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {

        if (p.codigo == codigoRemover) {
            encontrado = 1;
            continue; // não grava no arquivo temporário
        }

        // Regrava linha no arquivo temporário
        fprintf(temp, "%d,%s,%d,%.2f\n",
                p.codigo, p.descricao, p.quantidade, p.preco);
    }

    fclose(fp);
    fclose(temp);

    if (encontrado) {
        remove(nomeArquivo);
        rename("temp.csv", nomeArquivo);
        printf("Produto removido com sucesso!\n");
    } else {
        remove("temp.csv");
        printf("Produto com código %d não encontrado.\n", codigoRemover);
    }
}

//função para listar produto.
void listarProdutos(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Nenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        return;
    }

    Produto p;
    int count = 0;

    printf("\n=== Lista de Produtos ===\n");

    // Lê linha por linha do CSV
    while (fscanf(fp, "%d,%49[^,],%d,%f\n",
                  &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {

        printf("\nProduto %d:\n", ++count);
        printf("  Código     : %d\n", p.codigo);
        printf("  Descrição  : %s\n", p.descricao);
        printf("  Quantidade : %d\n", p.quantidade);
        printf("  Preço      : R$ %.2f\n", p.preco);
    }

    if (count == 0) {
        printf("Nenhum produto encontrado.\n");
    }

    fclose(fp);
}
