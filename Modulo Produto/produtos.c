#include <stdio.h>
#include <stdlib.h>
#include <produtos.h>

// Função para verificar se há arquivo, se não cria um arquivo .csv já com a strutura escolhida.

void verificarOuCriarArquivo(const char *nomeArquivo, const char *tipo) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL) {
        printf("Arquivo '%s' já existe.\n", nomeArquivo);
        fclose(arquivo);
        return;
    }

    // Se chegou aqui, o arquivo não existe
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    printf("Arquivo '%s' criado com sucesso!\n", nomeArquivo);

    // Cabeçalho de acordo com o tipo
    if (strcmp(tipo, "cliente") == 0) {
        fprintf(arquivo, "id,nome,email\n");
    } 
    else if (strcmp(tipo, "produto") == 0) {
        fprintf(arquivo, "id,nome,preco\n");
    } 
    else if (strcmp(tipo, "pedido") == 0) {
        fprintf(arquivo, "id,id_cliente,id_produto,quantidade\n");
    } 
    else {
        printf("Tipo desconhecido: %s\n", tipo);
    }

    fclose(arquivo);
}
