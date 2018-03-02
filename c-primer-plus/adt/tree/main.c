#include "tree.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char menu();
void add_pet(tree_t*);
void drop_pet(tree_t*);
void show_pets(const tree_t*);
void find_pet(const tree_t*);
void print_item(item_t);
void uppercase(char*);
char* s_gets(char*, int);
int main()
{
    tree_t pets;
    char choice;
    tree_init(&pets);
    while ((choice = menu()) != 'q') {
        switch (choice) {
        case 'a':
            add_pet(&pets);
            break;
        case 'l':
            show_pets(&pets);
            break;
        case 'f':
            find_pet(&pets);
            break;
        case 'n':
            printf("%d pets in club\n", tree_item_count(&pets));
            break;
        case 'd':
            drop_pet(&pets);
            break;
        default:
            puts("Switching error");
        }
    }
    delete_all(&pets);
    puts("Bye.");
    return 0;
}

char menu()
{
    int ch;
    puts("Nerfville Pet Club Membership Program");
    puts("Enter the letter corresponding to your choice:");
    puts("a)add a pet l)show list of pets");
    puts("n)number of pets f)find pets");
    puts("d)delete a pet q)quit");

    while ((ch = getchar()) != EOF) {
        while (getchar() != '\n')
            continue;
        ch = tolower(ch);
        if (strchr("alfndq", ch) == NULL)
            puts("Please enter an a, l, f, n, d, or q:");
        else
            break;
    }
    if (ch == EOF)
        ch = 'q';
    return ch;
}

void add_pet(tree_t* pt)
{
    item_t temp;
    if (tree_is_full(pt))
        puts("No room in the club!");
    else {
        puts("Please enter name of pet:");
        s_gets(temp.petname, SLEN);
        uppercase(temp.petname);
        puts("Please enter kind of pet:");
        s_gets(temp.petkind, SLEN);
        uppercase(temp.petkind);

        add_item(&temp, pt);
    }
}

void show_pets(const tree_t* pt)
{
    if (tree_is_empty(pt))
        puts("No entries!");
    else
        traverse(pt, print_item);
}

void print_item(item_t item)
{
    printf("Pet: %-19s Kind: %-19s\n", item.petname, item.petkind);
}

void find_pet(const tree_t* pt)
{
    item_t temp;
    if (tree_is_empty(pt)) {
        puts("No entries!");
        return;
    }

    puts("Please enter name of pet you wish to find:");
    s_gets(temp.petname, SLEN);
    puts("Please enter pet kind:");
    s_gets(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);

    printf("%s the %s ", temp.petname, temp.petkind);
    if (in_tree(&temp, pt))
        puts("is a member.");
    else
        puts("is not a member.");
}

void drop_pet(tree_t* pt)
{
    item_t temp;
    if (tree_is_empty(pt)) {
        puts("No entries!");
        return;
    }

    puts("Please enter name of pet you wish to find:");
    s_gets(temp.petname, SLEN);
    puts("Please enter pet kind:");
    s_gets(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);

    printf("%s the %s ", temp.petname, temp.petkind);
    if (delete_item(&temp, pt))
        puts("is dropped from the club.");
    else
        puts("is not a member.");
}

void uppercase(char* str)
{
    while (*str) {
        *str = toupper(*str);
        str++;
    }
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