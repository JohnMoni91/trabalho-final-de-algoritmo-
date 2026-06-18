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
//Parcelas é maximo 12 mesmo?
//acredito que sim
#define LISTA 100
#define MAX_PARCELAS 12
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
    int qtdParcelas;
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
    char situacaoDaParcela; // A: em aberto, R: recebido, V: vencido, C: cancelado
}Parcela;

// Declarando variaveis globais de vendas
Parcela listaParcelas[500];  // A prateleira que guarda todas as parcelas
int qtdParcelas = 0;         // O contador de quantas parcelas existem
int proximoIdParcela = 1001; // O gerador de ID automático

Cliente listaClientes[LISTA];
int qtdClientes = 0;

vendas listaVendas[100];
int qtdVendas = 0;
int proximoIdVenda = 101;

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
void geradorParcelas(int idVenda, float valorTotal, int qtd, data dataVenda);


//declarando a função de diasPorMes
data diasPorMes(data dataAtual) {
    dataAtual.mes += 1;
    if (dataAtual.mes > 12) {
        dataAtual.mes = 1;
        dataAtual.ano += 1;
    }
    return dataAtual;
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
	int tam = strlen(cpf), i = 0, soma = 0,todosIguais = 1;
    int peso = 10, resto = 0, atualNumero = 0, digitosIniciais, digitosFinais;

    // 1 verificar se o cpf tem exatamente 11 digitos
	if(tam != 11){
		return 0;
	}

    // 2 verificar se o cpf não são iguais
    for(i = 0; i < 11; i++){
        if(cpf[i] != cpf[0]){
            todosIguais = 0;
            break;
        }
    }

    if(todosIguais == 1){
        return 0;
    }

    // 3 multiplicar os primeiros digitos. Já que o 10 numero é para proteger o 9 primeiros digitos
    for(i = 0; i < 9; i++){
            atualNumero = cpf[i] - '0';
            soma += (atualNumero * peso);
            peso--;
    }

    // armazenando a soma
    resto = soma % 11;
    // para fazer a verificação precisa do resto da divisão 

    //o resto não pode ter mais de 1 casa
    if(resto < 2){
        digitosIniciais = 0; // Se o resto der 0 ou 1, o digito vira 0. 
    } else {
        digitosIniciais = 11 - resto; // Senão a conta continua normal 
    }

    // Verifica se tem um numero na 10 casa
    if(digitosIniciais != (cpf[9] - '0')){
        return 0; // Se for diferente, o CPF é invalido
    }

    // Fase de verificar o segundo digito
    // Limpar a soma e peso
    soma = 0;
    peso = 11;

    // Multiplicar os 10 primeiros numeros. O 11 numero do CPF serve para proteger os 9 numeros bases e o 10 numero.
    // deve separar o 10 e 9 numero para poder fazer a validação
    for(i = 0; i < 10; i++){
        atualNumero = cpf[i] - '0';
        soma += (atualNumero * peso);
        peso--;
    }

     resto = soma % 11;

    if(resto < 2){
        digitosFinais = 0; 
    } else {
        digitosFinais = 11 - resto; 
    }

    // Verifica se tem um numero na 10 casa
    if(digitosFinais != (cpf[10] - '0')){
        return 0; // Se for diferente, o CPF é invalido
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

//
// vou fazer as financeiras aqui embaixo
// fica muito ruim?

//não tem problema. Só deixa declarado as coisas de função lá em cima e depois vai colocando aqui embaixo
float recibos() {
    float total = 0;
    int i;
    for (i = 0; i < qtdParcelas; i++) { //
        if (listaParcelas[i].situacaoDaParcela == 'R') {
            total += listaParcelas[i].valorDaParcela;
        }
    }
    return total;
}

float aindaReceber() {
    float total = 0;
    int i;
    for (i = 0; i < qtdParcelas; i++) {
        if (listaParcelas[i].situacaoDaParcela == 'A') {
            total += listaParcelas[i].valorDaParcela;
        }
    }
    return total;
}

float parcelasVencidas() {
    float total = 0;
    int i;
    for (i = 0; i < qtdParcelas; i++) {
        if (listaParcelas[i].situacaoDaParcela == 'V') {
            total += listaParcelas[i].valorDaParcela;
        }
    }
    return total;
}

void geradorParcelas(int idVenda, float valorTotal, int qtd, data dataVenda) {
	Parcela p;
    data vencimento;
    float valorParcela;
    int i;

	valorParcela = valorTotal / qtd;
    vencimento = dataVenda;
	for (i = 0; i < qtd; i++) {
        if (qtdParcelas >= MAX_PARCELAS) {
            printf("Limite de parcelas atingido\n");
            return;
        	}
		
	vencimento = diasPorMes(vencimento);
 		p.idParcela = proximoIdParcela++;
        p.idVenda  = idVenda;
        p.numeroDaParcela = i + 1;
        p.valorDaParcela = valorParcela;
        p.dataVencimento =  vencimento;
        p.dataRecebimento.dia = 0;
        p.dataRecebimento.mes = 0;
        p.dataRecebimento.ano = 0;
        p.situacaoDaParcela = 'A'; // A de Em aberto
 			listaParcelas[qtdParcelas] = p;
        	qtdParcelas++;
    }
}

/*
Só anotação, variaveis como a listaParcelas, qtdParcelas, proximoParcela não estavam declaradas

teve umas confusão entre qtd e qtde. Coloquei tudo qtd

vai ter que criar uma função chamada diaPorMes para poder executar o vencimento 

*/
