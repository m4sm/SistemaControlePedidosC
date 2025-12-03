#include <ncurses.h>
#include "produtos.h"

// Função "Deseja Continuar?"
int desejaContinuar() {
    char resposta;
    while (1) {
        printw("\nDeseja Continuar? (S/N): ");
        refresh();
        resposta = getch();
        resposta = toupper(resposta);

        if (resposta == 'S') return 1;
        if (resposta == 'N') return 0;

        printw("\nOpcao invalida! Digite S ou N.\n");
    }
}

// Lê os dados de um produto via ncurses
void lerProduto(Produto *p) {
    char entrada[100];

    printw("Digite o codigo: ");
    refresh();
    getnstr(entrada, 99);
    p->codigo = atoi(entrada);

    printw("Digite a descricao: ");
    refresh();
    getnstr(p->descricao, 99); 

    printw("Digite a quantidade: ");
    refresh();
    getnstr(entrada, 99);
    p->quantidade = atoi(entrada);

    printw("Digite o preco: ");
    refresh();
    getnstr(entrada, 99);
    p->preco = atof(entrada);

    printw("\n");
}

void cadastrarProduto(const char *nomeArquivo){
    Produto p;
    lerProduto(&p);

    FILE *arq = fopen(nomeArquivo, "a");
    if (arq == NULL) {
        printw("Erro ao abrir o arquivo %s!\n", nomeArquivo);
        getch();
        return;
    }
    
    
    fprintf(arq, "%d;%s;%d;%.2f\n", p.codigo, p.descricao, p.quantidade, p.preco);
    fclose(arq);

    printw("\nProduto cadastrado com sucesso!\n");
}

void consultarProduto(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printw("Erro ao abrir o arquivo.\n");
        getch();
        return;
    }

    int codigoBusca;
    char entrada[50];
    
    printw("Digite o codigo do produto a consultar: ");
    refresh();
    getnstr(entrada, 49);
    codigoBusca = atoi(entrada);
    
    Produto p;
    int encontrado = 0;
    char linha[256];

    //Leitura linha a linha com fgets e sscanf com (;)
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = 0; // Remove quebra de linha

        if (sscanf(linha, "%d;%[^;];%d;%f", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
            if (p.codigo == codigoBusca) {
                printw("\n=== Produto Encontrado ===\n");
                printw("Codigo: %d\n", p.codigo);
                printw("Descricao: %s\n", p.descricao);
                printw("Quantidade: %d\n", p.quantidade);
                printw("Preco: %.2f\n", p.preco);
                encontrado = 1;
                break;
            }
        }
    }

    if (!encontrado) {
        printw("\nProduto com codigo %d nao encontrado.\n", codigoBusca);
    }
    fclose(fp);
    printw("\nPressione qualquer tecla para voltar...");
    getch();
}

void removerProduto(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printw("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printw("Erro ao criar arquivo temporario.\n");
        fclose(fp);
        return;
    }

    int codigoRemover;
    char entrada[50];
    printw("Digite o codigo do produto a remover: ");
    refresh();
    getnstr(entrada, 49);
    codigoRemover = atoi(entrada);
    
    Produto p;
    int encontrado = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = 0;

        // Lê os dados para verificar o código
        if (sscanf(linha, "%d;%[^;];%d;%f", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
            if (p.codigo == codigoRemover) {
                encontrado = 1;
                continue; 
            }
            // escreve no temporário 
            fprintf(temp, "%d;%s;%d;%.2f\n", p.codigo, p.descricao, p.quantidade, p.preco);
        }
    }

    fclose(fp);
    fclose(temp);

    if (encontrado) {
        remove(nomeArquivo);
        rename("temp.csv", nomeArquivo);
        printw("Produto removido com sucesso!\n");
    } else {
        remove("temp.csv");
        printw("Produto com codigo %d nao encontrado.\n", codigoRemover);
    }
    printw("\nPressione qualquer tecla para voltar...");
    getch();
}

