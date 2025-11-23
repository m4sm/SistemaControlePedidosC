#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct {
    int codigo;
    char descricao[100];
    float preco;
    int quantidade;
} Produto;

// Funções básicas

void cadastrarProduto();
void consultarProduto();
void removerProduto();
void listarProdutos();
//funções gerais de manipulação
void lerProduto();

#endif
