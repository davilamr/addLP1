#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

#define MAX 200000

int cmpfunc (const void * a, const void * b)
{
   if(a>b) return 1;
   if(a<b) return -1;
   return 0;
}

int main(){

    int edad[MAX];
    int edadOrdenada[MAX];
    int sizeEdad = 5;
    struct timeval start, stop;
    double secs = 0;

    sizeEdad = fillFromFile(edad, MAX);
    gettimeofday(&start, NULL);
    nadiaSort(edad,sizeEdad,edadOrdenada);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTiempo Insumido (Nadia Sort) %.2f ms",secs*1000);

    sizeEdad = fillFromFile(edad, MAX);
    gettimeofday(&start, NULL);
    nadiaSort2(edad,sizeEdad);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTiempo Insumido (Nadia II Sort) %.2f ms",secs*1000);

    sizeEdad = fillFromFile(edad, MAX);
    gettimeofday(&start, NULL);
    bubleSort(edad,sizeEdad);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTiempo Insumido (Buble Sort) %.2f ms",secs*1000);

    sizeEdad = fillFromFile(edad, MAX);
    gettimeofday(&start, NULL);
    insertionSort(edad,sizeEdad);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTiempo Insumido (Insertion Sort) %.2f ms",secs*1000);

    sizeEdad = fillFromFile(edad, MAX);
    gettimeofday(&start, NULL);
    quickSort(edad,sizeEdad);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTiempo Insumido (Quick Sort) %.2f ms\n",secs*1000);


    sizeEdad = fillFromFile(edad, MAX);
    gettimeofday(&start, NULL);
    qsort(edad, sizeEdad, sizeof(int), cmpfunc);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTiempo Insumido (Quick Sort qsort()) %.2f ms\n",secs*1000);

    //printIntArray(edadOrdenada,sizeEdad);



}
