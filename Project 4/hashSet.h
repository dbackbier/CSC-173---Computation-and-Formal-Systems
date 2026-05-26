#ifndef PROJECT_4_HASHSET_H
#define PROJECT_4_HASHSET_H

#include <stdbool.h>

typedef struct entry{
    char *key;
    void *value;
    struct entry *next;
} entry;

typedef struct hashSet{
    int size;
    entry** table;
} hashSet;

extern hashSet *newHashSet(int size);
extern void freeHashSet(hashSet* this);
extern unsigned int hash(hashSet *this, char *key);
extern void insert(hashSet *this, char *key, void *value);
extern void* lookup(hashSet *this, char *key);
extern bool delete(hashSet *this, char *key);

#endif //PROJECT_4_HASHSET_H