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

int analisarPedido(char *codigo){
    FILE *fp = fopen("pedido.csv", "r");
    char linha[300], numero_lido[50];

    if(fp == NULL)
        return 0;

    fgets(linha, sizeof(linha), fp);

    while(fgets(linha, sizeof(linha), fp)){
        sscanf(linha, "%[^;];", numero_lido);

        if(strcmp(codigo, numero_lido) == 0){
            fclose(fp);
            return 1; // encontrado
        }
    }

    fclose(fp);
    return 0; 
}

void cadastrarPedido(){
    bkgd(COLOR_PAIR(2)); 
    FILE *fp_pedido;
    pedido c;
    int codigo_cadas = 0;
    int produto_t;
    char cliente_t[30];

    pessoa c_encontrado;
    Produto p_encontrado;

    char texto[1000], codigo_existente[100];

    fp_pedido = fopen("pedido.csv", "a+");

    if(fp_pedido == NULL){
        attron(COLOR_PAIR(1));
        printw("Erro ao abrir o arquivo\n");
        attroff(COLOR_PAIR(1));
        getch();
        return;
    }

    attron(COLOR_PAIR(1));
    printw("Digite o Identificador do Pedido:\n");
    attroff(COLOR_PAIR(1));
    ncurses_getstr(c.numero_pedido, 50);

    if(analisarPedido(c.numero_pedido)){
        attron(COLOR_PAIR(3));
        printw("Este Identificador já existe!\n");
        attroff(COLOR_PAIR(3));
        getch();
        fclose(fp_pedido);
        return;
    } else {
        attron(COLOR_PAIR(3));
        printw("Identificador cadastrado!\n");
        attroff(COLOR_PAIR(3));
    }


    attron(COLOR_PAIR(1));
    printw("Digite o código do cliente:\n");
    attroff(COLOR_PAIR(1));
    ncurses_getstr(cliente_t, 30);

    c_encontrado = buscarCliente(cliente_t);
    if(strcmp(c_encontrado.codigo, "") == 0){
        attron(COLOR_PAIR(3));
        printw("Codigo de cliente não encontrado!\n");
        attroff(COLOR_PAIR(3));
        getch();
        fclose(fp_pedido);
        return;
    }

    strcpy(c.idcliente, cliente_t);
    strcpy(c.nome_cliente, c_encontrado.cadastro);

    attron(COLOR_PAIR(3));
    printw("Cliente encontrado: %s\n", c.nome_cliente);
    attroff(COLOR_PAIR(3));

    printw("Digite o codigo do produto:\n");
    produto_t = ncurses_getint();

    p_encontrado = buscarProdutos(produto_t);

    if(p_encontrado.codigo == -1){
        attron(COLOR_PAIR(3));
        printw("Produto não encontrado.\n");
        attroff(COLOR_PAIR(3));
        getch();
        fclose(fp_pedido);
        return;
    }

    c.idproduto = produto_t;
    strcpy(c.nome_produto, p_encontrado.descricao);
    c.preco_produto = p_encontrado.preco;

    attron(COLOR_PAIR(3));
    printw("Produto encontrado: %s R$ %.2f\n", c.nome_produto, c.preco_produto);
    attroff(COLOR_PAIR(3));

    printw("Digite a quantidade:\n");
    c.quantidade = ncurses_getint();

    c.preco_total = c.preco_produto * c.quantidade;

    attron(COLOR_PAIR(3));
    printw("Custo total: R$ %.2f\n", c.preco_total);
    attroff(COLOR_PAIR(3));

    fprintf(fp_pedido,
        "%s;%s;%s;%d;%s;%.2f;%d;%.2f\n",
        c.numero_pedido, c.idcliente, c.nome_cliente, c.idproduto,
        c.nome_produto, c.preco_produto, c.quantidade, c.preco_total
    );

    attron(COLOR_PAIR(3));
    printw("Pedido cadastrado!\n");
    attroff(COLOR_PAIR(3));

    getch();
    fclose(fp_pedido);
}

