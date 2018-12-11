#include <mqueue.h>

#include "../adapters/queue.h"

int main(void)
{
    mqd_t test_queue;
    
    queue_Create("/test", test_queue, 10)
    
    queue_Write(test_queue, 4);

    int data = queue_Read(test_queue);

    printf("I received %d\n", data);

    return 0;
}
