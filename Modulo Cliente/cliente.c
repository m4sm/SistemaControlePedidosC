#include "cliente.h"

void maincliente(){
    char resp;

    printf("=============MENU CLIENTE==============\n");
    printf("========QUAL OPCAO VOCE DESEJA?========\n");
    printf("=======1 PARA CADASTRAR CLIENTE========\n");
    printf("=======2 PARA CONSULTAR CLIENTE========\n");
    printf("=======3 PARA REMOVER CLIENTE==========\n");
    printf("=======4 PARA LISTAR CLIENTE===========\n\n");
    scanf("%c", &resp);

    switch(resp){
        case 1:
            cadastrarcliente();
            break;

        case 2: 
            consultarcliente();
            break;

        case 3:
            removercliente();
            break;

        case 4:
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