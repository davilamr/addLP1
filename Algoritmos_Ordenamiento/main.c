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

    int arrayOrdenado[MAX];
    int array[MAX];
    int arrayAuxiliar[MAX];

    struct timeval start, stop;
    double secs = 0;
    int cantidadTest;


    fillFromFile(arrayAuxiliar, MAX);


    printf("\n\nsortQty,NadiaSort,NadiaIISort,BubleSort,BubleSortII,InsertionSort,QuickSort,QuickSort()\n");
    for(cantidadTest = 10000; cantidadTest < MAX; cantidadTest = cantidadTest + 10000)
    {

        printf("%d,",cantidadTest);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        nadiaSort(array,cantidadTest,arrayOrdenado);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Nadia Sort) %.2f ms",secs*1000);
        printf("%.0f,",secs*1000*1000);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        nadiaSort2(array,cantidadTest);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Nadia II Sort) %.2f ms",secs*1000);
        printf("%.0f,",secs*1000*1000);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        bubleSort(array,cantidadTest);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Buble Sort) %.2f ms",secs*1000);
        printf("%.0f,",secs*1000*1000);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        bubleSort2(array,cantidadTest);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Buble Sort II) %.2f ms",secs*1000);
        printf("%.0f,",secs*1000*1000);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        insertionSort(array,cantidadTest);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Insertion Sort) %.2f ms",secs*1000);
        printf("%.0f,",secs*1000*1000);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        quickSort(array,cantidadTest);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Quick Sort) %.2f ms",secs*1000);
        printf("%.0f,",secs*1000*1000);

        memcpy(array,arrayAuxiliar, sizeof(int) * cantidadTest);
        gettimeofday(&start, NULL);
        qsort(array,cantidadTest, sizeof(int), cmpfunc);
        gettimeofday(&stop, NULL);
        secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
        //printf("\nTiempo Insumido (Quick Sort qsort()) %.2f ms\n",secs*1000);
        printf("%.0f\n",secs*1000*1000);
    }
    //printIntArray(edadOrdenada,sizeEdad);



}
