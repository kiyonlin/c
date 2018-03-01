#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TSIZE 45

struct film {
    struct film* next; // 指向链表中的下一个结构
    int rating;
    char title[TSIZE];
};

char* s_gets(char* st, int n);

int main()
{
    struct film* head = NULL;
    struct film *prev, *current;
    char input[TSIZE];

    // 收集并存储信息
    puts("Enter first movie title:");
    while (s_gets(input, TSIZE) != NULL && input[0] != '\0') {
        current = (struct film*)malloc(sizeof(struct film));
        if (head == NULL) {
            head = current;
        } else {
            prev->next = current;
        }
        current->next = NULL;
        strcpy(current->title, input);
        puts("Enter your rating <0-10>:");
        scanf("%d", &current->rating);
        while (getchar() != '\n') {
            continue;
        }

        puts("Enter next movie title (empty line to stop):");
        prev = current;
    }

    if (head == NULL) {
        puts("No data entered.");
    } else {
        puts("Here is the movie list:");
    }

    current = head;

    while (current != NULL) {
        printf("Movie: %s Rating: %d\n", current->title, current->rating);
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        head = current->next;
        free(current);
        current = head;
    }

    puts("Bye!");
    return 0;
}

char* s_gets(char* st, int n)
{
    char* ret_val;
    char* find;
    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(st, '\n');
        if (find) {
            *find = '\0';
        } else {
            while (getchar() != '\n')
                continue;
        }
    }
    return ret_val;
}