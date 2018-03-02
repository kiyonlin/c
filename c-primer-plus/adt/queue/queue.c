#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

static void CopyToNode(Item, Node*);
static void CopyToItem(Node*, Item*);

void InitializeQueue(Queue* pq)
{
    pq->front = pq->rear = NULL;
    pq->items = 0;
}

bool QueueIsFull(const Queue* pq)
{
    return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue* pq)
{
    return pq->items == 0;
}

int QueueItemCount(const Queue* pq)
{
    return pq->items;
}

bool EnQueue(Item item, Queue* pq)
{
    Node* pnew;
    if (QueueIsFull(pq)) {
        return false;
    }

    pnew = (Node*)malloc(sizeof(Node));
    if (pnew == NULL) {
        fprintf(stderr, "Unable to allocate memory!\n");
        exit(EXIT_FAILURE);
    }

    CopyToNode(item, pnew);

    pnew->next = NULL;
    if (QueueIsEmpty(pq))
        pq->front = pnew;
    else
        pq->rear->next = pnew;

    pq->rear = pnew;
    pq->items++;
    return true;
}

bool DeQueue(Item* pitem, Queue* pq)
{
    Node* ptemp;
    if (QueueIsEmpty(pq))
        return false;
    CopyToItem(pq->front, pitem);

    ptemp = pq->front;
    pq->front = pq->front->next;
    free(ptemp);
    pq->items--;

    // 队列为空时，处理队列尾部指针
    if (pq->items == 0) {
        pq->rear = NULL;
    }

    return true;
}

void EmptyTheQueue(Queue* pq)
{
    Item dummy;
    while (!QueueIsEmpty(pq)) {
        DeQueue(&dummy, pq);
    }
}

static void CopyToNode(Item item, Node* pnode)
{
    pnode->item = item;
}

static void CopyToItem(Node* pnode, Item* pitem)
{
    (*pitem) = pnode->item;
}