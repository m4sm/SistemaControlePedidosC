#include "cliente.h"

void listarcliente(){
      
    fp = fopen("clientes.csv", "r");

    if(fp == NULL){
        printf("Erro ao abrir arquivo. \n");
        return;
    }

    /*printf("\n--- LISTAGEM DE CLIENTES CADASTRADOS ---\n\n");
    printf("CODIGO | CPF/CNPJ     | RUA               | SETOR         | CIDADE        | ESTADO | TELEFONE   | EMAIL        | NOME/RAZAO SOCIAL         | CELULAR/NUMERO DE CONTATO     |\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    */

   while (fgets(texto, sizeof(texto), fp)) {
            texto[strcspn(texto, "\n")] = 0; // Remove o \n

            int campos = sscanf(texto, " %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^;] ; %[^\n]",
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

int main(){
    listarcliente();
}