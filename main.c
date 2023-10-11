#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

int main(){
    ListaClientes lt;
    Operacao op;
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
        else if(opcao == 2){
            DeletarCliente(&lt);
        }
        else if(opcao == 3){
            ListarClientes1(lt);
        }
        else if(opcao == 4){
            Debitar(&lt);
        }
        else if(opcao == 5){
            Depositar(&lt);
        }
        else if(opcao == 6){
            Extrato(&lt, &op);
        }
        else if(opcao == 7){
            Transferencia(&lt);
        }
        else{
            printf("Escolha uma opção válida");
        }
        

        
    }while (opcao != 0);

    cod = SalvarCliente(&lt, "Clientes.txt");

    if(cod !=0){
        printf("Erro ao salvar os clientes");
    }

    return 0;
}