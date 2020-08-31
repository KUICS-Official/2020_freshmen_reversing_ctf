#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* key = "Q[VPl^yaredrHxqHOXEj";

int compare(char* src, char* dst);

int main ()
{
    char buf[128];
    
    printf("[KUICS] Serial number for Flag Print Service? : ");
    scanf("%s", buf);
    
    if(compare(buf, key) == -1)
    { 
        puts("[Error] Invalid serial number!");
        exit(-1);
    }

	puts("[KUICS] Valid serial! The flag is the answer you typed! ^^");
    return 0;
}

int compare(char* src, char* dst)
{
    if (strlen(src) != strlen(dst))
        return -1;
        
    int xor_key = 0x17;
    for(int idx = 0; idx < strlen(dst); idx++)
    {
        if (src[idx] != (dst[idx] ^ xor_key))
            return -1;
    }
    return 0;
}
