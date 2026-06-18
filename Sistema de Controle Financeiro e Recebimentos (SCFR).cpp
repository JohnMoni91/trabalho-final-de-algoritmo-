#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*
#include <time.h>
#include <locale.h>

Locale é para localização do idioma
Só para deixar salvo caso o professor permitir. time.h É para verificar o ano conforme o tempo atual
*/

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
}Cliente;

// estrutura das vendas
typedef struct Vendas
{
    int idVenda;
    Cliente cliente;
    float valorTotalVenda;
    int formaPagamento;
    int qtdeParcelas;
    data dataVenda;
    char observacao[50];
}vendas;

// estrutura das parcela
typedef struct Parcelas
{
    int idParcela;
    int idVenda;
    int numeroDaParcela;
    float valorDaParcela;
    data dataVencimento;
    data dataRecebimento;
    char situacaoDaParcela;
}Parcela;

// Funções Financeiras
float recibos();
float aindaReceber();
float parcelasVencidas();
float debitosPendentes();
float faturamentoTotal();

// Funções de validação
int validarCPF(char cpf[]);
int validarData(data d);
// obs: usar regra do calendario gregoriano
int validarTelefone(char telefone[]);
// obs: não esquecer de colocar 0 no inicio do ddd, e também ter 11 - 12 digitos (valores entre 0 - 9 )
int validarCartao(char numeroCartao[]);
int validarEmail (char email[]);
int registroVendas();
/*
obs: Todas as vendas devem ser registradas com vinculo do cliente a venda denifirá a forma de pagamento
pagamento à vista deverá ser gerado apenas com uma parcela somente para venda
Para pagamentos a prazo, deverá ser gerado uma parcela para cada prestração definida, estando vinculada à venda e status incial "Em Aberto"
*/
int anoBissexto(int ano);


//Menu
void cadastroClientes();
void buscarClientes();
int registroVendas();
/*
obs: Todas as vendas devem ser registradas com vinculo do cliente a venda denifirá a forma de pagamento
pagamento à vista deverá ser gerado apenas com uma parcela somente para venda
Para pagamentos a prazo, deverá ser gerado uma parcela para cada prestração definida, estando vinculada à venda e status incial "Em Aberto"
*/
int consultarVendas();
/*
Consultar com base nos dados da venda e parcela existente. O cliente pode ter mais de uma compra realizada
*/

// gerador automatico de parcelas
void geradorParcelas();

int main(){
	int op;
	
	do{
		printf("\nSISTEMA DE CONTROLE FINANCEIRO\n");
		printf("\n1 - Cadastro de cliente\n");
		printf("\n0 - Sair\n");
		
		scanf("%d", &op);
		
		getchar();
		
		switch(op){
			case 1:
				cadastroClientes();
				break;
			case 0:
				printf("\nSaindo...\n");
                break;
  			default:
				printf("\nDigite novamente\n");
                break;
		}
	}while(op != 0);

    return 0;
}

void cadastroClientes(){
    Cliente listaClientes[LISTA];
    int qtdClientes = 0;
    
    // verifica se a lista j� est� cheia
    if (qtdClientes >= LISTA) {
        printf("\nLimite de clientes cadastrados atingido!\n");
        return; // sai da fun��o
    }

    Cliente novoCliente;
    
    // CPF
    printf("\nDigite o CPF: ");
    fgets(novoCliente.CPF, 20, stdin);

    // validando cpf
    if(validarCPF(novoCliente.CPF) == 1){
        printf("\nCPF valido!\n");
    } else {
        printf("\nCPF invalido!\n");
    }

    // Nome
    printf("\nDigite o nome: ");
    fgets(novoCliente.nome, 50, stdin);

    // Telefone
    printf("\nDigite o telefone: ");
    fgets(novoCliente.telefone, 15, stdin);

    if(validarTelefone(novoCliente.telefone) == 1){
        printf("\nTelefone valido!\n");
    } else {
        printf("\nTelefone invalido!\n");
    }

    // Data de nascimento
    printf("\nDigite o dia de seu nascimento: ");
    scanf("%d", &novoCliente.dataNascimento.dia);

    printf("\nDigite o mes de seu nascimento: ");
    scanf("%d", &novoCliente.dataNascimento.mes);

    printf("\nDigite o ano de seu nascimento: ");
    scanf("%d", &novoCliente.dataNascimento.ano);

    if(validarData(novoCliente.dataNascimento) == 1){
        printf("\nData valida!\n");
    } else {
        printf("\nData invalida!\n");
    }

    // Numero de cartao
    printf("\nDigite o numero do cartao: ");
    fgets(novoCliente.numeroCartao, 20, stdin);

    if(validarCartao(novoCliente.numeroCartao) == 1){
        printf("\nNumero do cartao valido!\n");
    } else {
        printf("\nNumero do cartao invalido!\n");
    }

	// Chave Pix ou email
	printf("\nDigite a sua chave Pix (somente email): ");
	fgets(novoCliente.chavePix, 30, stdin);

	if(validarEmail(novoCliente.chavePix) == 1){
		printf("\nEmail/Pix valido!\n");
	} else {
		printf("\nEmail invalido!\n");
	}
	
	listaClientes[qtdClientes] = novoCliente;
    qtdClientes++;
}

