#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    //return 0;
//}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
/*
 * Programa: Sistema de Inventário - Mochila de Loot
 * Disciplina: Programação em C
 * Descrição: Gerencia até 10 itens com cadastro, remoção, listagem e busca sequencial.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Capacidade máxima da mochila
#define MAX_ITENS 10

// Protótipos das funções
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void limparBuffer();

// Função principal com menu interativo
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    printf("=== SISTEMA DE INVENTARIO - MOCHILA DE LOOT ===\n\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("Saindo do sistema... Mochila fechada!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função: Insere um novo item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("ERRO: Mochila cheia! Remova itens antes de adicionar.\n");
        return;
    }

    printf("\n--- CADASTRO DE ITEM ---\n");
    Item novo;

    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';  // Remove \n

    printf("Tipo (ex: arma, municao, cura): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    do {
        printf("Quantidade: ");
        scanf("%d", &novo.quantidade);
        limparBuffer();
        if (novo.quantidade <= 0) {
            printf("Quantidade deve ser maior que zero!\n");
        }
    } while (novo.quantidade <= 0);

    // Adiciona na próxima posição livre
    mochila[*total] = novo;
    (*total)++;

    printf("Item cadastrado com sucesso!\n");
    listarItens(mochila, *total);
}

// Função: Remove um item pelo nome
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("Mochila vazia! Nada para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- REMOCAO DE ITEM ---\n");
    printf("Nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            // Remove deslocando os itens seguintes
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }

    listarItens(mochila, *total);
}

// Função: Lista todos os itens da mochila
void listarItens(Item mochila[], int total) {
    printf("\n=== ITENS NA MOCHILA (%d/%d) ===\n", total, MAX_ITENS);
    if (total == 0) {
        printf("  [VAZIA]\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("  %d. [%s] %s - Qtd: %d\n",
                   i + 1, mochila[i].tipo, mochila[i].nome, mochila[i].quantidade);
        }
    }
}

// Função: Busca sequencial por nome
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("Mochila vazia! Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- BUSCA DE ITEM ---\n");
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nITEM ENCONTRADO:\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado.\n", nomeBusca);
    }
}

// Função: Limpa o buffer do teclado (evita problemas com fgets + scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}