#include "hashSet.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

hashSet *newHashSet(int size) {
    hashSet *set;

    if (size < 1) { return NULL; }

    if ((set = malloc(sizeof(hashSet))) == NULL) { return NULL; }

    if ((set->table = malloc(sizeof(entry *) * size)) == NULL) { return NULL; }

    for (int i = 0; i < size; i++) {
        set->table[i] = NULL;
    }

    set->size = size;

    return set;
}

void freeHashSet(hashSet* this) {
    if (this == NULL) { return; }

    for (int i = 0; i < this->size; i++) {
        if (this->table[i] != NULL) { free(this->table[i]); }
    }

    free(this->table);
    free(this);
}

unsigned int hash(hashSet *this, char *key) {
    unsigned long int hashCode = 0;
    int i = 0;

    while (hashCode < ULONG_MAX && i < strlen(key)) {
        hashCode = hashCode << 8;
        hashCode += key[i];
        i++;
    }

    return hashCode % this->size;
}

void insert(hashSet *this, char *key, void *value) {
    if (lookup(this, key) == NULL) {
        entry *newEntry;
        unsigned int bucket = hash(this, key);

        newEntry = malloc(sizeof(entry));
        newEntry->key = strdup(key);
        newEntry->value = value;
        newEntry->next = this->table[bucket];
        this->table[bucket] = newEntry;
    }
}

void* lookup(hashSet *this, char *key) {
    unsigned int bucket = hash(this, key);
    entry *e = this->table[bucket];

    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            return e->value;
        }
        e = e->next;
    }

    return NULL;
}

bool delete(hashSet *this, char *key) {
    unsigned int bucket = hash(this, key);
    entry *e = this->table[bucket];
    entry *prev = NULL;

    while (e != NULL) {
        if (strcmp(e->key, key) == 0) {
            if (prev == NULL) {
                this->table[bucket] = e->next;
            } else {
                prev->next = e->next;
            }
            free(e->key);
            free(e);
            return true;
        }
        prev = e;
        e = e->next;
    }

    return false;
}