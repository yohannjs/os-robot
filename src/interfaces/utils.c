#include <unistd.h>
#include <stdio.h>

void utils_Sleep(int ms)
{
    usleep(ms * 1000);
}

void utils_Log(const char *module_name, const char *msg)
{
    printf("[%s] %s\n", module_name, msg);
}

void utils_Err(const char *module_name, const char *msg)
{
    printf("\e[91m[%s] %s\e[0m\n", module_name, msg);
}

void utils_LogInt(const char *module_name, const char *msg, int number)
{
    printf("[%s] %s%d\n", module_name, msg, number);
}

void utils_ErrInt(const char *module_name, const char *msg, int number)
{
    printf("\e[91m[%s] %s%d\e[0m\n", module_name, msg, number);
}

int utils_Battery(void)
{
    FILE *f;
    f = fopen("/sys/class/power_supply/legoev3-battery/voltage_now", "r");
    int battery_voltage;
    fscanf(f, "%d", &battery_voltage);
    fclose(f);

    return battery_voltage / 10000;
}
