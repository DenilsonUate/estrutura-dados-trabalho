/*
 * SISTEMA DE REGISTO DE ESTUDANTES COM TABELA HASH
 * Elaborado por Denilson - Commit 1
 * Acrescentado por Ludovina - Commit 2 (Validacoes e Interface)
 * Acrescentado por Frederico - Commit 3 (Insercao no Menu)
 * Acrescentado por Denilson - Commit 4 (Insercao Encadeamento)
 * Acrescentado por Ludovina - Commit 5 (Insercao Linear)
 * Acrescentado por Frederico - Commit 6 (Exibicao das Tabelas)
 * Acrescentado por Denilson - Commit 7 (Busca Interativa)
 * Acrescentado por Denilson - Commit 8 (Persistencia em Arquivo)
 * Acrescentado por Frederico - Commit 9 (Remocao Interativa)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10          // Tamanho das tabelas hash
#define MAX_NOME 50     // Tamanho maximo para nome
#define MAX_CURSO 50    // Tamanho maximo para curso
#define MAX_STR 10      // Tamanho para strings de entrada

// Nomes dos arquivos para persistencia
#define ARQ_ENCADEAMENTO "estudantes_encadeamento.txt"
#define ARQ_LINEAR "estudantes_linear.txt"

// ------------------------
// Estrutura do estudante
// ------------------------
// Elaborado por Denilson
typedef struct Estudante {
    int numero;                 // Numero do estudante (matricula)
    char nome[MAX_NOME];        // Nome completo
    char curso[MAX_CURSO];      // Curso
    struct Estudante* prox;     // Ponteiro para proximo (encadeamento)
} Estudante;

// ------------------------
// Tabelas Hash
// ------------------------
// Elaborado por Denilson
Estudante* tabelaEncadeamento[TAM];     // Tabela para encadeamento (lista ligada)
Estudante tabelaLinear[TAM];             // Tabela para sondagem linear (vetor)

// ------------------------
// Prototipos das funcoes
// ------------------------
// Elaborado por Denilson
void inicializarTabelas();
int funcaoHash(int numero);
void exibirMenuPrincipal();
void limparBuffer();
void pausar();

// ------------------------
// Prototipos adicionados por Ludovina
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]);
int validarApenasLetras(char str[]);
int validarCampoVazio(char str[]);
void lerString(char destino[], int tamanho, char mensagem[]);
void exibirSubMenu(char titulo[]);

// ------------------------
// Prototipos adicionados por Frederico
// ------------------------
// Acrescentado por Frederico
void inserirEstudante();
void lerDadosEstudante(int *numero, char nome[], char curso[]);

// ------------------------
// Prototipos adicionados por Denilson
// ------------------------
// Acrescentado por Denilson
void inserirEncadeamento(int numero, char nome[], char curso[]);
void exibirMensagemColisaoEncadeamento(int indice);

// ------------------------
// Prototipos adicionados por Ludovina (Commit 5)
// ------------------------
// Acrescentado por Ludovina
void inserirLinear(int numero, char nome[], char curso[]);
void exibirMensagemColisaoLinear(int indiceOcupado, int proximoIndice);

// ------------------------
// Prototipos adicionados por Frederico (Commit 6)
// ------------------------
// Acrescentado por Frederico
void exibirTabelaEncadeamento();
void exibirTabelaLinear();
void exibirTodasTabelas();
void desenharLinha(int tamanho);

// ------------------------
// Prototipos adicionados por Denilson (Commit 7)
// ------------------------
// Acrescentado por Denilson
void menuProcurar();
void procurarEncadeamento();
void procurarLinear();
void listarAlunosIndiceEncadeamento(int indice);
void mostrarAlunoIndiceLinear(int indice);

// ------------------------
// Prototipos adicionados por Denilson (Commit 8)
// ------------------------
// Acrescentado por Denilson
void salvarEncadeamento();
void salvarLinear();
void carregarEncadeamento();
void carregarLinear();
void salvarTodasTabelas();
void carregarTodasTabelas();

// ------------------------
// Prototipos adicionados por Frederico (Commit 9)
// ------------------------
// Acrescentado por Frederico
void menuRemover();
void removerEncadeamento();
void removerLinear();
int escolherAlunoIndiceEncadeamento(int indice);
void removerAlunoEncadeamento(int indice, int posicao);

// ------------------------
// Funcao main - Menu principal
// ------------------------
// Elaborado por Denilson
int main() {
    int opcao;
    
    // Inicializar as tabelas
    inicializarTabelas();
    
    // Carregar dados dos arquivos
    carregarTodasTabelas();
    
    printf("\n============================================\n");
    printf("   SISTEMA DE REGISTO DE ESTUDANTES\n");
    printf("   Com Tabela Hash (Encadeamento e Linear)\n");
    printf("============================================\n");
    printf("   Elaborado por Denilson (Commit 1)\n");
    printf("   Acrescentado por Ludovina (Commit 2)\n");
    printf("   Acrescentado por Frederico (Commit 3)\n");
    printf("   Acrescentado por Denilson (Commit 4)\n");
    printf("   Acrescentado por Ludovina (Commit 5)\n");
    printf("   Acrescentado por Frederico (Commit 6)\n");
    printf("   Acrescentado por Denilson (Commit 7)\n");
    printf("   Acrescentado por Denilson (Commit 8)\n");
    printf("   Acrescentado por Frederico (Commit 9)\n");
    printf("============================================\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n--- INSERIR ESTUDANTE ---\n");
                inserirEstudante();
                salvarTodasTabelas();
                break;
                
            case 2:
                menuProcurar();
                break;
                
            case 3:
                menuRemover();
                salvarTodasTabelas();  // Salvar apos remocao
                break;
                
            case 0:
                printf("\nSaindo do sistema...\n");
                printf("Salvando dados...\n");
                salvarTodasTabelas();
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
// Menu de remocao de estudante
// ------------------------
// Acrescentado por Frederico
void menuRemover() {
    int opcao;
    
    do {
        exibirSubMenu("REMOVER ESTUDANTE");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n--- Remocao por Encadeamento ---\n");
                removerEncadeamento();
                pausar();
                break;
                
            case 2:
                printf("\n--- Remocao por Sondagem Linear ---\n");
                removerLinear();
                pausar();
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while(opcao != 0);
}

// ------------------------
// Remover estudante da tabela de encadeamento
// ------------------------
// Acrescentado por Frederico
void removerEncadeamento() {
    int indice;
    char indiceStr[MAX_STR];
    
    // Mostrar tabela atual
    exibirTabelaEncadeamento();
    
    // Pedir indice para remocao
    printf("\n--- Remocao por Encadeamento ---\n");
    printf("Digite o indice que deseja remover (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    // Verificar se ha alunos no indice
    if(tabelaEncadeamento[indice] == NULL) {
        printf("Nenhum aluno encontrado no indice %d.\n", indice);
        return;
    }
    
    // Escolher qual aluno remover
    int posicao = escolherAlunoIndiceEncadeamento(indice);
    
    if(posicao > 0) {
        removerAlunoEncadeamento(indice, posicao);
        printf("Aluno removido com sucesso do indice %d!\n", indice);
    }
}

// ------------------------
// Escolher qual aluno remover de um indice no encadeamento
// Retorna a posicao escolhida (1-based) ou 0 se cancelar
// ------------------------
// Acrescentado por Frederico
int escolherAlunoIndiceEncadeamento(int indice) {
    Estudante* temp = tabelaEncadeamento[indice];
    int total = 0;
    char escolhaStr[MAX_STR];
    int escolha;
    
    // Contar total de alunos
    while(temp != NULL) {
        total++;
        temp = temp->prox;
    }
    
    printf("\n--- Alunos no indice %d ---\n", indice);
    printf("Total de alunos: %d\n", total);
    desenharLinha(50);
    
    // Listar alunos em ordem numerica
    temp = tabelaEncadeamento[indice];
    for(int i = 1; i <= total; i++) {
        printf("%d. Numero: %d\n", i, temp->numero);
        printf("   Nome: %s\n", temp->nome);
        printf("   Curso: %s\n", temp->curso);
        desenharLinha(30);
        temp = temp->prox;
    }
    
    // Pedir escolha
    printf("Escolha o numero do aluno que deseja remover (1 a %d, 0 para cancelar): ", total);
    
    do {
        lerString(escolhaStr, MAX_STR, "");
        if(!validarApenasDigitos(escolhaStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(escolhaStr));
    
    escolha = atoi(escolhaStr);
    
    if(escolha == 0) {
        printf("Operacao cancelada.\n");
        return 0;
    }
    
    if(escolha < 1 || escolha > total) {
        printf("Escolha invalida! Deve ser entre 1 e %d.\n", total);
        return 0;
    }
    
    return escolha;
}

// ------------------------
// Remover aluno de uma posicao especifica no encadeamento
// ------------------------
// Acrescentado por Frederico
void removerAlunoEncadeamento(int indice, int posicao) {
    Estudante* temp = tabelaEncadeamento[indice];
    Estudante* ant = NULL;
    
    // Caso especial: remover o primeiro
    if(posicao == 1) {
        tabelaEncadeamento[indice] = temp->prox;
        free(temp);
        return;
    }
    
    // Procurar a posicao
    for(int i = 1; i < posicao; i++) {
        ant = temp;
        temp = temp->prox;
    }
    
    // Remover o aluno
    if(ant != NULL) {
        ant->prox = temp->prox;
        free(temp);
    }
}

// ------------------------
// Remover estudante da tabela de sondagem linear
// ------------------------
// Acrescentado por Frederico
void removerLinear() {
    int indice;
    char indiceStr[MAX_STR];
    char confirmacao;
    
    // Mostrar tabela atual
    exibirTabelaLinear();
    
    // Pedir indice para remocao
    printf("\n--- Remocao por Sondagem Linear ---\n");
    printf("Digite o indice que deseja remover (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    // Verificar se ha aluno no indice
    if(tabelaLinear[indice].numero == -1) {
        printf("Nenhum aluno encontrado no indice %d.\n", indice);
        return;
    }
    
    // Mostrar aluno que sera removido
    printf("\nAluno encontrado no indice %d:\n", indice);
    printf("  Numero: %d\n", tabelaLinear[indice].numero);
    printf("  Nome: %s\n", tabelaLinear[indice].nome);
    printf("  Curso: %s\n", tabelaLinear[indice].curso);
    
    // Confirmar remocao
    printf("\nTem certeza que deseja remover este aluno? (s/n): ");
    scanf("%c", &confirmacao);
    limparBuffer();
    
    if(confirmacao == 's' || confirmacao == 'S') {
        // Remover aluno
        tabelaLinear[indice].numero = -1;
        strcpy(tabelaLinear[indice].nome, "");
        strcpy(tabelaLinear[indice].curso, "");
        
        printf("Aluno removido com sucesso do indice %d!\n", indice);
    } else {
        printf("Operacao cancelada.\n");
    }
}

// ------------------------
// Menu de procura de estudante
// ------------------------
// Acrescentado por Denilson
void menuProcurar() {
    int opcao;
    
    do {
        exibirSubMenu("PROCURAR ESTUDANTE");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n--- Busca por Encadeamento ---\n");
                procurarEncadeamento();
                pausar();
                break;
                
            case 2:
                printf("\n--- Busca por Sondagem Linear ---\n");
                procurarLinear();
                pausar();
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while(opcao != 0);
}

// ------------------------
// Procurar estudante na tabela de encadeamento
// ------------------------
// Acrescentado por Denilson
void procurarEncadeamento() {
    int indice;
    char indiceStr[MAX_STR];
    
    // Mostrar tabela atual
    exibirTabelaEncadeamento();
    
    // Pedir indice para busca
    printf("\n--- Busca por Encadeamento ---\n");
    printf("Digite o indice que deseja consultar (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    // Listar alunos do indice escolhido
    listarAlunosIndiceEncadeamento(indice);
}

// ------------------------
// Listar todos os alunos de um indice na tabela de encadeamento
// ------------------------
// Acrescentado por Denilson
void listarAlunosIndiceEncadeamento(int indice) {
    printf("\n--- Alunos no indice %d (Encadeamento) ---\n", indice);
    
    if(tabelaEncadeamento[indice] == NULL) {
        printf("Nenhum aluno encontrado neste indice.\n");
        return;
    }
    
    Estudante* temp = tabelaEncadeamento[indice];
    int cont = 1;
    
    printf("Total de alunos neste indice: (lista locada)\n");
    desenharLinha(50);
    
    while(temp != NULL) {
        printf("Aluno %d:\n", cont);
        printf("  Numero: %d\n", temp->numero);
        printf("  Nome: %s\n", temp->nome);
        printf("  Curso: %s\n", temp->curso);
        desenharLinha(30);
        
        temp = temp->prox;
        cont++;
    }
}

// ------------------------
// Procurar estudante na tabela de sondagem linear
// ------------------------
// Acrescentado por Denilson
void procurarLinear() {
    int indice;
    char indiceStr[MAX_STR];
    
    // Mostrar tabela atual
    exibirTabelaLinear();
    
    // Pedir indice para busca
    printf("\n--- Busca por Sondagem Linear ---\n");
    printf("Digite o indice que deseja consultar (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    // Mostrar aluno do indice escolhido
    mostrarAlunoIndiceLinear(indice);
}

// ------------------------
// Mostrar aluno de um indice na tabela linear
// ------------------------
// Acrescentado por Denilson
void mostrarAlunoIndiceLinear(int indice) {
    printf("\n--- Aluno no indice %d (Sondagem Linear) ---\n", indice);
    
    if(tabelaLinear[indice].numero == -1) {
        printf("Nenhum aluno encontrado neste indice.\n");
        return;
    }
    
    printf("Numero: %d\n", tabelaLinear[indice].numero);
    printf("Nome: %s\n", tabelaLinear[indice].nome);
    printf("Curso: %s\n", tabelaLinear[indice].curso);
    
    // Verificar se houve colisao (indice diferente do calculado)
    int indiceOriginal = funcaoHash(tabelaLinear[indice].numero);
    if(indiceOriginal != indice) {
        printf("\n(Observacao: Este aluno sofreu colisao na insercao.\n");
        printf("Indice original calculado: %d\n", indiceOriginal);
        printf("Indice real apos sondagem: %d)\n", indice);
    }
}

// ------------------------
// Inserir estudante (sem escolha de metodo)
// ------------------------
// Acrescentado por Frederico (modificado por Ludovina)
void inserirEstudante() {
    int numero;
    char nome[MAX_NOME];
    char curso[MAX_CURSO];
    
    // Ler dados do estudante
    lerDadosEstudante(&numero, nome, curso);
    
    // Inserir automaticamente nas duas tabelas
    printf("\n--- Inserindo nas tabelas ---\n");
    inserirEncadeamento(numero, nome, curso);
    inserirLinear(numero, nome, curso);
    
    // Mostrar como ficaram as tabelas apos insercao
    printf("\n--- Estado atual das tabelas ---\n");
    exibirTodasTabelas();
    
    pausar();
}

// ------------------------
// Inserir estudante na tabela de encadeamento
// ------------------------
// Acrescentado por Denilson
void inserirEncadeamento(int numero, char nome[], char curso[]) {
    int indice = funcaoHash(numero);
    Estudante* novo = (Estudante*)malloc(sizeof(Estudante));
    
    // Preencher dados do novo estudante
    novo->numero = numero;
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    
    printf("\n[ENCADEAMENTO] Numero: %d\n", numero);
    printf("Indice calculado: %d\n", indice);
    
    // Verificar se o indice esta vazio
    if(tabelaEncadeamento[indice] == NULL) {
        // Indice vazio - insercao direta
        tabelaEncadeamento[indice] = novo;
        printf("Indice %d: vazio - inserido com sucesso!\n", indice);
    } else {
        // Indice ocupado - tratar colisao com lista locada
        exibirMensagemColisaoEncadeamento(indice);
        
        Estudante* temp = tabelaEncadeamento[indice];
        while(temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
        
        printf("Estudante alocado no final da lista do indice %d.\n", indice);
    }
}

// ------------------------
// Exibir mensagem de colisao para encadeamento
// ------------------------
// Acrescentado por Denilson
void exibirMensagemColisaoEncadeamento(int indice) {
    printf("\n!!! COLISAO DETECTADA !!!\n");
    printf("Indice %d ja esta ocupado.\n", indice);
    printf("Como e uma tabela com encadeamento (lista locada),\n");
    printf("o estudante sera alocado no final da lista existente.\n");
    printf("----------------------------------------\n");
}

// ------------------------
// Inserir estudante na tabela de sondagem linear
// ------------------------
// Acrescentado por Ludovina
void inserirLinear(int numero, char nome[], char curso[]) {
    int indiceOriginal = funcaoHash(numero);
    int indice = indiceOriginal;
    int tentativas = 0;
    
    printf("\n[LINEAR] Numero: %d\n", numero);
    printf("Indice calculado: %d\n", indiceOriginal);
    
    // Procurar posicao vazia (sondagem linear)
    while(tabelaLinear[indice].numero != -1 && tentativas < TAM) {
        tentativas++;
        exibirMensagemColisaoLinear(indice, (indice + 1) % TAM);
        indice = (indice + 1) % TAM;
        
        if(indice == indiceOriginal) {
            printf("\n!!! TABELA CHEIA !!!\n");
            printf("Nao foi possivel inserir o estudante na tabela linear.\n");
            return;
        }
    }
    
    // Inserir na posicao encontrada
    tabelaLinear[indice].numero = numero;
    strcpy(tabelaLinear[indice].nome, nome);
    strcpy(tabelaLinear[indice].curso, curso);
    tabelaLinear[indice].prox = NULL;
    
    if(indice == indiceOriginal) {
        printf("Indice %d: vazio - inserido com sucesso!\n", indice);
    } else {
        printf("Estudante inserido no indice %d (apos sondagem).\n", indice);
    }
}

// ------------------------
// Exibir mensagem de colisao para sondagem linear
// ------------------------
// Acrescentado por Ludovina
void exibirMensagemColisaoLinear(int indiceOcupado, int proximoIndice) {
    printf("\n!!! COLISAO DETECTADA !!!\n");
    printf("Indice %d ocupado, apliquei no indice %d (sondagem linear).\n", 
           indiceOcupado, proximoIndice);
    printf("----------------------------------------\n");
}

// ------------------------
// Exibir tabela de encadeamento
// ------------------------
// Acrescentado por Frederico
void exibirTabelaEncadeamento() {
    printf("\n=== TABELA HASH - ENCADEAMENTO ===\n");
    printf("Indice | Status | Alunos\n");
    desenharLinha(40);
    
    for(int i = 0; i < TAM; i++) {
        printf("%3d    | ", i);
        
        if(tabelaEncadeamento[i] == NULL) {
            printf("Vazio   | (nenhum aluno)\n");
        } else {
            printf("Ocupado | ");
            Estudante* temp = tabelaEncadeamento[i];
            int cont = 1;
            
            while(temp != NULL) {
                if(cont > 1) printf("         |         ");
                printf("%d: %s (%s)\n", temp->numero, temp->nome, temp->curso);
                temp = temp->prox;
                cont++;
            }
        }
        desenharLinha(40);
    }
}

// ------------------------
// Exibir tabela de sondagem linear
// ------------------------
// Acrescentado por Frederico
void exibirTabelaLinear() {
    printf("\n=== TABELA HASH - SONDAGEM LINEAR ===\n");
    printf("Indice | Status   | Aluno\n");
    desenharLinha(40);
    
    for(int i = 0; i < TAM; i++) {
        printf("%3d    | ", i);
        
        if(tabelaLinear[i].numero == -1) {
            printf("Vazio     | (nenhum aluno)\n");
        } else {
            printf("Ocupado   | %d: %s (%s)\n", 
                   tabelaLinear[i].numero, 
                   tabelaLinear[i].nome, 
                   tabelaLinear[i].curso);
        }
        desenharLinha(40);
    }
}

// ------------------------
// Exibir todas as tabelas
// ------------------------
// Acrescentado por Frederico
void exibirTodasTabelas() {
    exibirTabelaEncadeamento();
    exibirTabelaLinear();
}

// ------------------------
// Desenhar linha separadora
// ------------------------
// Acrescentado por Frederico
void desenharLinha(int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("-");
    }
    printf("\n");
}

// ------------------------
// Salvar tabela de encadeamento em arquivo
// ------------------------
// Acrescentado por Denilson
void salvarEncadeamento() {
    FILE *arquivo = fopen(ARQ_ENCADEAMENTO, "w");
    
    if(arquivo == NULL) {
        printf("Erro ao criar arquivo %s\n", ARQ_ENCADEAMENTO);
        return;
    }
    
    fprintf(arquivo, "# Tabela Hash - Encadeamento\n");
    fprintf(arquivo, "# Formato: indice:numero:nome:curso\n\n");
    
    for(int i = 0; i < TAM; i++) {
        if(tabelaEncadeamento[i] != NULL) {
            Estudante* temp = tabelaEncadeamento[i];
            while(temp != NULL) {
                fprintf(arquivo, "%d:%d:%s:%s\n", 
                        i, temp->numero, temp->nome, temp->curso);
                temp = temp->prox;
            }
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Salvar tabela linear em arquivo
// ------------------------
// Acrescentado por Denilson
void salvarLinear() {
    FILE *arquivo = fopen(ARQ_LINEAR, "w");
    
    if(arquivo == NULL) {
        printf("Erro ao criar arquivo %s\n", ARQ_LINEAR);
        return;
    }
    
    fprintf(arquivo, "# Tabela Hash - Sondagem Linear\n");
    fprintf(arquivo, "# Formato: indice:numero:nome:curso\n\n");
    
    for(int i = 0; i < TAM; i++) {
        if(tabelaLinear[i].numero != -1) {
            fprintf(arquivo, "%d:%d:%s:%s\n", 
                    i, tabelaLinear[i].numero, 
                    tabelaLinear[i].nome, tabelaLinear[i].curso);
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Salvar todas as tabelas
// ------------------------
// Acrescentado por Denilson
void salvarTodasTabelas() {
    salvarEncadeamento();
    salvarLinear();
}

// ------------------------
// Carregar tabela de encadeamento do arquivo
// ------------------------
// Acrescentado por Denilson
void carregarEncadeamento() {
    FILE *arquivo = fopen(ARQ_ENCADEAMENTO, "r");
    
    if(arquivo == NULL) {
        return;
    }
    
    char linha[200];
    int indice, numero;
    char nome[MAX_NOME], curso[MAX_CURSO];
    
    while(fgets(linha, sizeof(linha), arquivo)) {
        if(linha[0] == '#') continue;
        
        if(sscanf(linha, "%d:%d:%[^:]:%[^\n]", &indice, &numero, nome, curso) == 4) {
            Estudante* novo = (Estudante*)malloc(sizeof(Estudante));
            novo->numero = numero;
            strcpy(novo->nome, nome);
            strcpy(novo->curso, curso);
            novo->prox = NULL;
            
            if(tabelaEncadeamento[indice] == NULL) {
                tabelaEncadeamento[indice] = novo;
            } else {
                Estudante* temp = tabelaEncadeamento[indice];
                while(temp->prox != NULL) {
                    temp = temp->prox;
                }
                temp->prox = novo;
            }
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Carregar tabela linear do arquivo
// ------------------------
// Acrescentado por Denilson
void carregarLinear() {
    FILE *arquivo = fopen(ARQ_LINEAR, "r");
    
    if(arquivo == NULL) {
        return;
    }
    
    char linha[200];
    int indice, numero;
    char nome[MAX_NOME], curso[MAX_CURSO];
    
    while(fgets(linha, sizeof(linha), arquivo)) {
        if(linha[0] == '#') continue;
        
        if(sscanf(linha, "%d:%d:%[^:]:%[^\n]", &indice, &numero, nome, curso) == 4) {
            tabelaLinear[indice].numero = numero;
            strcpy(tabelaLinear[indice].nome, nome);
            strcpy(tabelaLinear[indice].curso, curso);
            tabelaLinear[indice].prox = NULL;
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Carregar todas as tabelas
// ------------------------
// Acrescentado por Denilson
void carregarTodasTabelas() {
    carregarEncadeamento();
    carregarLinear();
}

// ------------------------
// Ler dados do estudante com validacoes
// ------------------------
// Acrescentado por Frederico
void lerDadosEstudante(int *numero, char nome[], char curso[]) {
    char numStr[MAX_STR];
    int valido;
    
    printf("\n--- Dados do Estudante ---\n");
    
    // Ler numero (apenas digitos)
    do {
        lerString(numStr, MAX_STR, "Numero do estudante (apenas digitos): ");
        valido = 1;
        
        if(validarCampoVazio(numStr)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarApenasDigitos(numStr)) {
            printf("Erro: Apenas numeros sao permitidos!\n");
            valido = 0;
        }
        
    } while(!valido);
    
    *numero = atoi(numStr);
    
    // Ler nome (apenas letras e espacos)
    do {
        lerString(nome, MAX_NOME, "Nome do estudante (apenas letras): ");
        valido = 1;
        
        if(validarCampoVazio(nome)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarApenasLetras(nome)) {
            printf("Erro: Apenas letras e espacos sao permitidos!\n");
            valido = 0;
        }
        
    } while(!valido);
    
    // Ler curso (apenas letras e espacos)
    do {
        lerString(curso, MAX_CURSO, "Curso do estudante (apenas letras): ");
        valido = 1;
        
        if(validarCampoVazio(curso)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarApenasLetras(curso)) {
            printf("Erro: Apenas letras e espacos sao permitidos!\n");
            valido = 0;
        }
        
    } while(!valido);
    
    printf("\nDados validados com sucesso!\n");
}

// ------------------------
// Inicializar as tabelas hash
// ------------------------
// Elaborado por Denilson
void inicializarTabelas() {
    for(int i = 0; i < TAM; i++) {
        tabelaEncadeamento[i] = NULL;
        tabelaLinear[i].numero = -1;
        strcpy(tabelaLinear[i].nome, "");
        strcpy(tabelaLinear[i].curso, "");
        tabelaLinear[i].prox = NULL;
    }
}

// ------------------------
// Funcao hash (resto da divisao)
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
// Validar se string contem apenas digitos
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Validar se string contem apenas letras e espacos
// ------------------------
// Acrescentado por Ludovina
int validarApenasLetras(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Validar se campo nao esta vazio
// ------------------------
// Acrescentado por Ludovina
int validarCampoVazio(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Ler string com validacao simples
// ------------------------
// Acrescentado por Ludovina
void lerString(char destino[], int tamanho, char mensagem[]) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0;
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
// Pausar execucao
// ------------------------
// Elaborado por Denilson
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}
