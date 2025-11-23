#include "pedido.h"
#include "../Modulo Cliente/cliente.h"
#include "../Modulo Produto/produtos.h"

void cadastrarPedido(){
    FILE *fp_pedido;
    pedido c;
    int codigo_cadas = 0;
    int produto_t;
    char cliente_t[30];

    pessoa c_encontrado;
    Produto p_encontrado;   
    
    fp_pedido = fopen("pedido.csv", "a+");
     
     if(fp_pedido == NULL){
         printf("Erro ao abrir o arquivo");
        
    }

    printf("Digite o Indentificador do Pedido que deseja cadastrar:\n");
    fgets(c.numero_pedido, 50, stdin);
    c.numero_pedido[strcspn(c.numero_pedido, "\n")] = '\0';
        
    while(fgets(texto, 1000, fp_pedido)){

        
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

        printf("Digite o código do cliente:");
        fgets(cliente_t, 30, stdin);
        cliente_t[strcspn(cliente_t, "\n")] = '\0';
        

        c_encontrado = buscarCliente(cliente_t);
         if(strcmp(c_encontrado.codigo, "") == 0){
            printf("Código não encontrado");
            fclose(fp_pedido);
            return;
         }
         strcpy(c.idcliente, cliente_t);
         strcpy(c.nome_cliente, c_encontrado.cadastro);
         printf("Cliente Encontrado: %s\n", c.nome_cliente);

         printf("Digite o Código do produto:");
         scanf("%d", &produto_t);

        p_encontrado= buscarProdutos(produto_t);

        if(p_encontrado.codigo == -1){ 
        printf("Código de produto não encontrado. Cadastro cancelado.\n");
        fclose(fp_pedido);
        return;
        }

        c.idproduto = produto_t;
        strcpy(c.nome_produto, p_encontrado.descricao);
        c.preco_produto = p_encontrado.preco;

        printf("Produto encontrado: %s R$ %.2f\n", c.nome_produto, c.preco_produto);

        printf("Digite a quantidade de produtos:");
        scanf("%d", &c.quantidade);

        c.preco_total = c.preco_produto * c.quantidade;

        printf("Custo total: R$ %.2f\n", c.preco_total);

        fprintf(fp_pedido, "%s, %s, %s, %d, %s, %.2f, %d, %.2f",
        c.numero_pedido, c.idcliente, c.nome_cliente, c.idproduto,
        c.nome_produto, c.preco_produto, c.quantidade, c.preco_total
        );
        
        printf("Pedido cadastrado!");
        
        fclose(fp_pedido);
}


void consultarPedido(){
    FILE *fp_pedido; 
    pedido c; 
    char numero[50];
    int encontrado = 0;

    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido== NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    printf("Digite o numero do pedido que deseja consultar:");
    getchar(); 
    fgets(numero, 50, stdin);
    numero[strcspn(numero, "\n")] = '\0';

    char linha[256];

    fgets(linha, sizeof(linha), fp_pedido); 

    while(fgets(linha, sizeof(linha), fp_pedido)){
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

    fclose(fp_pedido);
}
 
void listarPedido(){
    FILE *fp_pedido; 
    pedido c; 
    
    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    char linha[256];
    fgets(linha, sizeof(linha), fp_pedido);
    printf("%s", linha);
    
    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(linha, " %[^;];", c.numero_pedido);
        printf("Número: %s\n", c.numero_pedido);
    }

    fclose(fp_pedido);
}

void removerPedido(){
    FILE *fp_pedido, *temp_fp; 
    pedido c; 
    char numero[50];
    int encontrado = 0;
    
    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    temp_fp = fopen("temp_pedido.csv", "w");
    if(temp_fp == NULL){
        printf("Erro ao criar o arquivo temporário\n");
        fclose(fp_pedido);
        return;
    }
    
    printf("Digite o numero do pedido que deseja remover:");
    getchar();
    fgets(numero, 50, stdin);
    numero[strcspn(numero, "\n")] = '\0';
    
    char linha[256];
    fgets(linha, sizeof(linha), fp_pedido);
    fprintf(temp_fp, "%s", linha);
    
    while(fgets(linha, sizeof(linha), fp_pedido)){
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
    
    fclose(fp_pedido);
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

int mainPedido(){
   menuPedido();
   return 0;
}
