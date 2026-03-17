Exercício 7
Enunciado:
Proponha uma função calcularMetricas() que calcule e exiba as seguintes métricas para ambas as tabelas:

Número total de estudantes

Número de índices ocupados

Média de elementos por índice (apenas encadeamento)

Índice com mais elementos (apenas encadeamento)

Percentual de ocupação da tabela linear

Resolução:

c
void calcularMetricas() {
    printf("\n========== MÉTRICAS DO SISTEMA ==========\n");
    
    // Variáveis para encadeamento
    int totalEncadeamento = 0;
    int indicesOcupadosEncadeamento = 0;
    int maxElementosPorIndice = 0;
    int indiceMaisCheio = -1;
    int elementosPorIndice[TAM] = {0};
    
    // Variáveis para linear
    int totalLinear = 0;
    int indicesOcupadosLinear = 0;
    
    // ===== Análise da tabela de encadeamento =====
    for(int i = 0; i < TAM; i++) {
        int contador = 0;
        Estudante* temp = tabelaEncadeamento[i];
        
        if(temp != NULL) {
            indicesOcupadosEncadeamento++;
        }
        
        while(temp != NULL) {
            contador++;
            temp = temp->prox;
        }
        
        elementosPorIndice[i] = contador;
        totalEncadeamento += contador;
        
        if(contador > maxElementosPorIndice) {
            maxElementosPorIndice = contador;
            indiceMaisCheio = i;
        }
    }
    
    // ===== Análise da tabela linear =====
    for(int i = 0; i < TAM; i++) {
        if(tabelaLinear[i].numero != -1) {
            totalLinear++;
            indicesOcupadosLinear++;
        }
    }
    
    // ===== Exibição dos resultados =====
    printf("\n--- TABELA DE ENCADEAMENTO ---\n");
    printf("Total de estudantes: %d\n", totalEncadeamento);
    printf("Índices ocupados: %d de %d (%.1f%%)\n", 
           indicesOcupadosEncadeamento, TAM, 
           (float)indicesOcupadosEncadeamento/TAM * 100);
    
    if(totalEncadeamento > 0) {
        printf("Média de elementos por índice ocupado: %.2f\n", 
               (float)totalEncadeamento / indicesOcupadosEncadeamento);
        printf("Índice com mais elementos: %d (%d elementos)\n", 
               indiceMaisCheio, maxElementosPorIndice);
        
        printf("\nDistribuição por índice:\n");
        for(int i = 0; i < TAM; i++) {
            if(elementosPorIndice[i] > 0) {
                printf("  Índice %2d: %d elemento(s)\n", i, elementosPorIndice[i]);
            }
        }
    }
    
    printf("\n--- TABELA DE SONDAGEM LINEAR ---\n");
    printf("Total de estudantes: %d\n", totalLinear);
    printf("Índices ocupados: %d de %d\n", indicesOcupadosLinear, TAM);
    printf("Percentual de ocupação: %.1f%%\n", 
           (float)totalLinear / TAM * 100);
    
    if(totalLinear < TAM) {
        printf("Espaço disponível: %d posições\n", TAM - totalLinear);
    } else {
        printf("⚠️  TABELA LINEAR COMPLETAMENTE CHEIA!\n");
    }
    
    // Comparação entre as duas tabelas
    printf("\n--- COMPARAÇÃO ---\n");
    printf("Encadeamento: %d estudantes | Linear: %d estudantes\n", 
           totalEncadeamento, totalLinear);
    
    if(totalEncadeamento == totalLinear) {
        printf("✅ Tabelas consistentes (mesmo número de elementos)\n");
    } else {
        printf("❌ INCONSISTÊNCIA! Tabelas com número diferente de elementos!\n");
        printf("   Diferença: %d elementos\n", abs(totalEncadeamento - totalLinear));
    }
    
    printf("==========================================\n");
}

// Adicionar ao menu principal
void exibirMenuPrincipal() {
    printf("\n--------------------------------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("--------------------------------------------\n");
    printf("1 - Inserir Estudante\n");
    printf("2 - Procurar Estudante\n");
    printf("3 - Remover Estudante\n");
    printf("4 - Analisar Colisões\n");
    printf("5 - Métricas do Sistema\n");  // Nova opção
    printf("0 - Sair\n");
    printf("--------------------------------------------\n");
}

// Exemplo de saída:
/*
========== MÉTRICAS DO SISTEMA ==========

--- TABELA DE ENCADEAMENTO ---
Total de estudantes: 8
Índices ocupados: 6 de 10 (60.0%)
Média de elementos por índice ocupado: 1.33
Índice com mais elementos: 5 (2 elementos)

Distribuição por índice:
  Índice  0: 1 elemento(s)
  Índice  2: 1 elemento(s)
  Índice  3: 1 elemento(s)
  Índice  4: 1 elemento(s)
  Índice  5: 2 elemento(s)
  Índice  8: 2 elemento(s)

--- TABELA DE SONDAGEM LINEAR ---
Total de estudantes: 8
Índices ocupados: 8 de 10
Percentual de ocupação: 80.0%
Espaço disponível: 2 posições

--- COMPARAÇÃO ---
Encadeamento: 8 estudantes | Linear: 8 estudantes
✅ Tabelas consistentes (mesmo número de elementos)
==========================================
*/
