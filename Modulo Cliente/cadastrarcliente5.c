#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char codigo[30];
    char cadastro[15];
    char cpf[12];
    char cnpj[15];
    char rua[30];
    char setor[30];
    char cidade[30];
    char estado[30];
    char telefone[30];
    char email[50];
    char nome[50];
    char celular[30];
    char razao_social[30];
    char nome_contato[50];
    char opcao1[50];
    char opcao2[50];

} pessoa;

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


int main() {
    pessoa p;
    FILE *fp;
    char texto[1000];
    int existe_codigo = 0;

    // Garante que o arquivo existe
    fp = fopen("clientes.csv", "a+");
    fclose(fp);

    // Reabre para leitura e escrita
    fp = fopen("clientes.csv", "r+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Digite o codigo identificador do cliente: ");
    scanf("%s", p.codigo);

    // Verifica se já existe o código
    while (fgets(texto, sizeof(texto), fp)) {
        char codigo_existente[30];
        sscanf(texto, "%[^;];", codigo_existente); // lê só o primeiro campo (código)

        if (strcmp(p.codigo, codigo_existente) == 0) {
            existe_codigo = 1;
            break;
        }
    }
    
    if (existe_codigo) {
        printf("Este codigo ja existe. Digite outro. \n");
    } else {
        printf("Digite o numero de cadastro do cliente: ");
        scanf("%s", p.cadastro);


        switch(strlen(p.cadastro)){
            case 11:
                strcpy(p.cpf, p.cadastro);

                int resultado = valida_cpf(p.cpf);

                if(!resultado){
                    printf("CPF invalido! ");
                    break;
                } 
                else{

                    int existe_cpf = 0;

                    rewind(fp);

                    while(fgets(texto, sizeof(texto), fp)){

                        //ler o codigo e o cpf da linha
                        char codigo_existente[30], cadastro_existente[20];
                        sscanf(texto, "%[^;];%[^;];", codigo_existente, cadastro_existente);

                        if (strcmp(p.cadastro, cadastro_existente) == 0) {
                            existe_cpf = 1;
                            break;
                        }
                    }
                    
                    if (existe_cpf){
                        printf("%s ja esta cadastrado no sistema. \n", p.cadastro);
                    } else{
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
                    }


                }

                break;

            case 14:
                strcpy(p.cnpj, p.cadastro);

                int resultadocnpj = valida_cnpj(p.cnpj);

                if(!resultadocnpj){
                    printf("CNPJ invalido! ");
                    break;
                } else{

                    int existe_cnpj = 0;

                    rewind(fp);

                    while(fgets(texto, sizeof(texto), fp)){

                        char codigo_existente[30], cadastro_existente[20];
                        sscanf(texto, "%[^;];%[^;];", codigo_existente, cadastro_existente);

                        if (strcmp(p.cadastro, cadastro_existente) == 0) {
                            existe_cnpj = 1;
                            break;
                        }
                    }

                    if (existe_cnpj){
                        printf("%s ja esta cadastrado no sistema. \n", p.cadastro);
                    } else{
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
                    }
                }
                break;
        }

    }

    return 0;
}
