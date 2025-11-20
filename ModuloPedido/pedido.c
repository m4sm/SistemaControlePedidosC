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
    
    
    fp = fopen("pedido.csv", "a+");
     
     if(fp == NULL){
         printf("Erro ao abrir o arquivo");
        
     }
     
    rewind(fp);
    char primeira_linha[100];
    if (fgets(primeira_linha, 100, fp) == NULL) {
        fprintf(fp, "ID, CLIENTE, PRODUTO\n");
    };
        
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
        return;
    } else {
        printf("Identificador cadastrado com sucesso!\n");
    }
    
   
    printf("\nNome do cliente:\n");
    fgets(c.nome_cliente, 100, stdin);
    c.nome_cliente[strcspn(c.nome_cliente, "\n")] = '\0';
    
    printf("\nProduto solicitado:\n");
    fgets(c.produto_pedido, 100, stdin);
    c.produto_pedido[strcspn(c.produto_pedido, "\n")] = '\0';
    
    fprintf(fp, "%s, %s,  %s\n", c.numero_pedido, c.nome_cliente, c.produto_pedido);

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
        sscanf(linha, " %49[^,],%99[^,],%99[^\n]", c.numero_pedido, c.nome_cliente, c.produto_pedido);
        if(strcmp(c.numero_pedido, numero) == 0){
            printf("\nPedido encontrado:\n");
            printf("Número: %s\nCliente: %s\nProduto: %s\n", c.numero_pedido, c.nome_cliente, c.produto_pedido);
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
        sscanf(linha, " %49[^,],%99[^,],%99[^\n]", c.numero_pedido, c.nome_cliente, c.produto_pedido);
        printf("Número: %s | Cliente: %s | Produto: %s\n", c.numero_pedido, c.nome_cliente, c.produto_pedido);
    }
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
            //removerPedido();
            break;

           /*case 5:
                
           break;*/
           
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

