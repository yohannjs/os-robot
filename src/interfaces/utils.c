#include <unistd.h>
#include <stdio.h>

void utils_sleep(int ms)
{
    usleep(ms * 1000);
}

void utils_log(const char *module_name, const char *msg)
{
    printf("[%s] %s\n", module_name, msg);
}

void utils_err(const char *module_name, const char *msg)
{
    printf("\e[91m[%s] %s\e[0m\n", module_name, msg);
}

float utils_battery(void)
{
    FILE *f;
    f = fopen("/sys/class/power_supply/legoev3/battery_now", "r");
    int battery_voltage;
    fscanf(f, "%d", &battery_voltage);
    fclose(f);

    return ((float) battery_voltage) / 1000;
}
