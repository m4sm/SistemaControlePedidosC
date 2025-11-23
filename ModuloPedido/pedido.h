#ifndef PEDIDO_H
#define PEDIDO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char numero_pedido[50];
    char quantidade[50];
} cadastro;

void analisarPedido();
void cadastrar();
void consultar();
void listar();
void remover();


#endif
