#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char serial[128];

	printf("[KUICS] Please enter the serial number of Flag Print Service ^^ : ");
	scanf("%s", serial);

	if(strlen(serial) != 16)
	{
		puts("[Error] Serial number is 16-bytes long!");
		exit(-1);
	}

	if(strncmp(serial, "KUICS-2020-", 11) != 0)
	{
		puts("[Error] Invalid serial number!");
		exit(-1);
	}

	puts("[KUICS] Valid serial! Here is the flag you ordered ^^");
	system("/bin/cat ~/flag"); 
	return 0;
}
