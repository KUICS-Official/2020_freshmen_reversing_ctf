#include <stdio.h>

void success()
{
    printf("Success!");
    printf("flag is FLAG{MD5 hash your result offset in decimal form}");
    return;
}

int main()
{
    unsigned int eip;
    int off;
    void (*foo)(void);

    printf("I want to jump to success at once!\n");
    asm volatile("1: lea 1b, %0;": "=a"(eip));
    printf("give me offset in decimal!: ");
    scanf("%d", &off);
    printf("jumping with offset...\n");
    foo = (void (*)()) (eip + off);
    foo();
}
