#include "pedido.h"
#include "../Modulo Cliente/cliente.h"
#include "../Modulo Produto/produtos.h"
#include <ncurses.h>

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
        printw("Erro ao abrir o arquivo");
    }

    printw("Digite o Indentificador do Pedido que deseja cadastrar:\n");
    flushinp();
    getstr(c.numero_pedido);
    c.numero_pedido[strcspn(c.numero_pedido, "\n")] = '\0';

    // VARIÁVEIS USADAS NA VERIFICAÇÃO (VOCÊ NÃO TINHA DECLARADO)
    char texto[1000];
    char codigo_existente[30];
        
    while(fgets(texto, 1000, fp_pedido)){

        sscanf(texto, "%[^,]", codigo_existente);

        if(strcmp(c.numero_pedido, codigo_existente) == 0){
            codigo_cadas = 1;
            break;
        }
    }

    if(codigo_cadas) {
        printw("Este Identificador ja existe. Digite outro.\n");
    }
    else {
        printw("Identificador cadastrado com sucesso!\n");
    }

    printw("Digite o código do cliente:");
    flushinp();
    getstr(cliente_t);
    cliente_t[strcspn(cliente_t, "\n")] = '\0';
        
    c_encontrado = buscarCliente(cliente_t);
    if(strcmp(c_encontrado.codigo, "") == 0){
        printw("Código não encontrado");
        fclose(fp_pedido);
        return;
    }

    strcpy(c.idcliente, cliente_t);
    strcpy(c.nome_cliente, c_encontrado.cadastro);
    printw("Cliente Encontrado: %s\n", c.nome_cliente);

    printw("Digite o Código do produto:");
    scanw("%d", &produto_t);

    p_encontrado= buscarProdutos(produto_t);

    if(p_encontrado.codigo == -1){ 
        printw("Código de produto não encontrado. Cadastro cancelado.\n");
        fclose(fp_pedido);
        return;
    }

    c.idproduto = produto_t;
    strcpy(c.nome_produto, p_encontrado.descricao);
    c.preco_produto = p_encontrado.preco;

    printw("Produto encontrado: %s R$ %.2f\n", c.nome_produto, c.preco_produto);

    printw("Digite a quantidade de produtos:");
    scanw("%d", &c.quantidade);

    c.preco_total = c.preco_produto * c.quantidade;

    printw("Custo total: R$ %.2f\n", c.preco_total);

    fprintf(fp_pedido, "%s, %s, %s, %d, %s, %.2f, %d, %.2f",
        c.numero_pedido, c.idcliente, c.nome_cliente, c.idproduto,
        c.nome_produto, c.preco_produto, c.quantidade, c.preco_total
    );
        
    printw("Pedido cadastrado!");
        
    fclose(fp_pedido);
}

void consultarPedido(){
    FILE *fp_pedido; 
    pedido c; 
    char numero[50];
    int encontrado = 0;

    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido== NULL){
        printw("Erro ao abrir o arquivo\n");
        return;
    }

    printw("Digite o numero do pedido que deseja consultar:");
    flushinp();
    getstr(numero);
    numero[strcspn(numero, "\n")] = '\0';

    char linha[256];

    fgets(linha, sizeof(linha), fp_pedido); 

    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(linha, " %[^;];", c.numero_pedido);

        if(strcmp(c.numero_pedido, numero) == 0){
            printw("\nPedido encontrado:\n");
            printw("Número: %s\n", c.numero_pedido);
            printw("Linha completa: %s\n", linha);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printw("Pedido não encontrado.\n");
    }

    fclose(fp_pedido);
}

 
void listarPedido(){
    FILE *fp_pedido; 
    pedido c; 
    
    fp_pedido = fopen("pedido.csv", "r");
    if(fp_pedido == NULL){
        printw("Erro ao abrir o arquivo\n");
        return;
    }
    
    char linha[256];
    fgets(linha, sizeof(linha), fp_pedido);
    printw("%s", linha);
    
    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(linha, " %[^;];", c.numero_pedido);
        printw("Número: %s\n", c.numero_pedido);
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
        printw("Erro ao abrir o arquivo\n");
        return;
    }
    
    temp_fp = fopen("temp_pedido.csv", "w");
    if(temp_fp == NULL){
        printw("Erro ao criar o arquivo temporário\n");
        fclose(fp_pedido);
        return;
    }
    
    printw("Digite o numero do pedido que deseja remover:");
    flushinp();
    getstr(numero);
    numero[strcspn(numero, "\n")] = '\0';
    
    char linha[256];
    fgets(linha, sizeof(linha), fp_pedido);
    fprintf(temp_fp, "%s", linha);
    
    while(fgets(linha, sizeof(linha), fp_pedido)){
        sscanf(linha, " %[^;];", c.numero_pedido);

        if(strcmp(c.numero_pedido, numero) == 0){
            encontrado = 1;
            printw("Pedido removido com sucesso.\n");
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
}


void menuPedido() {
    int opcao = 0;
    int highlight = 0;

    char *opcoes[] = {
        "Cadastrar Pedido",
        "Consultar Pedido",
        "Listar Pedidos",
        "Remover Pedido",
        "Sair"
    };

    int n_opcoes = 5;

    initscr();            // inicia ncurses
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); // permite setas

    while(1) {
        clear();
        box(stdscr, 0, 0);
        mvprintw(1, 2, "===== MENU DE PEDIDOS =====");

        for (int i = 0; i < n_opcoes; i++) {
            if (i == highlight)
                attron(A_REVERSE);
            
            mvprintw(3 + i, 4, "%s", opcoes[i]);

            if (i == highlight)
                attroff(A_REVERSE);
        }

        int ch = getch();

        switch(ch) {

            case KEY_UP:
                highlight--;
                if (highlight < 0) highlight = n_opcoes - 1;
                break;

            case KEY_DOWN:
                highlight++;
                if (highlight >= n_opcoes) highlight = 0;
                break;

            case 10: // ENTER
                opcao = highlight + 1;
                clear();

                if(opcao == 1) cadastrarPedido();
                else if(opcao == 2) consultarPedido();
                else if(opcao == 3) listarPedido();
                else if(opcao == 4) removerPedido();
                else if(opcao == 5) {
                    endwin();
                    return;
                }

                mvprintw(20, 2, "Pressione qualquer tecla para voltar...");
                getch();
                break;
        }
    }

    endwin();
}
int main(){
    menuPedido();

    return 0;

}
