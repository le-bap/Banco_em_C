#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

// utilizado para rodar o menu toda vez que alguma ação for realizada no programa
void menu(){
    printf("\nBanco QuemPoupaTem\n");
    printf("\nEscolha uma das opções abaixo:\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência entre contas\n0. Sair\n");
    printf(">>> ");
}

int NovoCliente(ListaClientes *lt){
    if(lt->qnt<1000){
        printf("Digite o seu nome: ");
        scanf(" %[^\n]s", lt->cl[lt->qnt].nome);
        clearBuffer();

        printf("Digite o seu cpf: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].cpf);
        clearBuffer();

        printf("O tipo de conta: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].tipo);
        clearBuffer();

        printf("Digite o valor inicial da conta: ");
        scanf("%f", &lt->cl[lt->qnt].valor0);
        clearBuffer();

        printf("Senha do usuario: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].senha);
        clearBuffer();
    }
    else{
        printf("Maximo de clientes atingidos");
    }
    lt -> qnt++;
    return 0;
}

int DeletarCliente(ListaClientes *lt){
    char clienteEscolhido[11];
    printf("Digite o CPF da conta que deseja deletar? "); // informa o cliente a ser deletado
    scanf("%s", clienteEscolhido);
    clearBuffer();

    int escolhido = ProcurarCPF(lt, clienteEscolhido);

    for (int i = escolhido; i != 999; i++){
        lt->cl[i] = lt->cl[i + 1];
    }

    lt->qnt--;// ao deletar uma conta, as posições das restante devem "descer" para uma posição abaixo da que estava
    return 0;
}

int ListarClientes1(ListaClientes lt){
    for (int i = 0; i < lt.qnt; i++){ //apenas aparece as tarefas já estabelecidas
            printf("Nome: %s\n", lt.cl[i].nome);
            printf("CPF: %s\n", lt.cl[i].cpf);
            printf("Tipo de conta: %s\n", lt.cl[i].tipo);
            printf("\n");
        }
    return 0;
}

int Debitar(ListaClientes *lt){
    char senha[10];
    float valor;
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja debitar? "); // informa o cliente a ser debitado
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido);
    printf("%d", escolhido);

    while (escolhido != 1) // se o cpf não for encontrado
    {
        printf("CPF nao encontrado! porra \n");
        printf("Digite o CPF da conta que deseja debitar? "); // informa o cliente a ser debitado
        scanf("%s", clienteEscolhido);
        int escolhido = ProcurarCPF(lt, clienteEscolhido);
        if (escolhido == 1){
            break;
        }
    }
    
    printf("Digite a senha: "); // informar a senha para conferir se esta certa
    scanf("%s", senha);
    clearBuffer();
    int senhaachada = ProcurarSenha(lt, clienteEscolhido);

    while (senha != senhaachada){
        printf("senha incorreta! porra");
    }
    
    printf("Digite o valor "); // informa o cliente a ser debitado
    scanf("%f", &valor);
    clearBuffer();

}

//////////////////////////////////////////////////////////////////
int SalvarCliente(ListaClientes *lt, char nome[]){
    FILE *f = fopen(nome, "wb");
    if(f == NULL){
        return 1;
    }else{
        fwrite(lt, sizeof(ListaClientes), 1, f);
        fclose(f);
    }
    return 0;
}

int CarregarCliente(ListaClientes *lt, char nome[]){
    FILE *f = fopen(nome, "rb");
    if(f == NULL){
        return 1;
    }
    else{
        fread(lt,sizeof(ListaClientes), 1, f);
        fclose(f);
    }
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/////////////////////////////////////////////////////
int ProcurarCPF(ListaClientes *lt, char *cpfProcurado) {

    // Percorre a lista de clientes
    for (int i = 0; i < lt->qnt; i++) {
        // Compara o CPF atual com o CPF procurado
        if (strcmp(lt->cl[i].cpf, cpfProcurado) == 0) {
            return 1;  // Encontrou o CPF, retorna o cliente correspondente
        }
    }

    return 0;  // CPF não encontrado
}

int ProcurarSenha(ListaClientes *lt, char *senha){
    for(int i = 0; i < lt->qnt; i++){
        if (strcmp(lt->cl[i].senha, senha) == 0) {
            return i;  // Encontrou o CPF, retorna o cliente correspondente
        } 
    }
    return 0;
}

// NAO ESQUECER DOS COMMITS