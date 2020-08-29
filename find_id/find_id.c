#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void serialize(char *str)
{
    int len, key_len;
    char key[10] = "kuics4win";
    
    len = strlen(str);
    for(int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }

    key_len = strlen(key);
    for(int i = 0; i < len; i++) {
        str[i] = str[i] ^ key[i % key_len];
    }

    printf("OK, your serial is given as: ");

    for(int i = 0; i < len; i++) {
        printf("%02X", str[i]);
    }
    putchar('\n');
}

int main()
{
    char str[100];

    printf("Please, give me your ID: ");
    scanf("%s", str);

    serialize(str);
}
