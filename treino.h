#ifndef TREINO_H
#define TREINO_H

// Estrutura que representa um treino na fila circular
typedef struct Treino {
    int alunoId;                    // ID do aluno dono do treino
    char grupo_muscular[50];        // Nome do grupo muscular
    int execucoes_restantes;        // Quantas vezes ainda deve ser executado
    int execucoes_totais;           // Total de execuções definido pelo instrutor
    struct Treino* prox;            // Ponteiro para o próximo treino na fila
} Treino;

// Declaração das funções para manipulação de treinos
void adicionarGrupoDeTreinos();
void listarTreinosDoAluno(int alunoId);
void marcarTreinoComoFeito(int alunoId);
void carregarTreinos();
void salvarTreinos();

// Array de ponteiros - uma fila circular para cada aluno (índice = ID do aluno)
extern Treino* filaTreinos[100];

#endif