#ifndef SCAN_H
#define SCAN_H

int scan_LoadSamples(char *file_name, int *samples);
int scan_Scan360(int *samples);
int scan_WriteSamplesToFile(int *samples, char *file_name);
int scan_FindBall2(int* samples, int threshold, int *head, int *dist);

#endif
