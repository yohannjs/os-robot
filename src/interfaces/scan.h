#ifndef SCAN_H
#define SCAN_H

int scan_TurnRightScan(int degrees, int speed);
int scan_FindBallHeading(int NUM_SAMPLES, int* head, int* dist);
int scan_LoadSamples(char *file_name, int *samples);
int scan_FindBall(int *samples, int *template, int *head, int *dist);
int scan_Scan360(int *samples, int speed);
int scan_WriteSamplesToFile(int *samples, char *file_name);
int FindBall2(int *samples, int threshold, int *head, int *dist);

#endif
