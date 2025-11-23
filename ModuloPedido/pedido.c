#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pedido.h"
#include "../Modulo Cliente/cliente.h"
#include "../Modulo Produto/produtos.h"

void cadastrarPedido(){
    FILE *fp;
    cadastro c;
    int codigo_cadas = 0;
    pessoa c;
    Produtos p;
    
    fp = fopen("pedido.csv", "a+");
     
     if(fp == NULL){
         printf("Erro ao abrir o arquivo");
        
     }

    printf("Digite o Indentificador do Pedido que deseja cadastrar:\n");
    fgets(c.numero_pedido, 50, stdin);
    c.numero_pedido[strcspn(c.numero_pedido, "\n")] = '\0';
        
    while(fgets(texto, 1000, fp)){

        char codigo_existente[30];
        sscanf(texto, "%[^,]", codigo_existente);

        if(strcmp(c.numero_pedido, codigo_existente) == 0){
            codigo_cadas = 1;
            break;
        }
    }
        if(codigo_cadas) {
        printf("Este Identificador ja existe. Digite outro. \n");
        }
        else {
        printf("Identificador cadastrado com sucesso!\n");
        }
        fprintf(fp, "%s, \n", c.numero_pedido);
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
