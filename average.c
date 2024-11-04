#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE  2000000

int media(){
    int v[SIZE], sum = 0;
    for (int i = 0; i < SIZE; i++)
        v[i] = rand() % 100; // Random number between 0 and 99
    for (int i = 0; i < SIZE; i++)
        sum = sum + v[i];
    return sum/SIZE;
}

void main(){
    clock_t start, end;
    double cpu_time_used;
    int val;
    for (int i = 0; i < 300; i++){
        start = clock();
        val = media();
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%g \n",  cpu_time_used);
    }
}
