#ifndef PEDIDO_H
#define PEDIDO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char numero_pedido[50];
    char nome_cliente[100];
    char produto_pedido[100];
} cadastro;

void cadastrar();
void consultar();
void listar();
void remover();

#endif
