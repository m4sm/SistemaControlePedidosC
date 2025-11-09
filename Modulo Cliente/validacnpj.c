#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(){
    char cnpj[15];

    printf("Digite seu CNPJ: ");
    scanf("%s", cnpj);

    int resultado = valida_cnpj(cnpj);

    printf("O CNPJ eh %s \n", resultado ? "VALIDO" : "INVALIDO");

    return 0;
}