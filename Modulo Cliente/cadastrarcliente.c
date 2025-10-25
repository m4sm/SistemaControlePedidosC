#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char codigo[30];
    char cpf[12];
    char cnpj[15];
    char rua[30];
    char setor[30];
    char cidade[30];
    char estado[30];
} pessoa;


int main(){

    pessoa p;
    FILE *fp;
    char texto[1000];
    int existe_codigo = 0;


    //VER SE EXISTE O CODIGO
    fp = fopen("clientes.csv", "r+");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Digite o codigo identificador do cliente: "); // JA E NO CLIENTE
    scanf("%s", p.codigo);

    //VER SE JA EXISTE O
    while(fgets(texto, 1000, fp)){

        char codigo_existente[30];
        sscanf(texto, "%s", codigo_existente);

        if(strcmp(p.codigo, texto) == 0){
            existe_codigo = 1;
            break;
        }
    }

    if(existe_codigo){
        printf("Esse codigo ja existe. Digite Outro. ");
    }
    else{
        printf("Digite o numero de cadastro: ");
        scanf("%s", p.cpf);

        fprintf(fp, "%s %s \n", p.codigo, p.cpf);
    }


    fclose(fp);
    
    return 0;
}