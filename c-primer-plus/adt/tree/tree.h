#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>
#define SLEN 20
typedef struct item_s {
    char petname[SLEN];
    char petkind[SLEN];
} item_t;

#define MAXITEMS 10

typedef struct trnode_s {
    item_t item;
    struct trnode_s* left;
    struct trnode_s* right;
} trnode_t;

typedef struct tree_s {
    trnode_t* root;
    int size;
} tree_t;

typedef void (*traverse_cb)(item_t);

void tree_init(tree_t*);

bool tree_is_empty(const tree_t*);

bool tree_is_full(const tree_t*);

int tree_item_count(const tree_t*);

bool add_item(const item_t*, tree_t*);

bool in_tree(const item_t*, const tree_t*);

bool delete_item(const item_t*, tree_t*);

void traverse(const tree_t*, traverse_cb cb);

void delete_all(tree_t*);

#endif