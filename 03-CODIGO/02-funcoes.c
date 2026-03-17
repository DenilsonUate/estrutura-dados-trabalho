/*
 * SISTEMA DE REGISTO DE ESTUDANTES COM TABELA HASH
 * Elaborado por Denilson - Commit 1
 * Acrescentado por Ludovina - Commit 2 (Validações e Interface)
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
// Protótipos adicionados por Ludovina
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]);
int validarApenasLetras(char str[]);
int validarCampoVazio(char str[]);
void lerString(char destino[], int tamanho, char mensagem[]);
void exibirSubMenu(char titulo[]);

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
    printf("   Elaborado por Denilson (Commit 1)\n");
    printf("   Acrescentado por Ludovina (Commit 2)\n");
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
        tabelaLinear[i].prox = NULL;
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
// Exibir submenu (adicionado por Ludovina)
// ------------------------
// Acrescentado por Ludovina
void exibirSubMenu(char titulo[]) {
    printf("\n--------------------------------------------\n");
    printf("%s\n", titulo);
    printf("--------------------------------------------\n");
    printf("1 - Encadeamento (Lista Locada)\n");
    printf("2 - Sondagem Linear\n");
    printf("0 - Voltar\n");
    printf("--------------------------------------------\n");
    printf("Escolha: ");
}

// ------------------------
// Validar se string contém apenas dígitos
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isdigit(str[i])) {
            return 0;  // Não é dígito
        }
    }
    return 1;  // São apenas dígitos
}

// ------------------------
// Validar se string contém apenas letras e espaços
// ------------------------
// Acrescentado por Ludovina
int validarApenasLetras(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalpha(str[i]) && str[i] != ' ') {
            return 0;  // Não é letra nem espaço
        }
    }
    return 1;  // São apenas letras e espaços
}

// ------------------------
// Validar se campo não está vazio
// ------------------------
// Acrescentado por Ludovina
int validarCampoVazio(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
            return 0;  // Tem caracteres não vazios
        }
    }
    return 1;  // Está vazio
}

// ------------------------
// Ler string com validação simples
// ------------------------
// Acrescentado por Ludovina
void lerString(char destino[], int tamanho, char mensagem[]) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0;  // Remover o \n
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
