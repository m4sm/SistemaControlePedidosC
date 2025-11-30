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
    getnstr(p->descricao, 99); // Aumentei um pouco o buffer de leitura segura

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
        return;
    }
    
    // Formato CSV simples
    fprintf(arq, "%d,%s,%d,%.2f\n", p.codigo, p.descricao, p.quantidade, p.preco);
    fclose(arq);

    printw("\nProduto cadastrado com sucesso!\n");
}

void consultarProduto(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printw("Erro ao abrir o arquivo.\n");
        return;
    }

    int codigoBusca;
    char entrada[50];
    
    printw("Digite o codigo do produto a consultar: ");
    refresh();
    getnstr(entrada, 49); // Usar getnstr é mais seguro que scanw em ncurses
    codigoBusca = atoi(entrada);
    
    Produto p;
    int encontrado = 0;

    // Lê linha por linha do CSV
    while (fscanf(fp, "%d,%99[^,],%d,%f\n", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
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

    while (fscanf(fp, "%d,%99[^,],%d,%f\n", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
        if (p.codigo == codigoRemover) {
            encontrado = 1;
            continue; 
        }
        fprintf(temp, "%d,%s,%d,%.2f\n", p.codigo, p.descricao, p.quantidade, p.preco);
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
        return;
    }

    Produto p;
    int count = 0;

    clear(); // Limpa a tela para a listagem
    printw("=== Lista de Produtos ===\n");

    while (fscanf(fp, "%d,%99[^,],%d,%f\n", &p.codigo, p.descricao, &p.quantidade, &p.preco) == 4) {
        printw("\nProduto %d:\n", ++count);
        printw("  Codigo     : %d\n", p.codigo);
        printw("  Descricao  : %s\n", p.descricao);
        printw("  Quantidade : %d\n", p.quantidade);
        printw("  Preco      : R$ %.2f\n", p.preco);
        
    }

    if (count == 0) {
        printw("Nenhum produto encontrado.\n");
    }

    fclose(fp);
    printw("\nPressione qualquer tecla para voltar...");
    getch();
}

Produto buscarProdutos(){
    int codigo_p;
    FILE *fp_produto;
    char linha[256];    
    
    fp_produto = fopen("listadeprodutos.csv", "r");

    if(fp_produto == NULL){
        printw("Erro ao abrir o arquivo");
        getch();
        Produto vazio = {0};
        return vazio;
    }

    Produto p_busca;

    while (fgets(linha, sizeof(linha), fp_produto)) {
        
        linha[strcspn(linha, "\n")] = 0; 

        
        int campos_lidos = sscanf(linha, "%d, %[^,], %d, %f", 
                                  &p_busca.codigo, 
                                  p_busca.descricao, 
                                  &p_busca.quantidade, 
                                  &p_busca.preco); 
        if (campos_lidos == 4) {
            if (p_busca.codigo == codigo_p) {
                fclose(fp_produto);
                return p_busca; 
            }
        }
    }
}