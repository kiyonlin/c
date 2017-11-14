#include <stdio.h>

typedef unsigned char *pointer;

void show_bytes(pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
    {
        printf("%p\t0x%.2x\n", start + i, start[i]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    long a = 99344212109836183;
    printf("long a = 99344212109836183;\n");
    show_bytes((pointer) &a, sizeof(long));
    return 0;
}
