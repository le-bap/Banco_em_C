#include <stdio.h>
#include "biblioteca.h"

int main(){
    ListaClientes lt;
    int cod;
    char arquivo[] = "Clientes.txt";
    
    cod = CarregarCliente(&lt, arquivo);
    if (cod == 1){
        lt.qnt = 0;
    }

    int opcao;

    do{
        menu();
        scanf("%d", &opcao);
        
        clearBuffer();

        if(opcao == 1){
            NovoCliente(&lt);
        }
    }while (opcao != 0);

    cod = SalvarCliente(&lt, "Clientes.txt");

    if(cod !=0){
        printf("Erro ao salvar os clientes");
    }

    return 0;
}