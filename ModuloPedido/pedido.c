#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pedido.h"
#include "../Modulo Cliente/cliente.h"
#include "../Modulo Produto/produtos.h"


void cadastrarPedido() {
    FILE *fp = fopen("pedido.csv", "a+");
    if (fp == NULL) {
        printf("Erro ao abrir pedido.csv\n");
        return;
    }

    // Criar cabeçalho se arquivo estiver vazio
    char teste[5];
    if (fgets(teste, sizeof(teste), fp) == NULL) {
        fprintf(fp, "ID;CLIENTE;PRODUTO;PRECO\n");
    }

    char idPedido[30];
    char codCliente[30];
    int codProduto;

    char nomeCliente[100];
    char nomeProduto[100];
    float precoProduto;

    printf("ID do pedido: ");
    fgets(idPedido, sizeof(idPedido), stdin);
    idPedido[strcspn(idPedido, "\n")] = 0;

    // Cliente
    printf("Código do cliente: ");
    scanf("%s", codCliente);
    getchar();

    if (!buscarCliente(codCliente, nomeCliente)) {
        printf("Cliente não encontrado. Cancelando.\n");
        fclose(fp);
        return;
    }

    // Produto
    printf("Código do produto: ");
    scanf("%d", &codProduto);
    getchar();

    if (!buscarProduto(codProduto, nomeProduto, &precoProduto)) {
        printf("Produto não encontrado. Cancelando.\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "%s;%s;%s;%.2f\n",
        idPedido, nomeCliente, nomeProduto, precoProduto);

    printf("Pedido cadastrado!\n");

    fclose(fp);
}


void consultarPedido(){
    FILE *fp; 
    cadastro c; 
    char numero[50];
    
    int encontrado = 0;
    fp = fopen("pedido.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo");
        }
    
    printf("Digite o numero do pedido que deseja consultar:");
    fgets(numero, 50, stdin);
    numero[strcspn(numero, "\n")] = '\0';
    
    char linha[256];
    fgets(linha, sizeof(linha), fp);
    
    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, " %[^,],%[^,],%[^\n]", c.numero_pedido, c.nome_cliente, c.produto_pedido);
        if(strcmp(c.numero_pedido, numero) == 0){
            printf("\nPedido encontrado:\n");
            printf("Número:%s\nCliente:%s\nProduto:%s", c.numero_pedido, c.nome_cliente, c.produto_pedido);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("Pedido não encontrado.\n");
    }
    fclose(fp);
}
 
void listarPedido(){
    FILE *fp; 
    cadastro c; 
    
    fp = fopen("pedido.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo");
        }
    
    char linha[256];
    fgets(linha, sizeof(linha), fp);
    printf("%s", linha);
    
    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, " %[^,],%[^,],%[^\n]", c.numero_pedido, c.nome_cliente, c.produto_pedido);
        printf("Número: %s | Cliente: %s | Produto: %s\n", c.numero_pedido, c.nome_cliente, c.produto_pedido);
    }
}


void removerPedido(){
    FILE *fp, *temp_fp; 
    cadastro c; 
    char numero[50];
    int encontrado = 0;
    
    fp = fopen("pedido.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    
    temp_fp = fopen("temp_pedido.csv", "w");
    if(temp_fp == NULL){
        printf("Erro ao criar o arquivo temporário");
        fclose(fp);
        return;
    }
    
    printf("Digite o numero do pedido que deseja remover:");
    fgets(numero, 50, stdin);
    numero[strcspn(numero, "\n")] = '\0';
    
    char linha[256];
    fgets(linha, sizeof(linha), fp);
    fprintf(temp_fp, "%s", linha);
    
    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, " %[^,],%[^,],%[^\n]", c.numero_pedido, c.nome_cliente, c.produto_pedido);
        if(strcmp(c.numero_pedido, numero) == 0){
            encontrado = 1;
            printf("Pedido removido com sucesso.\n");
            continue;
        }
        fprintf(temp_fp, "%s", linha);
    }

    if(!encontrado){
        printf("Pedido não encontrado.\n");
    }
    
    fclose(fp);
    fclose(temp_fp);
    
    remove("pedido.csv");
    rename("temp_pedido.csv", "pedido.csv");
}

void menupedido(){
    int opcao;
   
   do{
       printf("\n=============MENU==============\n");
       printf("\n============1-CADASTRE SEU PEDIDO===========\n");
       printf("=============2-CONSULTE O PEDIDO===============\n");
       printf("=============3-LISTE TODOS OS PEDIDOS===========\n");
       printf("=================4-REMOVER PEDIDO==============\n");
       printf("====================5-SAIR================\n");
       printf("Escolha uma opção:\n");
       scanf("%d", &opcao);
       getchar();
       
       switch(opcao){
           case 1:
            cadastrarPedido();
             break;
           
           case 2:
            consultarPedido();
            break;
          
           case 3:
            listarPedido();
            break;
           
           case 4:
            removerPedido();
            break;

           case 5:
            break;
           
           default:
           printf("Nenhum opção selecionada");
           break;
        }
   } while(opcao!= 5);
   
}

int main(){
   menupedido();
   return 0;
    
}

