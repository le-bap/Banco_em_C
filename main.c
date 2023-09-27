#include <stdio.h>
#include "biblioteca.h"

int main(){
    ListaClientes lt;

    int opcao;

    do{
        menu();
        scanf("%d", &opcao);

        if(opcao == 1){
            NovoCliente(&lt);
        }
    }while (opcao != 0);

    return 0;
}