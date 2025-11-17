#ifndef CLIENTE_H
#define CLIENTE_H

#define maxNome 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char codigo[30];
    char cadastro[20];        // CPF/CNPJ
    char cpf[12];
    char cnpj[15];
    char rua[100];            
    char setor[50];
    char cidade[50];
    char estado[5];           // GO, PA, BA, etc.
    char telefone[30];
    char email[100];          
    char nome[100];
    char celular[30];
    char razao_social[100];
    char nome_contato[100];
    char opcao1[100];
    char opcao2[100];
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
int existe_codigo;

#endif