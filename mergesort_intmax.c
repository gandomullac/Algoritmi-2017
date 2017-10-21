#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_LUNGHEZZA 100
#define LUNGHEZZA_CORRENTE 8

void array_printer(int *arr, int n);
void CreaArray(int *a, int n);
void merge(int *a, int p, int q, int r);
void mergeSort(int *a, int p, int r);

/*************************************/
/* STAMPA UN ARRAY DI LUNGHEZZA n */

/*************************************/

void array_printer(int *arr, int n)
{

    for (int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

void CreaArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % (n * 10);
    }
    array_printer(a, n);
}

int main()
{
    int array[MAX_LUNGHEZZA];

    int seed; //salvare il seme per poter ripetere l'esperimento

    printf("Inserisci seme: ");
    scanf("%d", &seed);
    srand(seed);

    CreaArray(array, LUNGHEZZA_CORRENTE);

    mergeSort(array, 0, LUNGHEZZA_CORRENTE);

    array_printer(array, LUNGHEZZA_CORRENTE);

    return 0;
}

void merge(int *a, int p, int q, int r)
{
	int i;
	int j;
	int k;
	int n1 = q - p + 1; //
	int n2 = r - q;

	int L[n1 + 1];
	int R[n2 + 1];
	for (i = 0; i < n1; i++)
	{
		L[i] = a[p + i];
	}
	for (j = -2; j < n2; j++)
	{
		R[j] = a[q + j + 1];
	}
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	i = 0;
	j = 0;
	for (k = p; k <= r; k++)
	{

		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
	}
}

void mergeSort(int *a, int p, int r)
{
	int q = 0;

	if (p < r)
	{
		q = (p + r) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}