
#include "cliente.h"

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

int analisacliente(char *cadastro) {
    FILE *fp_analisa = fopen("clientes.csv", "r");
    char codigo[30], cpfcnpj[30];

    if (fp_analisa == NULL) {
        printf("Erro ao abrir arquivo .");
        return 0;
    }

    while (fgets(texto, sizeof(texto), fp)) {
        sscanf(texto, "%[^;];%[^;];", codigo, cpfcnpj);
        if (strcmp(cadastro, cpfcnpj) == 0) {
            fclose(fp);
            return 1; // ja existe
        }
    }

    fclose(fp_analisa);

    return 0; // nao existe
}

void cadastrarcliente() {
    int existe_codigo = 0;

    fp = fopen("clientes.csv", "a+");
    if(fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o codigo do cliente: ");
    scanf("%s", p.codigo);

    rewind(fp); 

    // Ver se o código existe
    while(fgets(texto, sizeof(texto), fp)) {
        char codigo_existente[30];
        sscanf(texto, "%[^;];", codigo_existente);
        if(strcmp(p.codigo, codigo_existente) == 0) {
            existe_codigo = 1;
            break;
        }
    }

    if(existe_codigo) {
        printf("Este cóodigo ja existe. Digite outro.\n");
        fclose(fp);
        return;
    }

    printf("Digite o numero de cadastro do cliente (CPF ou CNPJ): ");
    scanf("%s", p.cadastro);

    switch(strlen(p.cadastro)) {

        case 11: // CPF
            strcpy(p.cpf, p.cadastro);

            if(!valida_cpf(p.cpf)) {
                printf("CPF inválido!\n");
                fclose(fp);
                return;
            }

            // analisa cliente
            while(analisacliente(p.cadastro)) {
                printf("O CPF %s ja esta cadastrado no sistema.\n", p.cadastro);
                printf("Digite um CPF diferente: ");
                scanf("%s", p.cadastro);
            }

            printf("Digite a rua, setor, cidade, estado, telefone e email: ");

            scanf(" %[^\n]", p.rua);
            scanf(" %[^\n]", p.setor);
            scanf(" %[^\n]", p.cidade);
            scanf(" %[^\n]", p.estado);
            scanf(" %[^\n]", p.telefone);
            scanf(" %[^\n]", p.email);
      
            printf("Digite o nome e o celular: ");
            scanf(" %[^\n]", p.nome);
            scanf(" %[^\n]", p.celular);

            strcpy(p.opcao1, p.nome);
            strcpy(p.opcao2, p.celular);

            fprintf(fp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", p.codigo, p.cadastro, p.rua, 
                p.setor, p.cidade, p.estado, p.telefone, p.email, p.opcao1, p.opcao2);
                        
            printf("Cliente cadastrado com sucesso! ");
                        
            fclose(fp);
            break;

        case 14: // CNPJ
            strcpy(p.cnpj, p.cadastro);

            if (!valida_cnpj(p.cnpj)) {
                printf("CNPJ invalido!\n");
                fclose(fp);
                return;
            }

            // analisa cliente
            while(analisacliente(p.cadastro)) {
                printf("O CNPJ %s ja esta cadastrado no sistema.\n", p.cadastro);
                printf("Digite um CNPJ diferente: ");
                scanf("%s", p.cadastro);
            }

            printf("Digite a rua, setor, cidade, estado, telefone e email: ");

            scanf(" %[^\n]", p.rua);
            scanf(" %[^\n]", p.setor);
            scanf(" %[^\n]", p.cidade);
            scanf(" %[^\n]", p.estado);
            scanf(" %[^\n]", p.telefone);
            scanf(" %[^\n]", p.email);
        
            printf("Digite a razao social e o nome de contato: ");
            scanf(" %[^\n]", p.razao_social);
            scanf(" %[^\n]", p.nome_contato);

            strcpy(p.opcao1, p.razao_social);
            strcpy(p.opcao2, p.nome_contato);

            fprintf(fp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", p.codigo, p.cadastro, p.rua, 
                    p.setor, p.cidade, p.estado, p.telefone, p.email, p.opcao1, p.opcao2);
                        
            printf("Cliente cadastrado com sucesso! ");
                        
            fclose(fp);            
            break;

        default:
            printf("Numero invalido.\n");
            fclose(fp);
            return;
    }

}

void consultarcliente(){
    int encontrado = 0;

    char codigo_busca[30];
    
    fp = fopen("clientes.csv", "r");

    if(fp == NULL){
        printf("Erro ao abrir arquivo. \n");
        return;
    }

    printf("Digite o codigo do cliente que deseja: ");
    scanf("%s", codigo_busca);

        while (fgets(texto, sizeof(texto), fp)) {
            texto[strcspn(texto, "\n")] = 0; // Remove o \n

            int campos = sscanf(texto, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
                                p.codigo, p.cadastro, p.rua, p.setor, p.cidade,
                                p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

            if (campos == 10) {
                if (strcmp(codigo_busca, p.codigo) == 0) {
                    printf("Cliente encontrado!\n");
                    printf("Codigo: %s\n", p.codigo);
                    printf("Cadastro: %s\n", p.cadastro);
                    printf("Rua: %s\n", p.rua);
                    printf("Setor: %s\n", p.setor);
                    printf("Cidade: %s\n", p.cidade);
                    printf("Estado: %s\n", p.estado);
                    printf("Telefone: %s\n", p.telefone);
                    printf("Email: %s\n", p.email);
                    printf("Opcao 1: %s\n", p.opcao1);
                    printf("Opcao 2: %s\n", p.opcao2);
                    encontrado = 1;
                    break;
                }
        }
    }

    if (!encontrado) {
        printf("Erro: cliente nao existe.\n");
    }

    fclose(fp);
}

void listarcliente(){
      
    fp = fopen("clientes.csv", "r");

    if(fp == NULL){
        printf("Erro ao abrir arquivo. \n");
        return;
    }


   while (fgets(texto, sizeof(texto), fp)) {
            texto[strcspn(texto, "\n")] = 0; // Remove o \n

            int campos = sscanf(texto, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
                                p.codigo, p.cadastro, p.rua, p.setor, p.cidade,
                                p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

            if (campos == 10) {
            
                    printf("\nCodigo: %s\n", p.codigo);
                    printf("Cadastro: %s\n", p.cadastro);
                    printf("Rua: %s\n", p.rua);
                    printf("Setor: %s\n", p.setor);
                    printf("Cidade: %s\n", p.cidade);
                    printf("Estado: %s\n", p.estado);
                    printf("Telefone: %s\n", p.telefone);
                    printf("Email: %s\n", p.email);
                    printf("Opcao 1: %s\n", p.opcao1);
                    printf("Opcao 2: %s\n\n", p.opcao2);
                                
        }
    }

    fclose(fp);
}

void removercliente(){
    int encontrado = 0;
    char codigo_busca[30];
    FILE *temp;

    printf("Digite o codigo do cliente que deseja: ");
    scanf("%s", codigo_busca);

    fp = fopen("clientes.csv", "r");

    if(fp == NULL){
        printf("Erro ao abrir arquivo. \n");
        return;
    }

    temp = fopen("temp.csv", "w");

    if(temp == NULL){
        printf("Erro ao abrir arquivo temporario. \n");
        return;
    }

    while (fgets(texto, sizeof(texto), fp)) {
        texto[strcspn(texto, "\n")] = 0; // Remove o \n

        int campos = sscanf(texto, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
                        p.codigo, p.cadastro, p.rua, p.setor, p.cidade,
                        p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

        if (campos == 10) {
            if (strcmp(codigo_busca, p.codigo) == 0) {
                printf("Cliente encontrado!\n");
                printf("Codigo: %s\n", p.codigo);
                printf("Cadastro: %s\n", p.cadastro);
                printf("Rua: %s\n", p.rua);
                printf("Setor: %s\n", p.setor);
                printf("Cidade: %s\n", p.cidade);
                printf("Estado: %s\n", p.estado);
                printf("Telefone: %s\n", p.telefone);
                printf("Email: %s\n", p.email);
                printf("Opcao 1: %s\n", p.opcao1);
                printf("Opcao 2: %s\n", p.opcao2);
                encontrado = 1;
                char confirma;

                printf("Deseja realmente remover esse cliente? (S|N) ");
                scanf(" %c", &confirma);

                if(confirma == 'S' || confirma == 's'){
                    printf("Cliente removido com sucesso! \n");
                        
                    continue; //não escreve no arquivo temporario (remove)
                } else {
                    printf("Cliente mantido, remocao cancelada. \n");
                }
            }
        }
        fprintf(temp, "%s\n", texto);
    }

    fclose(fp);
    fclose(temp);

    if(!encontrado){
        printf("\nErro: Cliente nao existe. \n");
        remove("temp.csv");
        return;
    }

    // substitui o original pelo temporário
    remove("clientes.csv");
    rename("temp.csv", "clientes.csv");
}

int buscarCliente(const char *codigoBuscado, char *nomeCliente) {
    FILE *fp = fopen("clientes.csv", "r");
    if (!fp) {
        printf("Erro ao abrir clientes.csv\n");
        return 0;
    }

    char linha[500];
    pessoa p;

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = 0;

        int campos = sscanf(
            linha,
            "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",
            p.codigo, p.cadastro, p.rua, p.setor, p.cidade,
            p.estado, p.telefone, p.email, p.opcao1, p.opcao2
        );

        if (campos == 10 && strcmp(p.codigo, codigoBuscado) == 0) {
            strcpy(nomeCliente, p.cadastro);  
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void maincliente(){
    char resp;

    printf("=============MENU CLIENTE==============\n");
    printf("========QUAL OPCAO VOCE DESEJA?========\n");
    printf("=======1 PARA CADASTRAR CLIENTE========\n");
    printf("=======2 PARA CONSULTAR CLIENTE========\n");
    printf("=======3 PARA REMOVER CLIENTE==========\n");
    printf("=======4 PARA LISTAR CLIENTE===========\n\n");
    scanf(" %c", &resp);

    switch(resp){
        case '1':
            cadastrarcliente();
            break;

        case '2': 
            consultarcliente();
            break;

        case '3':
            removercliente();
            break;

        case '4':
            listarcliente();
            break;

        default:
            printf("Nao existe. \n");
            break;
    }
}

int main(){
    maincliente();
    return 0;
}

