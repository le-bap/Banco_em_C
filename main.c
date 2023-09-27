#include <stdio.h>
#include "biblioteca.h"

int main(){
    ListaClientes lt;
    int cod;
    char arquivo[] = "Clientes.txt";
    int opcao;

    do{
        menu();
        scanf("%d", &opcao);
        clearBuffer();

        if(opcao == 1){
            NovoCliente(&lt);
        }
    }while (opcao != 0);

    return 0;
}