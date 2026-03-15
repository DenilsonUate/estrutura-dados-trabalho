/*
 * SISTEMA DE REGISTO DE ESTUDANTES COM TABELA HASH
 * Elaborado por Denilson
 * 
 * Este é o commit inicial que estabelece a estrutura base do sistema
 * com as duas tabelas hash (encadeamento e sondagem linear)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10          // Tamanho das tabelas hash
#define MAX_NOME 50     // Tamanho máximo para nome
#define MAX_CURSO 50    // Tamanho máximo para curso
#define MAX_STR 10      // Tamanho para strings de entrada

// ------------------------
// Estrutura do estudante
// ------------------------
// Elaborado por Denilson
typedef struct Estudante {
    int numero;                 // Número do estudante (matrícula)
    char nome[MAX_NOME];        // Nome completo
    char curso[MAX_CURSO];      // Curso
    struct Estudante* prox;     // Ponteiro para próximo (encadeamento)
} Estudante;

// ------------------------
// Tabelas Hash
// ------------------------
// Elaborado por Denilson
Estudante* tabelaEncadeamento[TAM];     // Tabela para encadeamento (lista ligada)
Estudante tabelaLinear[TAM];             // Tabela para sondagem linear (vetor)

// ------------------------
// Protótipos das funções
// ------------------------
// Elaborado por Denilson
void inicializarTabelas();
int funcaoHash(int numero);
void exibirMenuPrincipal();
void limparBuffer();
void pausar();

// ------------------------
// Função main - Menu principal
// ------------------------
// Elaborado por Denilson
int main() {
    int opcao;
    
    // Inicializar as tabelas
    inicializarTabelas();
    
    printf("\n============================================\n");
    printf("   SISTEMA DE REGISTO DE ESTUDANTES\n");
    printf("   Com Tabela Hash (Encadeamento e Linear)\n");
    printf("============================================\n");
    printf("   Elaborado por Denilson - Commit 1\n");
    printf("============================================\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n--- INSERIR ESTUDANTE ---\n");
                printf("Funcionalidade em desenvolvimento...\n");
                pausar();
                break;
                
            case 2:
                printf("\n--- PROCURAR ESTUDANTE ---\n");
                printf("Funcionalidade em desenvolvimento...\n");
                pausar();
                break;
                
            case 3:
                printf("\n--- REMOVER ESTUDANTE ---\n");
                printf("Funcionalidade em desenvolvimento...\n");
                pausar();
                break;
                
            case 0:
                printf("\nSaindo do sistema...\n");
                printf("Obrigado por utilizar!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
        
    } while(opcao != 0);
    
    return 0;
}

// ------------------------
// Inicializar as tabelas hash
// ------------------------
// Elaborado por Denilson
void inicializarTabelas() {
    // Inicializar tabela de encadeamento (todos ponteiros NULL)
    for(int i = 0; i < TAM; i++) {
        tabelaEncadeamento[i] = NULL;
    }
    
    // Inicializar tabela de sondagem linear (numero = -1 indica vazio)
    for(int i = 0; i < TAM; i++) {
        tabelaLinear[i].numero = -1;
        strcpy(tabelaLinear[i].nome, "");
        strcpy(tabelaLinear[i].curso, "");
        tabelaLinear[i].prox = NULL;  // Não usado na linear, mas por segurança
    }
    
    printf("Tabelas hash inicializadas com sucesso!\n");
}

// ------------------------
// Função hash (resto da divisão)
// ------------------------
// Elaborado por Denilson
int funcaoHash(int numero) {
    return numero % TAM;
}

// ------------------------
// Exibir menu principal
// ------------------------
// Elaborado por Denilson
void exibirMenuPrincipal() {
    printf("\n--------------------------------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("--------------------------------------------\n");
    printf("1 - Inserir Estudante\n");
    printf("2 - Procurar Estudante\n");
    printf("3 - Remover Estudante\n");
    printf("0 - Sair\n");
    printf("--------------------------------------------\n");
}

// ------------------------
// Limpar buffer do teclado
// ------------------------
// Elaborado por Denilson
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// ------------------------
// Pausar execução
// ------------------------
// Elaborado por Denilson
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}
