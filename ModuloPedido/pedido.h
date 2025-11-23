#ifndef PEDIDO_H
#define PEDIDO_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char numero_pedido[50];
    char idcliente[50];
    char idproduto[50];
    char quantidade[50];
    char nome_cliente[50];
    char nome_produto[50];
    float preco_produto;
    float preco_total;

} pedido;

void analisarPedido();
void cadastrarPedido();
void consultarPedido();
void listarPedido();
void removerPedido();


#endif
