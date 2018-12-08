#include "lib/ev3.h"

#include "adapters/detect.h"

#include <stdio.h>

int main()
{
	if (ev3_init())
		printf("woohoo\n");
	else
		printf("buhu\n");
	
	int status = detect_Init();
	printf("Detect module status: %d\n", status);
	
	printf("Distance: %d\n", detect_GetDistance());
	printf("Floor: %d\n", detect_OnLine());
	
	return 0;
}
