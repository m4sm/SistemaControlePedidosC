#ifndef PRODUTOS_H
#define PRODUTOS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

typedef struct {
    int codigo;
    char descricao[100];
    float preco;
    int quantidade;
} Produto;

// funções basicas 
void cadastrarProduto(const char *nomeArquivo);
void consultarProduto(const char *nomeArquivo);
void removerProduto(const char *nomeArquivo);
void listarProdutos(const char *nomeArquivo);
Produto buscarProdutos();

// Funções auxiliares de manipulação
void lerProduto(Produto *p);
int desejaContinuar(); 

#endif
