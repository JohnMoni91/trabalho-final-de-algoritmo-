## 🚀 Status do Projeto: Sistema de Controle Financeiro e Recebimentos (SCFR)

### ✅ O que já está PRONTO (Implementado e Testado)

A base do sistema, todas as lógicas matemáticas e módulos de relatório parcial foram finalizados com sucesso, cumprindo rigorosamente os requisitos do projeto final de Algoritmos 1:

**Estruturas de Dados (Item A):** Definição das *structs* aninhadas para Data, Cliente, Vendas e Parcela.

**Motor de Validações (Item B):** Algoritmos de validação completos operacionais para CPF, Data (com suporte a anos bissextos), Telefone, Cartão de Crédito e E-mail.

**Gestão de Clientes (Itens C e D):** Módulo de cadastro com validação rigorosa pré-armazenamento e sistema de busca (por CPF, Nome ou Telefone) retornando a ficha completa.

**Gestão de Vendas (Itens E e G):** Registro de vendas atrelado a clientes já cadastrados. O sistema define a forma de pagamento e suporta a consulta completa pelo ID da venda ou CPF do cliente.

* **Motor Financeiro (Itens F, H, I, J):**
* Geração automática de parcelas projetando vencimentos e aplicando a taxa base.

* Varredura temporal para identificar atrasos e alterar automaticamente a situação para 'V' (Vencida).

* Função de `quitarParcela()` com cálculo preciso de juros (2% fixos + 0.08% ao dia).

* Função `liquidarDivida()` mapeando compras e abatendo todo o montante de uma vez.

* **Relatórios Gerenciais (Itens K e L):** Funções `relatorioDiario()` e `relatorioMensal()` concluídas. Elas filtram os vetores cruzando as informações para exibir o total vendido, recebido, a receber e pendente em datas específicas.

**Interface e Boas Práticas (###):** Menu principal (switch-case) interligando 100% das opções operacionais , variáveis identificáveis e cabeçalho de autoria adicionado.

**[ ] Dashboard Financeiro (Item M):** Desenvolvido o corpo da função `dashboardFinanceiro()`, com um painel que exibe os valores recebidos, a vencer e previstos de mês a mês, organizado separadamente.

### 🚧 O que AINDA FALTA fazer (To-Do List)
Por enquanto nada uhul.
