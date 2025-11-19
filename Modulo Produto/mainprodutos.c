#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include "produtos.c"


int main() {
    Produto p;
    int opcao;
   
    do {
        printf("\n=== Sistema de Produtos ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Remover Produto\n");
        printf("4. Listar Produtos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();


        switch (opcao) {
            case 1: {
                do {
                    cadastrarProduto("listadeprodutos.csv");
                } while (desejaContinuar());
                break;
                }
            case 2: consultarProduto("listadeprodutos.csv"); break;
            case 3: removerProduto("listadeprodutos.csv"); break;
            case 4: listarProdutos("listadeprodutos.csv"); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

}
