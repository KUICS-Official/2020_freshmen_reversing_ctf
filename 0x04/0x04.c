#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int hash();

uint32_t corr = 0x0e000000;

int main ()
{
    char buf[32];
	
    printf("[KUICS] Welcome to SECURE Flag Print Service! Enter the code : ");
    scanf("%s", buf);

    if(strlen(buf) != 16)
    {
        printf("[Error] The code should be 16 byte!");
        exit(-1);
    }
    
    uint32_t digest = hash(buf);

    if(digest != corr)
    {
        printf("[Error] Invalid code!");
        exit(-1);
    }

	puts("[KUICS] Valid serial! Here is the flag you ordered ^^");
	system("/bin/cat ~/flag"); 

    return 0;
}

int hash(char* msg)
{   
    uint32_t p1;
    uint32_t p2;
    uint32_t p3;
    uint32_t p4;

    p1 = (uint32_t)((msg[3] << 24) + (msg[2] << 16) + (msg[1] << 8) + (msg[0] << 0));
    p2 = (uint32_t)((msg[7] << 24) + (msg[6] << 16) + (msg[5] << 8) + (msg[4] << 0));
    p3 = (uint32_t)((msg[11] << 24) + (msg[10] << 16) + (msg[9] << 8) + (msg[8] << 0));
    p4 = (uint32_t)((msg[15] << 24) + (msg[14] << 16) + (msg[13] << 8) + (msg[12] << 0));

    uint32_t s1 = p1 + p3;
    uint32_t s2 = p2 + p4;

    return (int)(s1^s2);
}