void consultarPedido(){
    bkgd(COLOR_PAIR(2)); 
    FILE *fp_pedido;
    pedido c;
    char numero[50];
    int encontrado = 0;

    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        attron(COLOR_PAIR(1));
        printw("Erro ao abrir o arquivo\n");
        attroff(COLOR_PAIR(1));
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
            attron(COLOR_PAIR(3));
            printw("\nPedido Encontrado!\n\n");
            attroff(COLOR_PAIR(3));

            printw("Numero: %s\n", c.numero_pedido);
            printw("ID cliente: %s\n", c.idcliente);
            printw("Cadastro do Cliente: %s\n", c.nome_cliente);
            printw("ID produto: %d\n", c.idproduto);
            printw("Nome do Produto: %s\n", c.nome_produto);
            printw("Preço: %.2f\n", c.preco_produto);
            printw("Quantidade: %d\n", c.quantidade);
            printw("Preço Total: %.2f\n\n", c.preco_total);

            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        attron(COLOR_PAIR(1));
        printw("Pedido não encontrado.\n");
        attroff(COLOR_PAIR(1));
    }

    getch();
    fclose(fp_pedido);
}

void listarPedido(){
    FILE *fp_pedido;
    pedido c;
    bkgd(COLOR_PAIR(2)); 

    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        attron(COLOR_PAIR(1));
        printw("Erro ao abrir o arquivo\n");
        attroff(COLOR_PAIR(1));
        getch();
        return;
    }

    char linha[256];

    fgets(linha, sizeof(linha), fp_pedido);

    attron(COLOR_PAIR(3));
    printw("\nLista de Pedidos:\n");
    attroff(COLOR_PAIR(3));

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
        printw("ID produto: %d\n", c.idproduto);
        printw("Nome do Produto: %s\n", c.nome_produto);
        printw("Preço: %.2f\n", c.preco_produto);
        printw("Quantidade: %d\n", c.quantidade);
        printw("Preço Total: %.2f\n", c.preco_total);
        printw("------------------------------------\n");
    }

    getch();
    fclose(fp_pedido);
}

void removerPedido(){
    FILE *fp_pedido, *temp_fp;
    pedido c;
    char numero[50];
    int encontrado = 0;
    bkgd(COLOR_PAIR(2)); 

    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        attron(COLOR_PAIR(1));
        printw("Erro ao abrir o arquivo\n");
        attroff(COLOR_PAIR(1));
        getch();
        return;
    }

    temp_fp = fopen("temp_pedido.csv", "w");
    if(temp_fp == NULL){
        attron(COLOR_PAIR(1));
        printw("Erro ao criar arquivo temporário\n");
        attroff(COLOR_PAIR(1));
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

            attron(COLOR_PAIR(3));
            printw("Pedido removido.\n");
            attroff(COLOR_PAIR(3));

            continue;
        }

        fprintf(temp_fp, "%s", linha);
    }

    if(!encontrado){
        attron(COLOR_PAIR(1));
        printw("Pedido não encontrado.\n");
        attroff(COLOR_PAIR(1));
    }

    fclose(fp_pedido);
    fclose(temp_fp);

    remove("pedido.csv");
    rename("temp_pedido.csv", "pedido.csv");

    getch();
}

void menuPedido(){
    int opcao = 1;
    int tecla;

    const char *opcoes[] = {
        "CADASTRAR PEDIDO",
        "CONSULTAR PEDIDO",
        "LISTAR PEDIDOS",
        "REMOVER PEDIDO",
        "SAIR"
    };

    int total = 5;

    while(1){
        clear();
        bkgd(COLOR_PAIR(4)); 

        printw("============= MENU =============\n\n");

        for(int i = 0; i < total; i++){
            if(i + 1 == opcao){
                attron(COLOR_PAIR(3)); 
                printw(">%s\n", opcoes[i]);
                attroff(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(1)); 
                printw("%s\n", opcoes[i]);
                attroff(COLOR_PAIR(1));
            }
        }

        printw("\nUse as SETAS para navegar e ENTER para selecionar.\n");

        tecla = getch();

        if(tecla == KEY_UP){
            opcao--;
            if(opcao < 1) opcao = total;
        }
        else if(tecla == KEY_DOWN){
            opcao++;
            if(opcao > total) opcao = 1;
        }
        else if(tecla == '\n'){
            switch(opcao){
                case 1: cadastrarPedido(); 
                break;
                
                case 2: consultarPedido(); 
                break;
                
                case 3: listarPedido(); 
                break;
                
                case 4: removerPedido(); 
                break;
                
                case 5: return;
            }
        }
    }
}

int mainPedido(){
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    start_color();
    use_default_colors();

    init_pair(1, COLOR_RED, -1);             
    init_pair(2, COLOR_BLACK, -1);           
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(4, COLOR_RED, -1);

    menuPedido();

    endwin();
    return 0;
}
