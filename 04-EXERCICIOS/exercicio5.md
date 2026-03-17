Exercício 5
Enunciado:
Escreva uma função reorganizarTabelaLinear() que percorra a tabela de sondagem linear e identifique elementos que não estão no seu índice original (sofreram colisão). A função deve exibir uma lista desses elementos e seus índices originais.

Resolução:

c
void reorganizarTabelaLinear() {
    printf("\n=== ANÁLISE DE COLISÕES (Sondagem Linear) ===\n");
    int colisoes = 0;
    
    for(int i = 0; i < TAM; i++) {
        if(tabelaLinear[i].numero != -1) {
            int indiceOriginal = funcaoHash(tabelaLinear[i].numero);
            
            if(indiceOriginal != i) {
                colisoes++;
                printf("Elemento no índice %d:\n", i);
                printf("  Número: %s\n", tabelaLinear[i].numeroStr);
                printf("  Nome: %s\n", tabelaLinear[i].nome);
                printf("  Índice original calculado: %d\n", indiceOriginal);
                printf("  Deslocamento: %d posições\n", 
                       (i - indiceOriginal + TAM) % TAM);
                printf("---\n");
            }
        }
    }
    
    if(colisoes == 0) {
        printf("Nenhuma colisão detectada na tabela linear.\n");
    } else {
        printf("Total de elementos com colisão: %d\n", colisoes);
        printf("Percentual de colisões: %.1f%%\n", 
               (float)colisoes / TAM * 100);
    }
}

// Adicionar ao menu principal
void exibirMenuPrincipal() {
    printf("\n--------------------------------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("--------------------------------------------\n");
    printf("1 - Inserir Estudante\n");
    printf("2 - Procurar Estudante\n");
    printf("3 - Remover Estudante\n");
    printf("4 - Analisar Colisões\n");  // Nova opção
    printf("0 - Sair\n");
    printf("--------------------------------------------\n");
}

// No switch da main
case 4:
    printf("\n--- ANÁLISE DE COLISÕES ---\n");
    reorganizarTabelaLinear();
    pausar();
    break;
