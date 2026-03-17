
/* Exercício 1

Enunciado:
Explique a diferença fundamental entre os métodos de tratamento de colisões por encadeamento e por sondagem linear implementados no sistema. Em que situações cada um seria mais adequado?

Resolução:
A diferença fundamental está na forma como cada método armazena elementos que colidem no mesmo índice:

· Encadeamento: Cada posição da tabela contém um ponteiro para o início de uma lista ligada. Quando ocorre colisão, os elementos são adicionados à lista, permitindo múltiplos elementos no mesmo índice.
· Sondagem linear: Cada posição armazena apenas um elemento. Quando ocorre colisão, o sistema procura sequencialmente a próxima posição livre na tabela.

Adequação:

· Encadeamento: Mais adequado quando não se conhece o volume de dados ou quando se espera muitas inserções, pois não há limite de elementos por índice.
· Sondagem linear: Mais adequada quando a tabela tem tamanho bem dimensionado e a memória é limitada, pois não requer ponteiros extras. */
