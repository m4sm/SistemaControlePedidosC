#include <ncurses.h>
#include "pedido.h"
#include "../Cliente/cliente.h"
#include "../Produto/produtos.h"


void ncurses_getstr(char *buffer, int size) {
    echo();
    wgetnstr(stdscr, buffer, size);
    noecho();
}

int ncurses_getint() {
    char temp[20];
    ncurses_getstr(temp, 20);
    return atoi(temp);
}

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
        printw("Erro ao abrir o arquivo\n");
        getch();
        return;
    }

    printw("Digite o Identificador do Pedido:\n");
    ncurses_getstr(c.numero_pedido, 50);

    rewind(fp_pedido);

    while(fgets(texto, 1000, fp_pedido)){
        sscanf(texto, "%[^;];", codigo_existente);

        if(strcmp(c.numero_pedido, codigo_existente) == 0){
            codigo_cadas = 1;
            break;
        }
    }

    if(codigo_cadas) {
        printw("Este Identificador já existe!\n");
        getch();
        fclose(fp_pedido);
        return;
    } else {
        printw("Identificador cadastrado!\n");
    }

    printw("Digite o código do cliente:\n");
    ncurses_getstr(cliente_t, 30);

    c_encontrado = buscarCliente(cliente_t);
    if(strcmp(c_encontrado.codigo, "") == 0){
        printw("Codigo de cliente não encontrado!\n");
        getch();
        fclose(fp_pedido);
        return;
    }

    strcpy(c.idcliente, cliente_t);
    strcpy(c.nome_cliente, c_encontrado.cadastro);
    printw("Cliente encontrado: %s\n", c.nome_cliente);

    printw("Digite o codigo do produto:\n");
    produto_t = ncurses_getint();

    p_encontrado = buscarProdutos(produto_t);

    if(p_encontrado.codigo == -1){
        printw("Produto não encontrado.\n");
        getch();
        fclose(fp_pedido);
        return;
    }

    c.idproduto = produto_t;
    strcpy(c.nome_produto, p_encontrado.descricao);
    c.preco_produto = p_encontrado.preco;

    printw("Produto encontrado: %s R$ %.2f\n", c.nome_produto, c.preco_produto);

    printw("Digite a quantidade:\n");
    c.quantidade = ncurses_getint();

    c.preco_total = c.preco_produto * c.quantidade;

    printw("Custo total: R$ %.2f\n", c.preco_total);

    fprintf(fp_pedido,
        "%s;%s;%s;%d;%s;%.2f;%d;%.2f\n",
        c.numero_pedido, c.idcliente, c.nome_cliente, c.idproduto,
        c.nome_produto, c.preco_produto, c.quantidade, c.preco_total
    );
    
    printw("Pedido cadastrado!\n");
    getch();
    fclose(fp_pedido);
}


void consultarPedido(){
    FILE *fp_pedido; 
    pedido c; 
    char numero[50];
    int encontrado = 0;

    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        printw("Erro ao abrir o arquivo\n");
        getch();
        return;
    }

    printw("Digite o numero do pedido:\n");
    ncurses_getstr(numero, 50);

    char linha[256];

    fgets(linha, sizeof(linha), fp_pedido);

    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(
            linha,
            " %[^;];%[^;];%[^;];%d;%[^;];%f;%d;%f",
            c.numero_pedido,
            c.idcliente,
            c.nome_cliente,
            &c.idproduto,
            c.nome_produto,
            &c.preco_produto,
            &c.quantidade,
            &c.preco_total
        );

    if(strcmp(c.numero_pedido, numero) == 0){
            printw("\nLista de Pedidos!\n");
            printw("Numero: %s\n", c.numero_pedido);
            printw("ID cliente: %s\n", c.idcliente);
            printw("Cadastro do Cliente: %s\n", c.nome_cliente);
            printw("ID  produto: %d\n", c.idproduto);
            printw("Nome do Produto: %s\n", c.nome_produto);
            printw("Preço: %.2f\n", c.preco_produto);
            printw("Quantidade: %d\n", c.quantidade);
            printw("Preço Total: %.2f\n\n", c.preco_total);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printw("Pedido não encontrado.\n");
    }

    getch();
    fclose(fp_pedido);
}
 

void listarPedido(){
    FILE *fp_pedido; 
    pedido c; 
    
    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        printw("Erro ao abrir o arquivo\n");
        getch();
        return;
    }
    
    char linha[256];

    fgets(linha, sizeof(linha), fp_pedido);
    printw("\nLista de Pedidos!\n");
    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(
            linha,
            " %[^;];%[^;];%[^;];%d;%[^;];%f;%d;%f",
            c.numero_pedido,
            c.idcliente,
            c.nome_cliente,
            &c.idproduto,
            c.nome_produto,
            &c.preco_produto,
            &c.quantidade,
            &c.preco_total
        );
            printw("\nNumero: %s\n", c.numero_pedido);
            printw("ID cliente: %s\n", c.idcliente);
            printw("Cadastro do Cliente: %s\n", c.nome_cliente);
            printw("ID  produto: %d\n", c.idproduto);
            printw("Nome do Produto: %s\n", c.nome_produto);
            printw("Preço: %.2f\n", c.preco_produto);
            printw("Quantidade: %d\n", c.quantidade);
            printw("Preço Total: %.2f\n", c.preco_total);
            printw("------------------------------------\n\n");
    }

    getch();
    fclose(fp_pedido);
}

void removerPedido(){
    FILE *fp_pedido, *temp_fp; 
    pedido c; 
    char numero[50];
    int encontrado = 0;
    
    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        printw("Erro ao abrir o arquivo\n");
        getch();
        return;
    }
    
    temp_fp = fopen("temp_pedido.csv", "w");
    if(temp_fp == NULL){
        printw("Erro ao criar arquivo temporário\n");
        fclose(fp_pedido);
        getch();
        return;
    }
    
    printw("Digite o número do pedido para remover:\n");
    ncurses_getstr(numero, 50);
    
    char linha[256];
    fgets(linha, sizeof(linha), fp_pedido);
    fprintf(temp_fp, "%s", linha);
    
    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(linha, " %[^;];", c.numero_pedido);

        if(strcmp(c.numero_pedido, numero) == 0){
            encontrado = 1;
            printw("Pedido removido.\n");
            continue;
        }

        fprintf(temp_fp, "%s", linha);
    }

    if(!encontrado){
        printw("Pedido não encontrado.\n");
    }
    
    fclose(fp_pedido);
    fclose(temp_fp);
    
    remove("pedido.csv");
    rename("temp_pedido.csv", "pedido.csv");

    getch();
}




void menuPedido(){
    int opcao;

    do{
        clear();
        printw("============= MENU =============\n");
        printw("1 - CADASTRAR PEDIDO\n");
        printw("2 - CONSULTAR PEDIDO\n");
        printw("3 - LISTAR PEDIDOS\n");
        printw("4 - REMOVER PEDIDO\n");
        printw("5 - SAIR\n");
        printw("Escolha uma opção:\n");

        opcao = ncurses_getint();

        switch(opcao){
            case 1: cadastrarPedido(); break;
            case 2: consultarPedido(); break;
            case 3: listarPedido(); break;
            case 4: removerPedido(); break;
            case 5: break;
            default:
                printw("Opção inválida!\n");
                getch();
        }
    } while(opcao != 5);
}



int mainPedido(){
    initscr();
    noecho();
    cbreak();

    menuPedido();

    endwin();
    return 0;
}
