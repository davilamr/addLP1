#include <stdio.h>
#include <stdlib.h>


int compactar(int array[], int size, int indice)
{
    for ( ;indice < size-1; indice++)
        array[indice] = array[indice+1];
    return size - 1;
}

int calcularIndiceMinimo(int array[], int size)
{
    int indice=1;
    int minimo = array[0];
    int indiceMinimo = 0;
    for ( ;indice < size; indice++)
    {
       if(array[indice] < minimo)
       {
           minimo = array[indice];
           indiceMinimo = indice;
       }

    }
    return indiceMinimo;
}

void nadiaSort(int array[], int size,int arrayOrdenado[])
{
    int i;
    int indiceMinimo;
    int sizeInicial = size;
    for(i=0;i<sizeInicial;i++)
    {
        indiceMinimo = calcularIndiceMinimo(array,size);
        arrayOrdenado[i] = array[indiceMinimo];
        size = compactar(array,size,indiceMinimo);
    }

}


void nadiaSort2(int array[], int size)
{
    int i;
    int indiceMinimo;
    int sizeInicial = size;
    int* arrayOrdenado = malloc(sizeof(int) * size);

    for(i=0;i<sizeInicial;i++)
    {
        indiceMinimo = calcularIndiceMinimo(array,size);
        arrayOrdenado[i] = array[indiceMinimo];
        size = compactar(array,size,indiceMinimo);
    }
    memcpy(array,arrayOrdenado, sizeof(int) * size);
    free(arrayOrdenado);

}


void insertionSort(int array[], int size)
{
	int i,j;
	int auxiliar;
	for(i = 1; i < size; i++) {
		auxiliar = array[i];
		j = i;
		while(j > 0 && auxiliar < array[j - 1]) {
			array[j] = array[j - 1];
			j--;
		}
		array[j] = auxiliar;
	}
}

void bubleSort(int array[], int size)
{
	int i,j;
	int auxiliar;
	for(i = 0; i < size - 1; i++)
	{
        for(j = i + 1; j < size; j++)
        {
            if(array[i] > array[j])
            {
                auxiliar = array[i];
                array[i] = array[j];
                array[j] = auxiliar;
            }

		}
	}
}


int fillFromFile(int array[], int maxSize)
{
    FILE* pFile;
    int i=0;
    char auxiliar[50];

    pFile = fopen("/Users/Mauro/Downloads/Algoritmos_Ordenamiento/numbers.csv","r");

    if(pFile != NULL)
        while(!feof(pFile))
        {
            fscanf(pFile,"%[^\n]\n",auxiliar);
            array[i] = atoi(auxiliar);
            i++;
            if(i > maxSize)
                break;
        }

    return i-1;
}

void quickSort(int array[], int size)
{
  int pivot;
  int i, j;
  int auxiliar;

  if (size < 2) return;

  pivot = array[size / 2];

  for (i = 0, j = size - 1; ; i++, j--)
  {
    while (array[i] < pivot) i++;
    while (array[j] > pivot) j--;

    if (i >= j) break;

    auxiliar =  array[i];
    array[i] =  array[j];
    array[j] =  auxiliar;
  }

  quickSort(array, i);
  quickSort(array + i, size - i);
}

void printIntArray(int array[], int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
	    printf("\n%d",array[i]);
	}
	printf("\n");
}
