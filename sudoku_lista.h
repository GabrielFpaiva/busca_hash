#ifndef SUDOKU_LISTA
#define SUDOKU_LISTA

#include <stdio.h>

// estrutura de no da tabela
typedef struct HashNode {
    char challenge[82];
    char solution[82];
    struct HashNode* next; 
} HashNode;

// tabela hash
typedef struct HashTable {
    HashNode** buckets; 
    int size;           
} HashTable;

HashTable* createHashTable(int size);
void insertHashTable(HashTable* table, const char* challenge, const char* solution);
const char* searchHashTable(HashTable* table, const char* challenge);
void freeHashTable(HashTable* table);
HashTable* buildHashTable(FILE* file);

#endif