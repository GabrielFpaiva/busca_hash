#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 10007 

typedef struct HashNode {
    char challenge[82];   
    char solution[82];    
    struct HashNode* next; 
} HashNode;

typedef struct HashTable {
    HashNode** buckets;   
    int size;             
} HashTable;

unsigned int hashFunction(const char* str, int tableSize) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str++) % tableSize; 
    }
    return hash;
}

// tabela hash
HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) {
        perror("erro");
        exit(EXIT_FAILURE);
    }
    table->size = size;
    table->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    if (!table->buckets) {
        perror("erro");
        free(table);
        exit(EXIT_FAILURE);
    }
    return table;
}

// inserindo puzzle e solucao na tabela
void insertHashTable(HashTable* table, const char* challenge, const char* solution) {
    unsigned int index = hashFunction(challenge, table->size);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (!newNode) {
        perror("erro");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->challenge, challenge);
    strcpy(newNode->solution, solution);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

// buscando a solucao pelo desafio
const char* searchHashTable(HashTable* table, const char* challenge) {
    unsigned int index = hashFunction(challenge, table->size);
    HashNode* current = table->buckets[index];
    while (current) {
        if (strcmp(current->challenge, challenge) == 0) {
            return current->solution;
        }
        current = current->next;
    }
    return NULL;
}

// liberando memoria
void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

HashTable* buildHashTable(FILE* file) {
    HashTable* table = createHashTable(HASH_TABLE_SIZE);
    char challenge[82], solution[82];

    // tem q ignorar o cabeçalho
    char header[256];
    fgets(header, sizeof(header), file);

    while (fscanf(file, "%81[^,],%81s\n", challenge, solution) == 2) {
        insertHashTable(table, challenge, solution);
    }

    return table;
}
