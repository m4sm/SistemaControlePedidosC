#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include "produtos.c"


int main() {
   
    /* do {
        printf("\n=== Sistema de Produtos ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Remover Produto\n");
        printf("4. Listar Produtos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: consultarProduto(); break;
            case 3: removerProduto(); break;
            case 4: listarProdutos(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);*/

    // Area de testes ------------------------------
    Produto p;

    do {
        
        cadastrarProduto("listadeprodutos.csv");  
        
    } while (desejaContinuar());

    consultarProduto("listadeprodutos.csv");

    removerProduto("listadeprodutos.csv");


    // Area de testes ------------------------------

}
