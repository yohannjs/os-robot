#include <unistd.h>
#include <stdio.h>

#include "../drive.h"
#include "../adapters/detect.h"

const int SAMPLE_NUM = 100; 

int main()
{
    drive_SensorInit();
    detect_Init();

    FILE* f;
    f = fopen("samples.txt")

    drive_ScanTurn(180);
    
    for (int i = 0; i < SAMPLE_NUM; i++)
    {
        fprintf(f, "%d\n", detect_GetDistance());
        usleep(100 * 1000);
    }
    fclose(f);
    return 0;
}