int validarCartao(char numeroCartao[]){
	int soma = 0, i = 0, tam = strlen(numeroCartao), casa = 0, digito;

	// percorrer todos os numeros impar
	for(i = tam - 1; i >= 0; i--){ // percorre cada numero de direita para esquerda 
		
		//alterar o tipo char para int
		digito = numeroCartao[i] - '0';

		//se for a posição impar, ele dobra
		if(casa == 1){
			digito *= 2;
		} if(digito > 9){ // Não deve ser mais do que nove a soma
			digito -= 9;
		}

		soma += digito;

		// alterar de 0 para 1 para o loop continuar
		if(casa == 0){
			casa = 1;
		} else {
			casa = 0; 
		}
	}

	// se for divisivel por 10, o cartão é valido
	if(soma % 10 == 0){
		return 1;
	} else {
		return 0;
	}
}

int validarData(data d) {
    // verificar ano
    if(d.ano < 1900 || d.ano > 2026){
        return 0;
    }

    // verifica o mes
    if(d.mes < 1 || d.mes > 12){
        return 0;
    }

    // colocando quantos dias tem por mes
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // vendo se o mes de fevereiro é ano bissexto
    if(d.mes == 2 && anoBissexto(d.ano)){
        diasPorMes[2] = 29;
    }

    // verificando o dia
    if(d.dia < 1 || d.dia > diasPorMes[d.mes]){
        return 0;
    }
    return 1;
    // return 0 é falso
    // return 1 é verdadeiro
}

int anoBissexto(int ano){
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        return 1;
    }
    return 0;
}

//validando telefone
int validarTelefone(char telefone[]) {
    int TAM = strlen(telefone);
    int i = 0;
    if (TAM != 11 && TAM != 12) { return 0; }
    if (telefone[0] != '0') { return 0; }

    for(i = 0; i < TAM; i++) {
        if (telefone[i] < '0' || telefone[i] > '9'){
            return 0;
        }
    }
    return 1;  
}

int validarCPF(char cpf[]){
	int tam = strlen(CPF), i = 0, soma = 0, ;
	
	if(tam != 11){
		return 0;
	}
	
	
	
	return 1;
}

// validando o email
int validarEmail (char email[]) {
    int TAM = strlen(email);
    int psAR = -1,psPonto = -1, qtdAR = 0;     //psAR é a posição do '@' e o psPonto é a posição do '.', o -1 é 'nao encontrado'
	int i = 0;
	
    for (i = 0; i < TAM; i++) {
        if (email[i] == '@') {
            qtdAR++;
            psAR = i;
        }
    }

    if (qtdAR != 1 || psAR < 2) { return 0; }
    for (i = psAR + 1; i < TAM; i++) {
        if (email[i] == '.') {
        psPonto = i;
        break;
        }
    }

    if (psPonto == -1 || (psPonto - psAR - 1) < 2) { return 0; }
    if ((TAM - 1 - psPonto) < 2) { return 0; }

    return 1;
}
