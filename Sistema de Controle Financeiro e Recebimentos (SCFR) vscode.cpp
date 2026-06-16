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
int validarCPF(char cpf[]);

// validar data
int validarData(data d);
// obs: usar regra do calendario gregoriano

// validar telefone
int validarTelefone(char telefone[]);
// obs: não esquecer de colocar 0 no inicio do ddd, e também ter 11 - 12 digitos (valores entre 0 - 9 )

// validar cartão
int validarCartao(char numeroCartao[]);

// validar email
int validarEmail (char email[]);

// cadastro de clientes
void cadastroClientes();

// buscar clientes via Cpf, numero de cartao, chave pix e nome, ser exibido no final os dados
void buscarClientes();

// verificação de ano bissexto
int anoBissexto(int ano);



// função para registro de venda
int registroVendas();
/*
obs: Todas as vendas devem ser registradas com vinculo do cliente a venda denifirá a forma de pagamento
pagamento à vista deverá ser gerado apenas com uma parcela somente para venda
Para pagamentos a prazo, deverá ser gerado uma parcela para cada prestração definida, estando vinculada à venda e status incial "Em Aberto"
*/

// gerador automatico de parcelas
void geradorParcelas();

// consultar as vendas
int consultarVendas();
/*
Consultar com base nos dados da venda e parcela existente. O cliente pode ter mais de uma compra realizada
*/

int main(){

    return 0;
}



void cadastroClientes(){
    Cliente novoCliente;

    // CPF
    printf("\nDigite o CPF: ");
    fgets(novoCliente.CPF, 20, stdin);

    // limpando o \n
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    // validando cpf
    if(validarCPF(novoCliente.CPF) == 1){
        printf("\nCPF valido! Continuando o registro...\n");
    } else {
        printf("\nERRO: CPF invalido! Registro cancelado.\n");
    }

    // Nome
    printf("\nDigite o nome: ");
    fgets(novoCliente.nome, 50, stdin);

    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    // Telefone
    printf("\nDigite o telefone: ");
    fgets(novoCliente.telefone, 15, stdin);

    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';

    if(validarTelefone(novoCliente.telefone) == 1){
        printf("\nTelefone valido! Continuando o registro...\n");
    } else {
        printf("\nERRO: Telefone invalido! Registro cancelado.\n");
    }

    // Data de nascimento
    printf("\nDigite o dia de seu nascimento: ");
    scanf("%d", &novoCliente.dataNascimento.dia);

    printf("\nDigite o dia de seu nascimento: ");
    scanf("%d", &novoCliente.dataNascimento.mes);

    printf("\nDigite o dia de seu nascimento: ");
    scanf("%d", &novoCliente.dataNascimento.ano);

    if(validarData(novoCliente.dataNascimento) == 1){
        printf("\nData valida! Continuando o registro...\n");
    } else {
        printf("\nERRO: Data invalida! Registro cancelado.\n");
    }

    /*
    typedef struct Clientes
        {
        char CPF[20];
        char nome[50];
        char telefone[15];
        data dataNascimento;
        char numeroCartao[20];
        char chavePix[30];
    }Cliente;  
    */

    // Numero de cartao
    printf("\nDigite o numero do cartao: ");
    fgets(novoCliente.numeroCartao, 20, stdin);

    novoCliente.numeroCartao[strcspn(novoCliente.numeroCartao, "\n")] = '\0';

    if(validarTelefone(novoCliente.numeroCartao) == 1){
        printf("\nNumero do cartao valido! Continuando o registro...\n");
    } else {
        printf("\nERRO: Numero do cartao invalido! Registro cancelado.\n");
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
    if (TAM != 11 && TAM != 12) { return 0; }
    if (telefone[0] != '0') { return 0; }

    for (int i=0; i < TAM; i++) {
        if (telefone[i] < '0' || telefone[i] > '9'){
            return 0;
        }
    }
    return 1;  
}

// validando o email
int validarEmail (char email[]) {
    int TAM = strlen(email);
    int psAR = -1,psPonto = -1, qtdAR = 0;     //psAR é a posição do '@' e o psPonto é a posição do '.', o -1 é 'nao encontrado'

    for (int i = 0; i < TAM; i++) {
        if (email[i] == '@') {
            qtdAR++;
            psAR = i;
        }
    }

    if (qtdAR != 1 || psAR < 2) { return 0; }
    for (int i = psAR + 1; i < TAM; i++) {
        if (email[i] == '.') {
        psPonto = i;
        break;
        }
    }

    if (psPonto == -1 || (psPonto - psAR - 1) < 2) { return 0; }
    if ((TAM - 1 - psPonto) < 2) { return 0; }

    return 1;
