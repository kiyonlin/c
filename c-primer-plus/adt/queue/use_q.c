#include "queue.h"
#include <stdio.h>
int main()
{
    Queue line;
    Item item;
    char ch;
    InitializeQueue(&line);
    puts("Testing the Queue interface.");
    puts("Type a to add a value,");
    puts("type d to delete a value, and type q to quit.");
    while ((ch = getchar()) != 'q') {

        if ((ch != 'a' && ch != 'd'))
            continue; // 忽略其他输入

        if (ch == 'a') {
            printf("Interger to add:");
            scanf("%d", &item);
            if (!QueueIsFull(&line)) {
                printf("Putting %d into queue\n", item);
                EnQueue(item, &line);
            } else {
                puts("Queue is full!");
            }
        } else {
            if (QueueIsEmpty(&line))
                puts("Nothing to delete!");
            else {
                DeQueue(&item, &line);
                printf("Removing %d from queue\n", item);
            }
        }

        printf("%d items in queue\n", QueueItemCount(&line));
        puts("Type a to add, d to delete, q to quit:");
    }

    EmptyTheQueue(&line);
    puts("Bye!");

    return 0;
}