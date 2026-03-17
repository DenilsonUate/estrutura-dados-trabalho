Exercício 4
Enunciado:
Implemente uma função calcularFatorCarga() que calcule e retorne o fator de carga atual da tabela de sondagem linear. O fator de carga é dado por: α = (número de elementos inseridos) / (tamanho da tabela). Utilize a função para alertar o usuário quando a tabela atingir 75% de ocupação.

Resolução:

c
float calcularFatorCarga() {
    int elementos = 0;
    
    for(int i = 0; i < TAM; i++) {
        if(tabelaLinear[i].numero != -1) {
            elementos++;
        }
    }
    
    return (float)elementos / TAM;
}

void verificarOcupacao() {
    float fator = calcularFatorCarga();
    
    printf("Fator de carga atual: %.2f\n", fator);
    
    if(fator >= 0.75) {
        printf("⚠️  ATENÇÃO: Tabela linear com %.0f%% de ocupação!\n", fator * 100);
        printf("Recomenda-se aumentar o tamanho da tabela para evitar degradação de desempenho.\n");
    } else {
        printf("✅ Ocupação normal: %.0f%%\n", fator * 100);
    }
}

// Exemplo de uso na main
int main() {
    // ... código existente ...
    
    case 1: // Inserir
        inserirEstudante();
        verificarOcupacao();  // Verifica após cada inserção
        break;
}

