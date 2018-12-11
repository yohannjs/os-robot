#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>


#include "../drive.h"
#include "../adapters/detect.h"

const int SAMPLE_NUM = 1000; 

int main()
{
    
    drive_Init();
    //drive_InitTachos();
    detect_Init();

    FILE* f;
    f = fopen("samples.txt", "w");

    drive_TurnRightForever(10);
    
    for (int i = 0; i < SAMPLE_NUM; i++)
    {
        fprintf(f, "%d\t%d\n", drive_GetHeading(), detect_GetDistance());
        usleep(10 * 1000);
    }
    fclose(f);

    drive_Stop();
    return 0;
}
