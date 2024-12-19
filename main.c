#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include "sudoku_lista.h"

void printHeader() {
    printf("========================================\n");
    printf("         SOLUCIONADOR DE SUDOKU         \n");
    printf("========================================\n");
}

void printDivider() {
    printf("----------------------------------------\n");
}

double calculateElapsedTime(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER frequency) {
    return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
}

int main() {
    printHeader();

    printf("[1] Abrindo arquivo 'sudoku.csv'...\n");
    FILE* file = fopen("sudoku.csv", "r");
    if (!file) {
        perror("[ERRO] Nao foi possivel abrir o arquivo");
        return EXIT_FAILURE;
    }
    printf("[SUCESSO] Arquivo aberto com sucesso!\n");

    printDivider();

    LARGE_INTEGER frequency, startTotal, endTotal;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTotal);

    printf("[2] Construindo tabela hash...\n");
    LARGE_INTEGER startBuild, endBuild;
    QueryPerformanceCounter(&startBuild);

    HashTable* table = buildHashTable(file);

    QueryPerformanceCounter(&endBuild);
    fclose(file);

    double buildTime = calculateElapsedTime(startBuild, endBuild, frequency);
    printf("[SUCESSO] Tabela hash construida com sucesso!\n");
    printf("[INFO] Tempo para construir a tabela hash: %.9f segundos\n", buildTime);

    printDivider();

    // medindo o tempo de busca
    const char* desafio = "029006100703000060861702005430000901000010040006070283300067018008500000102304000";
    printf("[3] Iniciando busca pelo desafio:\n%s\n", desafio);

    LARGE_INTEGER startSearch, endSearch;
    QueryPerformanceCounter(&startSearch);

    const char* resultado = searchHashTable(table, desafio);

    QueryPerformanceCounter(&endSearch);

    double searchTime = calculateElapsedTime(startSearch, endSearch, frequency);

    if (resultado) {
        printf("[SUCESSO] Solucao encontrada:\n%s\n", resultado);
    } else {
        printf("[ERRO] Solucao nao encontrada.\n");
    }

    printDivider();
    printf("[4] Tempo de busca: %.9f segundos\n", searchTime);

    QueryPerformanceCounter(&endTotal);
    double totalTime = calculateElapsedTime(startTotal, endTotal, frequency);

    printDivider();
    printf("[5] Limpando memoria...\n");
    freeHashTable(table);
    printf("[SUCESSO] Memoria liberada com sucesso!\n");

    printDivider();
    printf("[INFO] Tempo total (hash + busca): %.9f segundos\n", totalTime);

    printDivider();
    printf("           PROGRAMA FINALIZADO          \n");
    printf("========================================\n");

    return EXIT_SUCCESS;
}
