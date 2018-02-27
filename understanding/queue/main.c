#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
* A pointer to a list node.
*/
static QUEUE* q;

static QUEUE queue;
static QUEUE split_queue;

/**
* Our item struct we want to store in queue.
*/
struct user_s {
    int age;
    char* name;

    QUEUE node;
};

// 参考 
// http://www.cnblogs.com/chenyangyao/p/libuv.html
// https://www.jianshu.com/p/6373de1e117d
int main() {
    struct user_s* user;
    struct instance_s* instance;

    struct user_s john;
    john.name = "john";
    john.age = 44;

    struct user_s henry;
    henry.name = "henry";
    henry.age = 32;

    struct user_s amy;
    amy.name = "amy";
    amy.age = 27;

    struct user_s tom;
    tom.name = "tom";
    tom.age = 12;

    QUEUE_INIT(&queue);
    QUEUE_INIT(&john.node);
    QUEUE_INIT(&henry.node);
    QUEUE_INIT(&amy.node);
    QUEUE_INIT(&tom.node);

    printf("The queue is empty now? %s\n", QUEUE_EMPTY(&queue) ? "YES" : "NO");

    QUEUE_INSERT_TAIL(&queue, &john.node);
    QUEUE_INSERT_TAIL(&queue, &henry.node);
    QUEUE_INSERT_TAIL(&queue, &amy.node);
    QUEUE_INSERT_TAIL(&queue, &tom.node);

    printf("Insert john, henry, amy, tom.\n");

    printf("The queue is empty now? %s\n\n", QUEUE_EMPTY(&queue) ? "YES" : "NO");

    q = QUEUE_HEAD(&queue);

    user = QUEUE_DATA(q, struct user_s, node);

    printf("Received first inserted user: %s who is %d.\n", user->name, user->age);

    QUEUE_REMOVE(q);
    printf("Remove tom from the queue.\n\n");

    QUEUE_FOREACH(q, &queue) {
        user = QUEUE_DATA(q, struct user_s, node);

        printf("Received rest inserted users: %s who is %d\n", user->name, user->age);
    }

    printf("\nSplit the queue.\n");

    // 分割队列
    QUEUE_INIT(&split_queue);

    // 以tom为分割点进行队列分割，tom归属于新队列
    QUEUE_SPLIT(&queue, &tom.node, &split_queue);

    QUEUE_FOREACH(q, &queue) {
        user = QUEUE_DATA(q, struct user_s, node);

        printf("Received split A users: %s who is %d\n", user->name, user->age);
    }

    QUEUE_FOREACH(q, &split_queue) {
        user = QUEUE_DATA(q, struct user_s, node);

        printf("Received split B users: %s who is %d\n", user->name, user->age);
    }

    // 合并队列
    printf("\nMerge two queues.\n");
    
    QUEUE_ADD(&queue, &split_queue);

    QUEUE_FOREACH(q, &queue) {
        user = QUEUE_DATA(q, struct user_s, node);

        printf("Received merged users: %s who is %d\n", user->name, user->age);
    }

    return 0;
}