#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tamanho máximo do inventário
#define MAX_ITENS 10 

/**
 * @brief Definição da struct Item.
 * * Esta estrutura armazena as informações essenciais de cada objeto coletado 
 * (loot) na mochila virtual do jogador.
 */
typedef struct {
    char nome[30];
    char tipo[20]; // Ex: arma, munição, cura, ferramenta
    int quantidade;
} Item;

// Variáveis Globais para o Inventário
Item inventario[MAX_ITENS];
int contadorItens = 0; // Controla o número atual de itens na mochila

/**
 * @brief Exibe o menu principal de operações.
 * * Garante uma interface clara e orientativa para o jogador.
 */
void exibirMenu() {
    printf("\n--- 🎒 Inventário Inicial (Mochila) ---\n");
    printf("1. Cadastrar Novo Item (Coletar Loot)\n");
    printf("2. Remover Item (Descartar Loot)\n");
    printf("3. Buscar Item por Nome\n");
    printf("4. Sair do Jogo\n");
    printf("---------------------------------------\n");
    printf("Itens na Mochila: %d/%d\n", contadorItens, MAX_ITENS);
    printf("Escolha uma opção: ");
}

/**
 * @brief Lista todos os itens atualmente registrados na mochila.
 * * Deve ser chamada após cada operação para manter o jogador informado.
 */
void listarItens() {
    printf("\n--- 📜 Itens Atuais na Mochila ---\n");

    if (contadorItens == 0) {
        printf("A mochila está vazia. Colete alguns itens!\n");
        printf("---------------------------------------\n");
        return;
    }

    // Percorre o vetor de structs e exibe os dados de cada item
    for (int i = 0; i < contadorItens; i++) {
        printf("  [%d] Nome: %s, Tipo: %s, Quantidade: %d\n", 
               i + 1, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
    printf("-----------------------------------\n");
}

/**
 * @brief Função obrigatória para inserir um novo item na mochila.
 * * Verifica se há espaço disponível (capacidade máxima de 10) e coleta os dados 
 * do item com o jogador.
 */
void inserirItem() {
    // 1. Verificar se a mochila está cheia
    if (contadorItens >= MAX_ITENS) {
        printf("\n⚠️ ATENÇÃO: A mochila está cheia! Não é possível coletar mais loot.\n");
        return;
    }

    printf("\n--- ➕ Cadastro de Novo Item ---\n");
    
    // 2. Coletar dados do novo item
    
    // Nome
    printf("Informe o nome do item (máx 29 caracteres): ");
    // Uso de scanf("%s") para evitar problemas com buffer ao ler uma única palavra
    // Nota: Em um sistema mais robusto, usaríamos fgets() + limpeza de buffer.
    scanf("%29s", inventario[contadorItens].nome); 

    // Tipo
    printf("Informe o tipo do item (ex: arma, munição, cura): ");
    scanf("%19s", inventario[contadorItens].tipo);

    // Quantidade
    printf("Informe a quantidade: ");
    while (scanf("%d", &inventario[contadorItens].quantidade) != 1) {
        // Trata erro de entrada (não numérico)
        while(getchar() != '\n'); // Limpa o buffer
        printf("Entrada inválida. Por favor, digite um número inteiro para a quantidade: ");
    }

    // 3. Incrementa o contador, inserindo o item na próxima posição livre
    printf("\n✅ Item '%s' cadastrado com sucesso na mochila!\n", inventario[contadorItens].nome);
    contadorItens++; 

    listarItens(); // Lista após cada operação
}

/**
 * @brief Função obrigatória para buscar um item pelo nome (busca sequencial).
 * * Implementa uma busca sequencial linear no vetor de structs.
 * * @param nomeBusca O nome do item a ser localizado.
 * @return int O índice do item encontrado, ou -1 se não for localizado.
 */
int buscarItem(const char *nomeBusca) {
    // Percorre todos os itens presentes na mochila
    for (int i = 0; i < contadorItens; i++) {
        // Compara o nome do item no inventário (ignora maiúsculas/minúsculas)
        if (strcasecmp(inventario[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado, retorna o índice
        }
    }
    return -1; // Item não encontrado
}

/**
 * @brief Função obrigatória para remover um item da mochila pelo nome.
 * * Usa a busca sequencial para localizar o item e, se encontrado, o remove 
 * reorganizando o vetor de structs para evitar "buracos".
 */
void removerItem() {
    if (contadorItens == 0) {
        printf("\n⚠️ A mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeParaRemover[30];
    printf("\n--- ➖ Remoção de Item ---\n");
    printf("Informe o NOME do item que deseja descartar: ");
    scanf("%29s", nomeParaRemover);

    // 1. Busca sequencial para encontrar o índice do item
    int indice = buscarItem(nomeParaRemover);

    if (indice != -1) {
        // 2. Item encontrado. Reorganizar o vetor para remover o item
        
        // Desloca todos os itens à direita do índice para uma posição à esquerda,
        // sobrescrevendo o item a ser removido.
        for (int i = indice; i < contadorItens - 1; i++) {
            inventario[i] = inventario[i + 1];
        }
        
        // 3. Diminui o contador de itens
        contadorItens--;
        
        printf("\n✅ Item '%s' descartado com sucesso da mochila!\n", nomeParaRemover);
    } else {
        printf("\n❌ ERRO: Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    }

    listarItens(); // Lista após cada operação
}

/**
 * @brief Função que executa a busca e exibe o resultado para o jogador.
 */
void buscarItemInterface() {
    if (contadorItens == 0) {
        printf("\n⚠️ A mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeParaBuscar[30];
    printf("\n--- 🔍 Busca de Item ---\n");
    printf("Informe o NOME do item que deseja localizar: ");
    scanf("%29s", nomeParaBuscar);

    int indice = buscarItem(nomeParaBuscar);

    if (indice != -1) {
        // Item encontrado
        Item itemEncontrado = inventario[indice];
        printf("\n✅ Item '%s' encontrado na mochila!\n", nomeParaBuscar);
        printf("Detalhes:\n");
        printf("  -> Nome: %s\n", itemEncontrado.nome);
        printf("  -> Tipo: %s\n", itemEncontrado.tipo);
        printf("  -> Quantidade: %d\n", itemEncontrado.quantidade);
    } else {
        // Item não encontrado
        printf("\n❌ Item '%s' não encontrado na mochila. Tente outro nome.\n", nomeParaBuscar);
    }
}

// ----------------------------------------------------------------------------------

/**
 * @brief Função principal do programa.
 * * Controla o fluxo de execução e a interação com o jogador.
 */
int main() {
    int opcao;

    printf("Iniciando a Simulação de Inventário de Loot...\n");

    // Laço principal do menu
    do {
        exibirMenu();
        
        // Validação básica de entrada de opção
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa o buffer de entrada
            opcao = 0; // Define uma opção inválida para repetir o loop
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                buscarItemInterface();
                break;
            case 4:
                printf("\n👋 Jogo Encerrado. Obrigado por usar o sistema de Inventário!\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
                break;
        }
        
    } while (opcao != 4);

    return 0;
}