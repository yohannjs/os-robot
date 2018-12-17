#ifndef SCAN_H
#define SCAN_H

int scan_TurnRightScan(int degrees, int speed);
int scan_FindBallHeading(int NUM_SAMPLES, int* head, int* dist);
int scan_LoadSamples(char *file_name, int *samples);
int scan_FindBall(int *samples, int *template, int *head, int *dist);
int scan_Scan360(int speed, int *samples);
#endif
