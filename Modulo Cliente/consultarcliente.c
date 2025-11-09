#include "cliente.h"

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

            int campos = sscanf(texto, " %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^\n]",
                                p.codigo, p.cadastro, p.rua, p.setor, p.cidade,
                                p.estado, p.telefone, p.email, p.opcao1, p.opcao2);

            if (campos == 10) {
                if (strcmp(codigo_busca, p.codigo) == 0) {
                    printf("\nCliente encontrado!\n");
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

int main(){

    consultarcliente();

    return 0;
}