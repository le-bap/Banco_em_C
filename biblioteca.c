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

        printf("Tipo de conta (comum ou plus): ");
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
    printf("Digite o CPF da conta que deseja deletar: "); // informa o cliente a ser deletado
    scanf("%s", clienteEscolhido);
    clearBuffer();

    int escolhido = ProcurarCPF(lt, clienteEscolhido);
    printf("%d", escolhido);

    if (escolhido == -1){
        printf("Cliente não encontrado");
    }
    else{
        for (int i = escolhido; i != 999; i++){
        lt->cl[i] = lt->cl[i + 1];
        }
    }

    lt->qnt--;// ao deletar uma conta, as posições das restante devem "descer" para uma posição abaixo da que estava
    return 0;
}

int ListarClientes1(ListaClientes lt){
    for (int i = 0; i < lt.qnt; i++){ //apenas aparece as tarefas já estabelecidas
            printf("Nome: %s\n", lt.cl[i].nome);
            printf("CPF: %s\n", lt.cl[i].cpf);
            printf("Tipo de conta: %s\n", lt.cl[i].tipo);
            printf("Senha: %s\n", lt.cl[i].senha);
            printf("Valor: %.2f\n",  lt.cl[i].valor0);
            printf("\n");
        }
    return 0;
}

int Debitar(ListaClientes *lt){
    char senha[50];
    float valor;
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja debitar: "); // informa o cliente a ser debitado
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido); // acha o cpf do cliente para localizar seus dados

    if(escolhido == -1){
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{
        printf("Digite a senha: ");
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteEscolhido, senha);
        
        if(senhaCerta == 1){
            printf("Digite o valor a ser debitado: ");
            scanf("%f", &valor);
            FuncaoDebitar(lt, clienteEscolhido, valor);
        }
        else{
            printf("Senha errada\n");
        }
    }
}

int Depositar(ListaClientes *lt){
    char senha[50];
    float valor;
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja depositar: "); // informa o cliente a ser depositado
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido); // acha o cpf do cliente para localizar seus dados

    if(escolhido == -1){
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{
        printf("Digite a senha: ");
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteEscolhido, senha);
        
        if(senhaCerta == 1){
            printf("Digite o valor a ser depositado: ");
            scanf("%f", &valor);
            FuncaoDepositar(lt, clienteEscolhido, valor);
        }
        else{
            printf("Senha errada\n");
        }
    }
}

int Extrato(ListaClientes *lt, Operacao *op){

    char senha[50];
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja ver o extrato: "); // informa o cpf do cliente que quer ver o extrato
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido); // acha o cpf do cliente para localizar seus dados

    if(escolhido == -1){
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{
        printf("Digite a senha: ");
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteEscolhido, senha);
        
        if(senhaCerta == 1){
            EscreverNoExtrato(op, lt, clienteEscolhido);
        }
    }
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
            return i;  // Encontrou o CPF, retorna o cliente correspondente
        }
    }

    return -1;  // CPF não encontrado
}

int ProcurarSenha(ListaClientes *lt, char *cpfProcurado, char *senha) {
    int cpf = ProcurarCPF(lt, cpfProcurado); // Obtém o índice do cliente com o CPF

    // Verifica se o CPF foi encontrado
    if (cpf != -1) {
        // Compara as senhas usando strcmp
        if (strcmp(lt->cl[cpf].senha, senha) == 0) {
            return 1;  // Senha correta
        } else {
            return 0;  // Senha incorreta
        }
    }
}

/////////////////////////////////////////////////////

int FuncaoDebitar(ListaClientes *lt, char *cpfProcurado, float valor){
    int cpf = ProcurarCPF(lt, cpfProcurado); // Obtém o índice do cliente com o CPF
    
    // Verifica se o CPF foi encontrado
    if (cpf != -1) {
        if (strcmp(lt->cl[cpf].tipo, "comum") == 0){ // se a conta for do tipo comum 
            float taxa = valor * 0.05;
            if(lt->cl[cpf].valor0 > -1000){ // estabelece a taxa de desconto e verifica se o saldo é menor do que o permitido
                lt->cl[cpf].valor0 = lt->cl[cpf].valor0 - valor - taxa;
            }else{
                printf("Saldo insuficiente");
                return -1;
            }

        }else if(strcmp(lt->cl[cpf].tipo, "plus") == 0){
            float taxa2 = valor * 0.03;
            if(lt->cl[cpf].valor0 > -5000){
                lt->cl[cpf].valor0 = lt->cl[cpf].valor0 - valor - taxa2;
            }else{
                printf("Saldo insuficiente");
                return -1;
            }
        }  
    } 
}

int FuncaoDepositar(ListaClientes *lt, char *cpfProcurado, float valor){
    int cpf = ProcurarCPF(lt, cpfProcurado);
     // Verifica se o CPF foi encontrado
    if (cpf != -1) {
        lt->cl[cpf].valor0 = lt->cl[cpf].valor0 + valor; // Acrescenta o valor a conta
    } 
    return 0;
} 


int EscreverNoExtrato(Operacao *op, ListaClientes *lt, char *cpfProcurado){
    int cpf = ProcurarCPF(lt, cpfProcurado);
    // FILE *arq = fopen("Extrato.txt", "w");
    printf("%s", lt->cl->op->descricao);
    // fclose(arq);
    return 0;
}


// NAO ESQUECER DOS COMMITS