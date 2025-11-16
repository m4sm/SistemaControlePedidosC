#ifndef CLIENTE_H
#define CLIENTE_H

#define maxNome 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
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
    char opcao1[50]; // nome e celular
    char opcao2[50]; //razao social e nome de contato

} pessoa;

int valida_cpf(char cpf[12]);
int valida_cnpj(char cnpj[15]);
void cadastrarcliente();
int analisacliente(char *cadastro);
void consultarcliente();
void removercliente();
void listarcliente();
void maincliente();

pessoa p;
FILE *fp;
char texto[1000];
char codigo_existente[1000];
int existe_codigo = 0;

#endif