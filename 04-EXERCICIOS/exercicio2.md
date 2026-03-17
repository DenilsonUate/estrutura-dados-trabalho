/* Exercício 2

Enunciado:
Considerando a função hash h(k) = k mod 10 utilizada no sistema, determine em quais índices seriam armazenados os números de matrícula: 23, 45, 67, 12, 34, 56, 78, 90, 11 e 22. Simule a inserção na tabela de sondagem linear e indique quantas colisões ocorreram.

Resolução:

Passo 1: Calcular os índices originais

· 23 % 10 = 3
· 45 % 10 = 5
· 67 % 10 = 7
· 12 % 10 = 2
· 34 % 10 = 4
· 56 % 10 = 6
· 78 % 10 = 8
· 90 % 10 = 0
· 11 % 10 = 1
· 22 % 10 = 2 (colisão com 12)

Passo 2: Simular inserção na sondagem linear

Ordem de inserção: 23, 45, 67, 12, 34, 56, 78, 90, 11, 22

Inserção Número Índice Original Índice Final Colisão?
1 23 3 3 Não
2 45 5 5 Não
3 67 7 7 Não
4 12 2 2 Não
5 34 4 4 Não
6 56 6 6 Não
7 78 8 8 Não
8 90 0 0 Não
9 11 1 1 Não
10 22 2 9 Sim (após tentar 2,3,4,5,6,7,8)

Resultado: 1 colisão (número 22)

Tabela final:


Índice 0: 90
Índice 1: 11
Índice 2: 12
Índice 3: 23
Índice 4: 34
Índice 5: 45
Índice 6: 56
Índice 7: 67
Índice 8: 78
Índice 9: 22

*/