void listarProdutos(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printw("Nenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        getch();
        return;
    }

    Produto p;
    int count = 0;
    char linha[256];

    clear(); 
    printw("=== Lista de Produtos ===\n");

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = 0;
        
        if (sscanf(linha, "%d;%[^;];%d;%f", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
            printw("\nProduto %d:\n", ++count);
            printw("  Codigo     : %d\n", p.codigo);
            printw("  Descricao  : %s\n", p.descricao);
            printw("  Quantidade : %d\n", p.quantidade);
            printw("  Preco      : R$ %.2f\n", p.preco);
        }
    }

    if (count == 0) {
        printw("Nenhum produto encontrado.\n");
    }

    fclose(fp);
    printw("\nPressione qualquer tecla para voltar...");
    getch();
}

// função de busca do pedido.c
Produto buscarProdutos(int codigo_alvo){
    FILE *fp_produto;
    char linha[256];    
    
    // Inicializa produto "Vazio/Erro"
    Produto p_busca;
    p_busca.codigo = -1; 
    
    // Certifique-se que o nome do arquivo aqui é o mesmo usado nas outras funções
    // Nas outras funções você passa "produtos.csv" por parâmetro
    fp_produto = fopen("produtos.csv", "r");

    if(fp_produto == NULL){
        
        return p_busca;
    }

    while (fgets(linha, sizeof(linha), fp_produto)) {
        linha[strcspn(linha, "\n")] = 0; 

        // Lê usando ponto e vírgula
        int campos_lidos = sscanf(linha, "%d;%[^;];%d;%f", 
                                  &p_busca.codigo, 
                                  p_busca.descricao, 
                                  &p_busca.quantidade, 
                                  &p_busca.preco); 
        
        if (campos_lidos == 4) {
            if (p_busca.codigo == codigo_alvo) {
                fclose(fp_produto);
                return p_busca; // Retorna o produto encontrado
            }
        }
    }
    
    fclose(fp_produto);
    
    // Se saiu do loop, não encontrou. Retorna com codigo -1.
    p_busca.codigo = -1;
    return p_busca;
}



// MENU CLIENTE (ncurses)
//-------------------------------------
void menuProdutos()
{
    char *opcoes[] = {
        "Cadastrar Produto",
        "Consultar Produto",
        "Remover Produto",
        "Listar Produto",
        "Sair"};

    int n = 5;
    int escolha = 0;

    while (1)
    {
        clear();

        start_color();
        use_default_colors();
        init_pair(1, COLOR_CYAN, -1);
        init_pair(2, COLOR_YELLOW, -1);
        init_pair(3, COLOR_GREEN, -1);
        init_pair(4, COLOR_RED, -1);
        init_pair(5, COLOR_MAGENTA, -1);
        init_pair(6, COLOR_BLUE, -1);  
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
        init_pair(10, COLOR_WHITE, COLOR_BLACK);
        
        bkgd(COLOR_PAIR(10));
        
        init_color(COLOR_BLUE, 0, 0, 300);   // 0–1000 (RGB) → azul bem escuro
        init_pair(10, COLOR_WHITE, COLOR_BLUE);
        //bkgd(COLOR_PAIR(10));


        attron(COLOR_PAIR(1));
        mvprintw(1, 2, "=========== MENU PRODUTOS ===========");
        mvprintw(3, 2, "Use as setas e ENTER");
        attroff(COLOR_PAIR(1));

        for (int i = 0; i < n; i++)
        {
            if (i == escolha)
                attron(A_REVERSE | COLOR_PAIR(7));
            mvprintw(5 + i, 4, "%s", opcoes[i]);
            attroff(A_REVERSE | COLOR_PAIR(7));
        }

        int tecla = getch();

        if (tecla == KEY_UP)
            escolha = (escolha - 1 + n) % n;
        else if (tecla == KEY_DOWN)
            escolha = (escolha + 1) % n;
        else if (tecla == 10)
        {
            clear();
            switch (escolha)
            {
            case 0:
                cadastrarProduto("produtos.csv");
                break;
            case 1:
                consultarProduto("produtos.csv");
                break;
            case 2:
                removerProduto("produtos.csv");
                break;
            case 3:
                listarProdutos("produtos.csv");
                break;
            case 4:
                return;
            }
        }
    }
}
