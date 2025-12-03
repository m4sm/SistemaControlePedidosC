#include <ncurses.h>
#include "Cliente/cliente.h"
#include "Produto/produtos.h"
#include "Pedido/pedido.h"

void menuPrincipal() {
    const char *opcoes[] = {
        "Modulo de Clientes",
        "Modulo de Produtos",
        "Modulo de Pedidos",
        "Sair"
    };

    int num_opcoes = 4;
    int selecionado = 0;
    int tecla;
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(6, COLOR_BLUE, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(3, COLOR_GREEN, -1);


    while (1) {
        clear();
        attron(COLOR_PAIR(3));
        printw("======== SISTEMA DE CONTROLE DE PEDIDOS ========\n\n");
        attroff(COLOR_PAIR(3));

        for (int i = 0; i < num_opcoes; i++) {
            if (i == selecionado){
                attron(COLOR_PAIR(3));
                printw(" -> %s\n", opcoes[i]); 
                attroff(COLOR_PAIR(1));
            } 
            else{
                attron(COLOR_PAIR(2));
                printw("    %s\n", opcoes[i]);
                attroff(COLOR_PAIR(2));
            }
        }

        tecla = getch();

        switch (tecla) {
            case KEY_UP:
                selecionado--;
                if (selecionado < 0)
                    selecionado = num_opcoes - 1;
                break;

            case KEY_DOWN:
                selecionado++;
                if (selecionado >= num_opcoes)
                    selecionado = 0;
                break;

            case '\n':  // ENTER
                clear();
                switch (selecionado) {
                    case 0:
                        menuCliente();   // chama clientes
                        break;
                    case 1:
                        menuProdutos();  // chama produtos
                        break;
                    case 2:
                        menuPedido();    // chama pedidos
                        break;
                    case 3:
                        endwin();
                        exit(0);
                }
                break;
        }
    }
}



int main() {
    initscr();
    start_color();
    use_default_colors();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    menuPrincipal();

    endwin();
    return 0;
}
