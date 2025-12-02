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

    while (1) {
        clear();
        printw("======== SISTEMA PRINCIPAL ========\n\n");

        for (int i = 0; i < num_opcoes; i++) {
            if (i == selecionado)
                printw(" -> %s\n", opcoes[i]);   // destacado
            else
                printw("    %s\n", opcoes[i]);
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
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    menuPrincipal();

    endwin();
    return 0;
}
