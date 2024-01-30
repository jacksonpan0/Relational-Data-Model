#include <stdlib.h>
#include <string.h>
#include "databasefunc.h"
#include <limits.h>
// Create a new hash table
HashTable* createNewHashTable(int size) {
    if (size < 1) return NULL;
    // Allocate memory for the table structure
    HashTable* newTable = malloc(sizeof(HashTable));
    if (newTable == NULL) {
        return NULL;
    }
    // Allocate memory for the table itself
    newTable->table = malloc(sizeof(Data*) * size);
    if (newTable->table == NULL) {
        free(newTable);  // Cleanup if allocation fails
        return NULL;
    }
    // Initialize the elements of the table
    for (int i = 0; i < size; i++) {
        newTable->table[i] = NULL;
    }
    newTable->size = size;
    return newTable;
}
// Hash function
unsigned long int hash(HashTable *hashtable, char *key) {
    unsigned long int hashval = 0;
    size_t i = 0;  // Change the type of i to size_t
    // Convert string to an integer
    while (hashval < ULONG_MAX && i < strlen(key)) {
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }
    return hashval % hashtable->size;
}
// Insert a key-value pair into a hash table
void insertValue(HashTable *hashtable, char *key, void *value) {
    unsigned int bin = hash(hashtable, key);
    // Create a new entry
    Data *newEntry = malloc(sizeof(Data));
    if (!newEntry) {
        return;
    }
    newEntry->key = strdup(key);
    if (!newEntry->key) {
        free(newEntry);
        return;
    }
    newEntry->value = value;
    newEntry->next = hashtable->table[bin];
    hashtable->table[bin] = newEntry;
}
// Lookup a key in the hash table
void *lookupValue(HashTable *hashtable, char *key) {
    unsigned int bin = hash(hashtable, key);
    // Step through the bin, looking for the value
    for (Data *entry = hashtable->table[bin]; entry != NULL; entry = entry->next) {
        if (strcmp(key, entry->key) == 0) {
            return entry->value;
        }
    }
    return NULL;
}
// Delete a key-value pair from a hash table
bool deleteValue(HashTable *hashtable, char *key) {
    unsigned int bin = hash(hashtable, key);
    Data *entry = hashtable->table[bin];
    Data *previous = NULL;
    while (entry != NULL && strcmp(key, entry->key) != 0) {
        previous = entry;
        entry = entry->next;
    }
    if (entry == NULL) return false;
    if (previous == NULL) {
        hashtable->table[bin] = entry->next;
    } else {
        previous->next = entry->next;
    }
    free(entry->key);
    free(entry);
    return true;
}
// Free the hash table
void freeHashTable(HashTable *hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        Data *entry = hashtable->table[i];
        while (entry != NULL) {
            Data *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(hashtable->table);
    free(hashtable);
}
