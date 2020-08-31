#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* key = "\\B^TDl^yaredrHxqHOXEj";

void print_flag();

int main ()
{
    int out_of_service;
    char buf[128];
    
    if(out_of_service = 0)
    {
        puts("[KUICS] Welcome to Flag Print Service! Here is your flag ^^");
    	print_flag();

    }
    else
    {
        puts("[KUICS] Sorry... Flag Print Service is out of service TT");
    }    
    
    return 0;
}

void print_flag()
{   
    char flag[] = { 181, 75, 168, 85, 255, 211, 78, 172, 67, 172, 115, 134, 77, 237, 244, 75, 174, 64, 128, 110, 139, 126, 225, 228 };
    unsigned int key[] = { 0xf3, 0x07, 0xe9, 0x12, 0x84, 0x99, 0x3b, 0xc1, 0x33 };
    
    for(int idx = 0; idx < strlen(flag); idx++)
    {
        printf("%c", flag[idx] ^ key[idx % (sizeof(key) / sizeof(int))]);
    }
    puts("");
    return;
}
