#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdbool.h>
//Structure to hold the data
typedef struct Data {
    char *key;
    void *value;
    struct Data *next;
} Data;
//Structure to hold hashtable
typedef struct HashTable {
    int size;
    Data **table;
} HashTable;
HashTable *createNewHashTable(int size);
unsigned long int hash(HashTable *hashtable, char *key);
void insertValue(HashTable *hashtable, char *key, void *value);
void *lookupValue(HashTable *hashtable, char *key);
bool deleteValue(HashTable *hashtable, char *key);
void freeHashTable(HashTable *hashtable);
#endif //HASHTABLE_H
