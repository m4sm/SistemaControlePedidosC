#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pedido.h"
#include "../Modulo Cliente/cliente.h"
#include "../Modulo Produto/produtos.h"

void cadastrarPedido() {
    char idPedido[30];
    char codCliente[30];
    char nomeCliente[100];

    int codProduto;
    char nomeProduto[100];
    float precoProduto;

    int quantidade;

    FILE *fp = fopen("pedido.csv", "a+");
    if (!fp) {
        printf("Erro ao abrir pedido.csv\n");
        return;
    }

    // CABEÇALHO
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "ID;Cliente;Produto;Preco;Quantidade;Total\n");
    }

    printf("Digite o número do pedido: ");
    scanf("%s", idPedido);

    printf("Código do cliente: ");
    scanf("%s", codCliente);

    if (!buscarCliente(codCliente, nomeCliente)) {
        printf("Cliente não encontrado!\n");
        fclose(fp);
        return;
    }

    printf("Código do produto: ");
    scanf("%d", &codProduto);

    if (!buscarProduto(codProduto, nomeProduto, &precoProduto)) {
        printf("Produto não encontrado!\n");
        fclose(fp);
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &quantidade);

    float total = quantidade * precoProduto;

    fprintf(fp, "%s;%s;%s;%.2f;%d;%.2f\n",
            idPedido, nomeCliente, nomeProduto, precoProduto, quantidade, total);

    printf("\nPedido cadastrado com sucesso!\n");
    printf("Cliente: %s\n", nomeCliente);
    printf("Produto: %s (R$ %.2f)\n", nomeProduto, precoProduto);
    printf("Total: R$ %.2f\n", total);

    fclose(fp);
}

void analisarCliente(){

}

void consultarPedido(){
    FILE *fp; 
    cadastro c; 
    char numero[50];
    int encontrado = 0;

    fp = fopen("pedido.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    printf("Digite o numero do pedido que deseja consultar:");
    getchar(); 
    fgets(numero, 50, stdin);
    numero[strcspn(numero, "\n")] = '\0';

    char linha[256];

    fgets(linha, sizeof(linha), fp); // pula cabeçalho

    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, " %[^;];", c.numero_pedido);

        if(strcmp(c.numero_pedido, numero) == 0){
            printf("\nPedido encontrado:\n");
            printf("Número: %s\n", c.numero_pedido);
            printf("Linha completa: %s\n", linha);
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
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    char linha[256];
    fgets(linha, sizeof(linha), fp);
    printf("%s", linha);
    
    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, " %[^;];", c.numero_pedido);
        printf("Número: %s\n", c.numero_pedido);
    }

    fclose(fp);
}

void removerPedido(){
    FILE *fp, *temp_fp; 
    cadastro c; 
    char numero[50];
    int encontrado = 0;
    
    fp = fopen("pedido.csv", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    temp_fp = fopen("temp_pedido.csv", "w");
    if(temp_fp == NULL){
        printf("Erro ao criar o arquivo temporário\n");
        fclose(fp);
        return;
    }
    
    printf("Digite o numero do pedido que deseja remover:");
    getchar();
    fgets(numero, 50, stdin);
    numero[strcspn(numero, "\n")] = '\0';
    
    char linha[256];
    fgets(linha, sizeof(linha), fp);
    fprintf(temp_fp, "%s", linha);
    
    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, " %[^;];", c.numero_pedido);

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

void menuPedido(){
    int opcao;
   
   do{
       printf("\n=============MENU==============\n");
       printf("\n1-CADASTRE SEU PEDIDO\n");
       printf("2-CONSULTE O PEDIDO\n");
       printf("3-LISTE TODOS OS PEDIDOS\n");
       printf("4-REMOVER PEDIDO\n");
       printf("5-SAIR\n");
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
   menuPedido();
   return 0;
}
