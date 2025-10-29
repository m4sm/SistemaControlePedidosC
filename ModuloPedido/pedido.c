#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
     char numero_pedido[50];
     char nome_cliente[100];
     char produto_pedido[100];
    
     
} cadastro;

int main(){
    cadastro c;

    FILE *fp;

    fp = fopen("pedido.csv", "a+");

    printf("Digite o Pedido que deseja cadastrar:");
    gets(c.numero_pedido, 50, stdin);

    printf("Nome do cliente:");
    gets(c.nome_cliente, 100, stdin);

    printf("Produto solicitado:");
    gets(c.produto_pedido, 100, stdin);

    fprintf(fp, "%s, %s,  %s\n", c.numero_pedido, c.nome_cliente, c.produto_pedido);

    


}

