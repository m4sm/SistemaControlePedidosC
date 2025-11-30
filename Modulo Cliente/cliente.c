#include <ncurses.h>
#include "cliente.h"

FILE *fp;
char texto[1000];
pessoa p; 
FILE *fp_cliente;
char codigo_existente[1000];
int existe_codigo;

//-------------------------------------
// Função auxiliar para entrada ncurses
//-------------------------------------
void nc_input(int y, int x, const char *msg, char *buf, int size)
{
    attron(COLOR_PAIR(2));
    mvprintw(y, x, "%s", msg);
    attroff(COLOR_PAIR(2));

    echo();
    mvgetnstr(y + 1, x, buf, size);
    noecho();
}

int valida_cpf(char cpf[12]){
    int soma = 0;
    int dv1_informado = cpf[9] - '0';
    int dv2_informado = cpf[10] - '0';
    int resto = 0;
    int dv1_calculado, dv2_calculado;

    if(strlen(cpf)!= 11){
        return 0;
    }

    //VALIDACAO DO PRIMEIRO DIGITO
    // Soma os 9 primeiros dígitos (i=0 a i=8) com multiplicadores 10 a 2
    for(int i = 0; i < 9; i++){
        soma += (cpf[i] - '0') * (10-i); //(10-i) percorre de 10 ate 2
    }

    resto = soma % 11;


    if (resto < 2){ //Se o resto for 0 ou 1
        dv1_calculado = 0;
    } else { // Se o resto for 2 a 10
        dv1_calculado = 11 - resto; 
    }

    if(dv1_calculado != dv1_informado){
        return 0; //Se o dv1 nao bate, o cpf é invalido
    }

    soma = 0;
    resto = 0;

    //VALIDACAO DO SEGUNDO DIGITO
    for(int i = 0; i < 10; i++){
        soma += (cpf[i]- '0') * (11-i); //MULTIPLICADOR (11 - i) percorre de 11 até 2
    }

    resto = soma % 11;

    if (resto < 2){ //se o resto for 0 ou 1
        dv2_calculado = 0;
    } else { // se o resto for 2 a 10
        dv2_calculado = 11 - resto; 
    }

    if (dv2_calculado != dv2_informado){
        return 0; //se o dv2 nao bate, cpf é invalido
    }

    return 1; //CPF Valido
    
}

int valida_cnpj(char cnpj[15]){
    int soma = 0;
    int dv1_informado = cnpj[12] - '0';
    int dv2_informado = cnpj[13] - '0';
    int resto = 0;
    int dv1_calculado, dv2_calculado;

    //VALIDACAO DO PRIMEIRO DIGITO
    // Soma os 12 primeiros dígitos  com multiplicadores 
    //5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2. 

    if(strlen(cnpj)!= 14){
        return 0;
    }

    soma += (cnpj[0] - '0') * 5 + (cnpj[1] - '0') * 4 + (cnpj[2] - '0') * 3 + (cnpj[3] - '0') * 2;

    for(int i = 4; i < 12; i++){
        soma += (cnpj[i] - '0') * (13-i); //  (13-i) == 9 A 2
    }
    
    resto = soma % 11;


    if (resto < 2){ //Se o resto for 0 ou 1
        dv1_calculado = 0;
    } else { // Se o resto for 2 a 10
        dv1_calculado = 11 - resto; 
    }

    if(dv1_calculado != dv1_informado){
        return 0; //Se o dv1 nao bate, o cnpj é invalido
    }

    soma = 0;
    resto = 0;

    //VALIDACAO DO SEGUNDO DIGITO

    soma += (cnpj[0] - '0') * 6 + (cnpj[1] - '0') * 5 + (cnpj[2] - '0') * 4 + (cnpj[3] - '0') * 3 + (cnpj[4] - '0') * 2;


    for(int i = 5; i < 12; i++){
        soma += (cnpj[i] - '0') * (14-i); //  (14-i) == 9 A 2
    }

    soma += dv1_informado * 2;

    resto = soma % 11;

    if (resto < 2){ //se o resto for 0 ou 1
        dv2_calculado = 0;
    } else { // se o resto for 2 a 10
        dv2_calculado = 11 - resto; 
    }

    if (dv2_calculado != dv2_informado){
        return 0; //se o dv2 nao bate, cnpj é invalido
    }

    return 1; //CNPJ Valido
}


