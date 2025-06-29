#ifndef ALUNO_H
#define ALUNO_H

// Estrutura que representa um aluno
typedef struct {
    int id;           // ID único do aluno
    char nome[50];    // Nome do aluno
} Aluno;

// Declaração das funções para manipulação de alunos
Aluno* buscarAlunoPorNome(const char* nome);
Aluno* buscarAlunoPorId(int id);
void listarAlunos();
void carregarAlunos();
void salvarAlunos();
void adicionarAluno();

// Variáveis globais para armazenar alunos
extern Aluno alunos[100];    // Array de alunos (máximo 100)
extern int totalAlunos;      // Contador de alunos cadastrados

#endif