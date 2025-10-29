#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
     char cadastrar_Pedido[50];
     char pedidos_aceito[50];
} cadastro;

int main(){
    cadastro c;

    FILE *fp;

    fp = fopen("pedido.csv", "a+");

    printf("Digite o Pedido que deseja cadastrar:");
    gets(c.cadastrar_Pedido, 50, stdin);

    fprintf(fp, "%s\n", c.cadastrar_Pedido);


}

