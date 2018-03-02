#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair_s {
    trnode_t* parent;
    trnode_t* child;
} pair_t;

static trnode_t* make_node(const item_t*);
static bool to_left(const item_t*, const item_t*);
static bool to_right(const item_t*, const item_t*);
static void add_node(trnode_t*, trnode_t*);
static void in_order(const trnode_t*, traverse_cb cb);
static pair_t seek_item(const item_t*, const tree_t*);
static void delete_node(trnode_t**);
static void delete_all_nodes(trnode_t*);

void tree_init(tree_t* ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool tree_is_empty(const tree_t* ptree)
{
    return ptree->root == NULL;
}

bool tree_is_full(const tree_t* ptree)
{
    return ptree->size == MAXITEMS;
}

int tree_item_count(const tree_t* ptree)
{
    return ptree->size;
}

bool add_item(const item_t* pitem, tree_t* ptree)
{
    trnode_t* new_node;
    if (tree_is_full(ptree)) {
        fprintf(stderr, "Tree is full\n");
        return false;
    }

    if (seek_item(pitem, ptree).child != NULL) {
        fprintf(stderr, "Attempted to add duplicate item\n");
        return false;
    }

    new_node = make_node(pitem);

    if (new_node == NULL) {
        fprintf(stderr, "Couldn't create node\n");
        return false;
    }

    ptree->size++;
    if (ptree->root == NULL) {
        ptree->root = new_node;
    } else {
        add_node(new_node, ptree->root);
    }

    return true;
}

bool in_tree(const item_t* pitem, const tree_t* ptree)
{
    return !(seek_item(pitem, ptree).child == NULL);
}

bool delete_item(const item_t* pitem, tree_t* ptree)
{
    pair_t look;
    look = seek_item(pitem, ptree);
    if (look.child == NULL)
        return false;
    if (look.parent == NULL)
        delete_node(&ptree->root);
    else if (look.parent->left == look.child)
        delete_node(&look.parent->left);
    else
        delete_node(&look.parent->right);

    ptree->size--;
    return true;
}

void traverse(const tree_t* ptree, traverse_cb cb)
{
    if (ptree != NULL) {
        in_order(ptree->root, cb);
    }
}

void delete_all(tree_t* ptree)
{
    if (ptree != NULL)
        delete_all_nodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}

static void in_order(const trnode_t* root, traverse_cb cb)
{
    if (root != NULL) {
        in_order(root->left, cb);
        cb(root->item);
        in_order(root->right, cb);
    }
}

static void delete_all_nodes(trnode_t* root)
{
    trnode_t* pright;
    if (root != NULL) {
        pright = root->right;
        delete_all_nodes(root->left);
        free(root);
        delete_all_nodes(pright);
    }
}

static void add_node(trnode_t* new_node, trnode_t* root)
{
    if (to_left(&new_node->item, &root->item)) {
        if (root->left == NULL) {
            root->left = new_node;
        } else {
            add_node(new_node, root->left);
        }
    } else if (to_right(&new_node->item, &root->item)) {
        if (root->right == NULL) {
            root->right = new_node;
        } else {
            add_node(new_node, root->right);
        }
    } else {
        fprintf(stderr, "Location error in add_node()\n");
        exit(EXIT_FAILURE);
    }
}

static bool to_left(const item_t* i1, const item_t* i2)
{
    int comp;
    if ((comp = strcmp(i1->petname, i2->petname)) < 0)
        return true;
    else if (comp == 0 && strcmp(i1->petkind, i2->petkind) < 0)
        return true;
    else
        return false;
}

static bool to_right(const item_t* i1, const item_t* i2)
{
    int comp;
    if ((comp = strcmp(i1->petname, i2->petname)) > 0)
        return true;
    else if (comp == 0 && strcmp(i1->petkind, i2->petkind) > 0)
        return true;
    else
        return false;
}

static trnode_t* make_node(const item_t* pitem)
{
    trnode_t* new_node;
    new_node = (trnode_t*)malloc(sizeof(trnode_t));

    if (new_node != NULL) {
        new_node->item = *pitem;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

static pair_t seek_item(const item_t* pitem, const tree_t* ptree)
{
    pair_t look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
        return look;
    while (look.child != NULL) {
        if (to_left(pitem, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->left;
        } else if (to_right(pitem, &(look.child->item))) {
            look.parent = look.child;
            look.child = look.child->right;
        } else
            break; //与root相等
    }

    return look;
}

// ptr是指向目标节点的父节点指针成员的地址
static void delete_node(trnode_t** ptr)
{
    trnode_t* temp;
    if ((*ptr)->left == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    } else if ((*ptr)->right == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    } else {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
            continue;

        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}