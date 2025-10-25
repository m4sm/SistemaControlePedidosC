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
} pessoa;

int valida_cpf(char cpf[12]){
    int soma = 0;
    int primeiro_digito =  cpf[10] - '0';
    int segundo_digito = cpf[11] - '0';
    int resto = 0;
    int valido = 0;

    //VALIDACAO DO PRIMEIRO DIGITO
    for(int i = 10; i >= 2; i--){
        soma += cpf[i] * i;
    }

    resto = (soma * 10) % 11;

    if(resto == cpf[10]){
        primeiro_digito = 1;
    }

    soma = 0;
    resto = 0;

    //VALIDACAO DO SEGUNDO DIGITO
    for(int i = 11; i >= 2; i--){
        soma += cpf[i] * i;

        resto = (soma * 10) % 11;
        if(resto == cpf[11]){
            segundo_digito = 1;
        }
    }
    
    if(primeiro_digito == 1 && segundo_digito == 1){
        valido = 1;
    }

    return valido;
    
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
        sscanf(texto, "%s", codigo_existente); // lê só o primeiro campo (código)

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

        // VENDO SE É CPF OU CNPJ
        if(strlen(p.cadastro) == 11){
            strcpy(p.cpf, p.cadastro);
        } 
        
        if(strlen(p.cadastro) == 14){
            strcpy(p.cnpj, p.cadastro);
        }

        /*if(p.cpf && p.cnpj == NULL){
            printf("Invalido");
        }*/

        // Vai para o final do arquivo e grava
        fseek(fp, 0, SEEK_END);
        fprintf(fp, "%s %s\n", p.codigo, p.cadastro);

        printf("Cliente cadastrado com sucesso! \n");
    }

    fclose(fp);
    return 0;
}
