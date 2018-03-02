#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h> // C99特性

#define TSIZE 45
struct film {
    char title[TSIZE];
    int rating;
};

typedef struct film Item;

typedef struct node {
    Item item;
    struct node* next;
} Node;

typedef Node* List;

typedef void (*traverse_cb)(Item item);

void InitializeList(List* plist);
bool ListIsEmpty(const List* plist);
bool ListIsFull(const List* plist);
unsigned int ListItemCount(const List* plist);
bool AddItem(Item item, List* plist);
void Traverse(const List* plist, traverse_cb cb);
void EmptyTheList(List* plist);

#endif