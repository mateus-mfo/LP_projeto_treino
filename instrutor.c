#include <stdio.h>
#include "aluno.h"
#include "treino.h"

/**
 * Menu principal do instrutor
 * Permite cadastrar alunos, listar alunos e adicionar treinos
 */
void menuInstrutor() {
    int op;
    do {
        printf("\n=== Menu Instrutor ===\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("3 - Adicionar grupo de treinos\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();  // Consome quebra de linha

        switch(op) {
            case 1:
                adicionarAluno();
            break;
            case 2:
                listarAlunos();
            break;
            case 3:
                adicionarGrupoDeTreinos();
            break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(op != 0);
}