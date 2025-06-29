#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "treino.h"
#include "instrutor.h"

/**
 * Função principal do sistema
 * Carrega dados, exibe menu principal e coordena as operações
 */
int main() {
    // Carrega dados dos arquivos ao iniciar
    carregarAlunos();
    carregarTreinos();

    int op;
    do {
        printf("\n=== Sistema de Treinos ===\n");
        printf("1 - Instrutor\n");
        printf("2 - Aluno\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();  // Consome quebra de linha

        if (op == 1) {
            // Acesso do instrutor
            menuInstrutor();
        } else if (op == 2) {
            // Acesso do aluno
            char nome[50];
            int escolha;

            printf("Nome do aluno: ");
            fgets(nome, 50, stdin);
            nome[strcspn(nome, "\n")] = 0;  // Remove quebra de linha

            Aluno* a = buscarAlunoPorNome(nome);
            if (a) {
                // Menu do aluno autenticado
                do {
                    printf("\n=== Bem-vindo, %s! ===\n", a->nome);
                    printf("1 - Ver treinos\n");
                    printf("2 - Marcar treino como feito\n");
                    printf("0 - Voltar\n");
                    printf("Escolha: ");
                    scanf("%d", &escolha);
                    getchar();  // Consome quebra de linha

                    if (escolha == 1) {
                        listarTreinosDoAluno(a->id);
                    } else if (escolha == 2) {
                        marcarTreinoComoFeito(a->id);
                    }
                } while (escolha != 0);
            } else {
                printf("Aluno '%s' não encontrado!\n", nome);
                printf("Alunos disponíveis:\n");
                listarAlunos();
            }
        }
    } while(op != 0);

    // Salva dados antes de sair
    salvarAlunos();
    salvarTreinos();

    return 0;
}