int analisacliente(char *cadastro)
{
    FILE *fp_analisa = fopen("clientes.csv", "r");
    char codigo[30], cpfcnpj[30];

    if (fp_analisa == NULL)
        return 0;

    while (fgets(texto, sizeof(texto), fp_analisa))
    {
        sscanf(texto, "%[^;];%[^;];", codigo, cpfcnpj);
        if (strcmp(cadastro, cpfcnpj) == 0)
        {
            fclose(fp_analisa);
            return 1;
        }
    }
    fclose(fp_analisa);
    return 0; // nao existe
}


void cadastrarcliente()
{
    clear();
    existe_codigo = 0;

    fp = fopen("clientes.csv", "a+");
    if (fp == NULL)
    {
        mvprintw(2, 2, "Erro ao abrir o arquivo.");
        getch();
        return;
    }

    nc_input(2, 2, "Digite o codigo do cliente:", p.codigo, 30);

    rewind(fp);

    //Ver se o código existe
    while (fgets(texto, sizeof(texto), fp))
    {
        char codigo_existe[30];
        sscanf(texto, "%[^;];", codigo_existe);
        if (strcmp(p.codigo, codigo_existe) == 0)
        {
            mvprintw(10, 2, "Codigo ja existe!");
            fclose(fp);
            getch();
            return;
        }
    }

    do {
        nc_input(5, 2, "Digite CPF(11) ou CNPJ(14): ", p.cadastro, 30);

        if (strlen(p.cadastro) != 11 && strlen(p.cadastro) != 14) {

            attron(COLOR_PAIR(4));
            mvprintw(7, 2, "Tamanho incorreto! Deve ter 11 ou 14 digitos.");
            attroff(COLOR_PAIR(4));

            getch();
            move(7, 2);
            clrtoeol();
        }

        if (strlen(p.cadastro) == 11 &&
            (strcmp(p.cadastro, "00000000000") == 0 ||
            strcmp(p.cadastro, "11111111111") == 0 ||
            strcmp(p.cadastro, "22222222222") == 0 ||
            strcmp(p.cadastro, "33333333333") == 0 ||
            strcmp(p.cadastro, "44444444444") == 0 ||
            strcmp(p.cadastro, "55555555555") == 0 ||
            strcmp(p.cadastro, "66666666666") == 0 ||
            strcmp(p.cadastro, "77777777777") == 0 ||
            strcmp(p.cadastro, "88888888888") == 0 ||
            strcmp(p.cadastro, "99999999999") == 0))
        {
            attron(COLOR_PAIR(4));
            mvprintw(10, 2, "CPF invalido! (repetido)");
            attroff(COLOR_PAIR(4));
            fclose(fp);
            getch();
            return;
        }

        if (strlen(p.cadastro) == 14 &&
            (strcmp(p.cadastro, "00000000000000") == 0 ||
            strcmp(p.cadastro, "11111111111111") == 0 ||
            strcmp(p.cadastro, "22222222222222") == 0 ||
            strcmp(p.cadastro, "33333333333333") == 0 ||
            strcmp(p.cadastro, "44444444444444") == 0 ||
            strcmp(p.cadastro, "55555555555555") == 0 ||
            strcmp(p.cadastro, "66666666666666") == 0 ||
            strcmp(p.cadastro, "77777777777777") == 0 ||
            strcmp(p.cadastro, "88888888888888") == 0 ||
            strcmp(p.cadastro, "99999999999999") == 0))
        {
            attron(COLOR_PAIR(4));
            mvprintw(10, 2, "CNPJ invalido! (repetido)");
            attroff(COLOR_PAIR(4));
            fclose(fp);
            getch();
            return;
        }

    } while (strlen(p.cadastro) != 11 && strlen(p.cadastro) != 14);


    switch(strlen(p.cadastro)){
            
        case 11: // CPF
            strcpy(p.cpf, p.cadastro);

        if(!valida_cpf(p.cpf)){

            attron(COLOR_PAIR(4));
            mvprintw(10, 2, "CPF invalido!");
            attroff(COLOR_PAIR(4));

            fclose(fp);
            getch();
            return;
        }

        while (analisacliente(p.cadastro)){
            mvprintw(12, 2, "Ja existe no sistema. Digite outro:");
            nc_input(13, 2, ">", p.cadastro, 30);
        }

        nc_input(15, 2, "Rua:", p.rua, 100);
        nc_input(17, 2, "Setor:", p.setor, 100);
        nc_input(19, 2, "Cidade:", p.cidade, 100);
        nc_input(21, 2, "Estado:", p.estado, 50);
        nc_input(23, 2, "Telefone:", p.telefone, 50);
        nc_input(25, 2, "Email:", p.email, 100);

        nc_input(27, 2, "Nome:", p.nome, 100);
        nc_input(29, 2, "Celular:", p.celular, 50);

        strcpy(p.opcao1, p.nome);
        strcpy(p.opcao2, p.celular);

        fprintf(fp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
            p.codigo, p.cadastro, p.rua, p.setor, p.cidade, p.estado,
            p.telefone, p.email, p.opcao1, p.opcao2);

        fclose(fp);
        mvprintw(32, 2, "Cliente cadastrado com sucesso!");
        getch();
        break;

        case 14: //CNPJ
            strcpy(p.cnpj, p.cadastro);

            if(!valida_cnpj(p.cnpj)){

                attron(COLOR_PAIR(4));
                mvprintw(10, 2, "CNPJ invalido!");
                attroff(COLOR_PAIR(4));

                fclose(fp);
                getch();
                return;
            }

            while (analisacliente(p.cadastro)){
                mvprintw(12, 2, "Ja existe no sistema. Digite outro:");
                nc_input(13, 2, ">", p.cadastro, 30);
            }

            nc_input(15, 2, "Rua:", p.rua, 100);
            nc_input(17, 2, "Setor:", p.setor, 100);
            nc_input(19, 2, "Cidade:", p.cidade, 100);
            nc_input(21, 2, "Estado:", p.estado, 50);
            nc_input(23, 2, "Telefone:", p.telefone, 50);
            nc_input(25, 2, "Email:", p.email, 100);

            nc_input(27, 2, "Razao Social:", p.razao_social, 100);
            nc_input(29, 2, "Contato:", p.nome_contato, 100);
            strcpy(p.opcao1, p.razao_social);
            strcpy(p.opcao2, p.nome_contato);

            fprintf(fp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",
            p.codigo, p.cadastro, p.rua, p.setor, p.cidade, p.estado,
            p.telefone, p.email, p.opcao1, p.opcao2);

            fclose(fp);

            attron(COLOR_PAIR(3));
            mvprintw(32, 2, "Cliente cadastrado com sucesso!");
            attroff(COLOR_PAIR(3));

            getch();
            break;
    }
    
}


