#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LISTA 100

// estrutura de data de registro 
typedef struct Data
{
 int dia;
 int mes;
 int ano;
}data;

// estrutura de clientes
typedef struct Clientes
{
    char CPF[20];
    char nome[50];
    char telefone[15];
    data dataNascimento;
    char numeroCartao[20];
    char chavePix[30];
}Cliente ;

// Funções Financeiras
// quanto recebeu
float recibos();
// ainda para receber
float aindaReceber();
// parcelas vencidas
float parcelasVencidas();
// debitos pendentes
float debitosPendentes();
// faturamento total da emprea
float faturamentoTotal();

// Funções de validação
// validar CPF
int validarCPF();
// validar data
int validarData(data d);
// obs: usar regra do calendario gregoriano
// validar telefone
// obs: não esquecer de colocar 0 no inicio do ddd, e também ter 11 - 12 digitos (valores entre 0 - 9 )
int validarTelefone();
// validar cartão
int valdiarCartao();
//validar email
int validarEmail();

//cadastro de clientes
void cadastroClientes();

//buscar clientes via Cpf, numero de cartao, chave pix e nome, ser exibido no final os dados
void buscarClientes();

int main(){



    return 0;
}

int validaData(data d) {
	while(data == 1){		
	    if (d.dia < 1 || d.dia > 30) {
	        return 0; 
	    }
	
	    if (d.mes < 1 || d.mes > 12) {
	        return 0;
	    }
	    
	    if (d.ano < 1900 || d.ano > 2025) {
	        return 0;
	    }
	}
    return 1; 
}
