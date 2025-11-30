#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "produtos.h" /

int menuProdutos() { 
    // Inicia o ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int opcao;

    do {
        clear();
        printw("=== Sistema de Produtos ===\n");
        printw("1. Cadastrar Produto\n");
        printw("2. Consultar Produto\n");
        printw("3. Remover Produto\n");
        printw("4. Listar Produtos\n");
        printw("0. Sair\n");
        printw("Escolha uma opcao: ");
        refresh();
        
        scanw("%d", &opcao);
        
        // switch-case
        switch (opcao) {
            case 1: 
                do {
                    clear();
                    cadastrarProduto("listadeprodutos.csv");
                } while (desejaContinuar());
                break;
                
            case 2: 
                consultarProduto("listadeprodutos.csv"); 
                break;
            case 3: 
                removerProduto("listadeprodutos.csv"); 
                break;
            case 4: 
                listarProdutos("listadeprodutos.csv"); 
                break;
            case 0: 
                printw("Saindo...\n"); 
                break;
            default: 
                printw("Opcao invalida!\n");
                getch();
        }
    } while (opcao != 0);

    endwin(); // Encerra ncurse
    return 0;
}