void consultarcliente()
{
    clear();
    char codigo_busca[30];

    fp = fopen("clientes.csv", "r");
    if (fp == NULL)
    {
        mvprintw(2, 2, "Erro ao abrir arquivo.");
        getch();
        return;
    }

    nc_input(2, 2, "Digite o codigo do cliente:", codigo_busca, 30);

    int encontrado = 0;
    while (fgets(texto, sizeof(texto), fp))
    {
        sscanf(texto, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               p.codigo, p.cadastro, p.rua, p.setor, p.cidade, p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

        if (strcmp(codigo_busca, p.codigo) == 0)
        {
            attron(COLOR_PAIR(3));
            mvprintw(5, 2, "Cliente encontrado!");
            attroff(COLOR_PAIR(3));

            mvprintw(7, 2, "Codigo: %s", p.codigo);
            mvprintw(8, 2, "Cadastro: %s", p.cadastro);
            mvprintw(9, 2, "Rua: %s", p.rua);
            mvprintw(10, 2, "Setor: %s", p.setor);
            mvprintw(11, 2, "Cidade: %s", p.cidade);
            mvprintw(12, 2, "Estado: %s", p.estado);
            mvprintw(13, 2, "Telefone: %s", p.telefone);
            mvprintw(14, 2, "Email: %s", p.email);
            mvprintw(15, 2, "Opcao1: %s", p.opcao1);
            mvprintw(16, 2, "Opcao2: %s", p.opcao2);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado){
        attron(COLOR_PAIR(4));
        mvprintw(5, 2, "Cliente NAO encontrado.");
        attron(COLOR_PAIR(4));
    }

    fclose(fp);
    getch();
}


void listarcliente()
{
    clear();
    int linha = 2;

    fp = fopen("clientes.csv", "r");
    if (fp == NULL)
    {
        mvprintw(2, 2, "Erro ao abrir arquivo.");
        getch();
        return;
    }

    while (fgets(texto, sizeof(texto), fp))
    {
        sscanf(texto, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               p.codigo, p.cadastro, p.rua, p.setor, p.cidade, p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

        attron(COLOR_PAIR(7));
        mvprintw(linha, 2, "Codigo: %s", p.codigo);
        linha++;
        mvprintw(linha, 2, "Cadastro: %s", p.cadastro);
        linha++;
        mvprintw(linha, 2, "Rua: %s", p.rua);
        linha++;
        mvprintw(linha, 2, "Setor: %s", p.setor);
        linha++;
        mvprintw(linha, 2, "Cidade: %s", p.cidade);
        linha++;
        mvprintw(linha, 2, "Estado: %s", p.estado);
        linha++;
        mvprintw(linha, 2, "Telefone: %s", p.telefone);
        linha++;
        mvprintw(linha, 2, "Email: %s", p.email);
        linha++;
        mvprintw(linha, 2, "Opcao1: %s", p.opcao1);
        linha++;
        mvprintw(linha, 2, "Opcao2: %s", p.opcao2);
        linha++;
        attroff(COLOR_PAIR(7));

        attron(COLOR_PAIR(5));
        mvprintw(linha, 2, "----------------------------------------");
        attroff(COLOR_PAIR(5));

        linha += 2;

        if (linha > LINES - 5)
        {
            mvprintw(linha, 2, "-- Pressione ENTER para continuar --");
            getch();
            clear();
            linha = 2;
        }
    }

    fclose(fp);
    getch();
}


void removercliente()
{
    clear();
    char codigo_busca[30];
    FILE *temp;

    nc_input(2, 2, "Digite o codigo do cliente:", codigo_busca, 30);

    fp = fopen("clientes.csv", "r");
    if (fp == NULL)
    {
        mvprintw(2, 2, "Erro ao abrir arquivo.");
        getch();
        return;
    }

    temp = fopen("temp.csv", "w");
    if (temp == NULL)
    {
        mvprintw(2, 2, "Erro: arquivo temporario.");
        getch();
        return;
    }

    int encontrado = 0;
    while (fgets(texto, sizeof(texto), fp))
    {
        sscanf(texto, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
               p.codigo, p.cadastro, p.rua, p.setor, p.cidade, p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

        if (strcmp(codigo_busca, p.codigo) == 0)
        {
            encontrado = 1;

            attron(COLOR_PAIR(1));
            mvprintw(5, 2, "Cliente encontrado!");
            mvprintw(7, 2, "Remover? (S/N)");
            attroff(COLOR_PAIR(1));

            int c = getch();
            if (c == 'S' || c == 's')
            {
                attron(COLOR_PAIR(3));
                mvprintw(9, 2, "Removido!");
                attroff(COLOR_PAIR(3));
            }
            else
            {
                fprintf(temp, "%s", texto);

                attron(COLOR_PAIR(6));
                mvprintw(9, 2, "Cancelado, mantido.");
                attroff(COLOR_PAIR(6));
            }
        }
        else
        {
            fprintf(temp, "%s", texto);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!encontrado)
    {
        attron(COLOR_PAIR(4));
        mvprintw(11, 2, "Cliente NAO encontrado.");
        attroff(COLOR_PAIR(4));
        remove("temp.csv");
    }
    else
    {
        remove("clientes.csv");
        rename("temp.csv", "clientes.csv");
    }

    getch();
}

pessoa buscarCliente(const char *codigo_c){
    FILE *fp_cliente;
    char linha[1000];

    fp_cliente=fopen("clientes.csv", "r");

    if(fp_cliente == NULL){
       mvprintw(2,2,"Erro ao abrir o arquivo.");
       getch();
       pessoa vazio = {0};
        return vazio;
    }

    pessoa c_busca;

    while(fgets(linha, sizeof(linha), fp_cliente)){
        linha[strcspn(linha, "\n")] = 0;

        int cmp= sscanf(linha, "%[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^\n]", 
        c_busca.codigo, c_busca.cadastro, c_busca.rua, c_busca.setor, 
        c_busca.cidade, c_busca.estado, c_busca.telefone, c_busca.email, c_busca.opcao1, c_busca.opcao2);
         
        if(cmp >= 2 && strcmp(codigo_c, c_busca.codigo)){
            fclose(fp_cliente);
            return c_busca;
        }
    }
}

//-------------------------------------
// MENU CLIENTE (ncurses)
//-------------------------------------
void maincliente()
{
    char *opcoes[] = {
        "Cadastrar Cliente",
        "Consultar Cliente",
        "Remover Cliente",
        "Listar Clientes",
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
        mvprintw(1, 2, "=========== MENU CLIENTES ===========");
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
                cadastrarcliente();
                break;
            case 1:
                consultarcliente();
                break;
            case 2:
                removercliente();
                break;
            case 3:
                listarcliente();
                break;
            case 4:
                return;
            }
        }
    }
}

int main()
{

    initscr(); // inicia o ncurses
    cbreak();  // permite capturar teclas sem enter
    noecho();  // evita eco de teclas ao digitar
    keypad(stdscr, TRUE);

    maincliente();

    endwin(); // encerra ncurses
    return 0;
}
