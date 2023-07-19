#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct Cliente{
    long int cpf;
    struct tm *data_entrega;
    struct Cliente *prox;
}Cliente;

typedef struct{
    int qtdClientes;
    Cliente *inicio;
}Fila;

void addCliente(Fila *fila, long int cpf, struct tm *data_entrega);
void consultarFila(Fila fila);
void removerCliente(Fila *fila, int dia_atual);

//Adiciona um cliente 
void addCliente(Fila *fila, long int cpf, struct tm *data_entrega){
    Cliente *aux, *novo = (Cliente*)malloc(sizeof(Cliente));

    novo -> cpf = cpf;
    novo -> data_entrega = data_entrega; 
    novo -> prox = NULL;

    if(fila -> inicio == NULL){
        fila -> inicio = novo;
    }
    else{
        aux = fila -> inicio;

        while(aux -> prox != NULL){
            aux = aux -> prox;
        }
        aux -> prox = novo;
    }
    fila -> qtdClientes++;
}

//Imprime a fila
void consultarFila(Fila fila){
    Cliente *novo = fila.inicio;

    printf("\n*** CLIENTES ***\n");
    printf("\nQuantidade de clientes na fila: %d\n", fila.qtdClientes);

    while(novo != NULL){
        printf("\nCPF: %ld", novo -> cpf);
        printf("\nData prevista de entrega: %d/%d/%d", novo -> data_entrega -> tm_mday, 
            novo -> data_entrega -> tm_mon + 1, 
            novo -> data_entrega -> tm_year + 1900);

        novo = novo -> prox;

        printf("\n");
    }
}

//Remove o cliente se a data de entrega estiver expirada
void removerCliente(Fila *fila, int dia_atual){
	Cliente *inicio = fila -> inicio;
	
	if(inicio != NULL && inicio -> data_entrega -> tm_yday < dia_atual){
		fila -> inicio = inicio -> prox;
		free(inicio);
		fila -> qtdClientes--;
	}
}

int main(){ 
    setlocale(LC_ALL, "Portuguese");

    //Variáveis para as opções do menu e para o CPF do cliente
    int op; 
    long int cpf;
    
    //Declarando as variáveis que vão armazenar a data
    struct tm *data;
    time_t segundos;

    //Declarando e inicializando a fila
    Fila fila;
    fila.inicio = NULL;
    fila.qtdClientes = 0;

    printf("\n*** ASSISTÊNCIA TÉCNICA ***\n");

    do{
        //Pega a data atual do sistema em segundos
        time(&segundos);

        printf("\n1 - Consultar a fila");
        printf("\n2 - Cadastrar cliente");
        printf("\n0 - Sair");
        printf("\n\nInforme a opção desejada: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                consultarFila(fila);
                break;
            case 2:
                printf("\nInforme o CPF do cliente: ");
                scanf("%ld", &cpf);
				
                //Adiciona 2 dias na data do sistema e deixa em formato legível
                segundos += 172800;
                data = localtime(&segundos);
                
                addCliente(&fila, cpf, data);
                removerCliente(&fila, (data -> tm_yday) - 2);

                break;
            default:
            	printf("\nOpção inválida\n");
        }
    }while(op != 0);

    return 0;
}