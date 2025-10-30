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
    
    rewind(fp);
    char primeira_linha[100];
    if (fgets(primeira_linha, 100, fp) == NULL) {
        fprintf(fp, "ID, CLIENTE, PRODUTO\n");
    };
    
    printf("Digite o Pedido que deseja cadastrar:\n");
    fgets(c.numero_pedido, 50, stdin);
    c.numero_pedido[strcspn(c.numero_pedido, "\n")] = '\0';
    
    printf("\nNome do cliente:\n");
    fgets(c.nome_cliente, 100, stdin);
    c.nome_cliente[strcspn(c.nome_cliente, "\n")] = '\0';
    
    printf("\nProduto solicitado:\n");
    fgets(c.produto_pedido, 100, stdin);
    c.produto_pedido[strcspn(c.produto_pedido, "\n")] = '\0';
    
    fprintf(fp, "%s, %s,  %s\n", c.numero_pedido, c.nome_cliente, c.produto_pedido);

    fclose(fp);
    
    
    return 0;

}

