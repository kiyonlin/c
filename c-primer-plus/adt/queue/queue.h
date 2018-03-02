#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

// 在这里插入Item类型的定义，例如
typedef int Item; // 用于use_q.c
// 或者typedef struct item {int gumption; int charisma;} Item;

#define MAXQUEUE 10

typedef struct node {
    Item item;
    struct node* next;
} Node;

typedef struct queue {
    Node* front;
    Node* rear;
    int items;
} Queue;

void InitializeQueue(Queue*);
bool QueueIsFull(const Queue*);
bool QueueIsEmpty(const Queue*);
int QueueItemCount(const Queue*);
bool EnQueue(Item item, Queue*);
bool DeQueue(Item*, Queue*);
void EmptyTheQueue(Queue*);

#endif