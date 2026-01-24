typedef struct LinkedList* LinkedList;

extern LinkedList new_LinkedList();
extern void*  getFirst(LinkedList l);
extern void prepend(LinkedList list, void *data);