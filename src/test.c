#include "lib/ev3.h"
#include <stdio.h>

int main()
{
	if (ev3_init())
	{
		printf("woohoo\n");
	}
	else
	{
		printf("buhu\n");
	}
	return 0;
}
