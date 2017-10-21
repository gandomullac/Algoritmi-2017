//define che serve per poter usare la vecchia scanf
//con visual studio 2015
//#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_LUNGHEZZA 21
#define NUM_ESPERIMENTI 1
#define REP_PER_ESPERIMENTO 1
#define SALTO 10

/*Nota: SALTO*NUM_ESPERIMENTI deve essere <= MAX_LUNGHEZZA */

#define K 10 //parametro per la hybrid sort

//creazione di array di int ed element CASUALI di lunghezza n
void CreaArray(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (n * 10);
	}
}

/*************************************/
/* COPIA DI UN ARRAY di INT DI LUNGHEZZA n IN UN ALTRO*/
void CopiaArray(int *a1, int *a2, int n)
{
	for (int i = 0; i < n; i++)
		a2[i] = a1[i];
}
/*************************************/

/*************************************/
/* STAMPA UN ARRAY DI LUNGHEZZA n */
void StampaArray(int *a, int n)
{
	for (int i = 0; i < n - 1; i++)
		printf("%d, ", a[i]);
	printf("%d\n", a[n - 1]);
}
/*************************************/

/*************************************/
/* INSERTION SORT */
void insertionSort(int *a, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int key = a[i];
		int j = i;
		while (j > 0 && key < a[j - 1])
		{
			a[j] = a[j - 1];
			--j;
		}
		a[j] = key;
	}
}

/*insertion_sort tra p e q*/
void insertionSortMod(int *a, int p, int q)
{
	/*for (int i = p; i<q; ++i) {
		int key = a[i];
		int j = i;
		while (j>0 && key<a[j - 1]) {
			a[j] = a[j - 1];
			--j;
		}
		a[j] = key;
	}	*/
}

/* MERGE SORT - prova di correttezza: la i-esima chiamata ordina tra p e r*/

/*soluzione senza int max con unico array di supporto*/
void mergeIndex(int *a, int left, int mid, int right)
{
	int i, j, k = left;
	int n1 = mid - left + 1, n2 = right - mid;
	int A[n1], B[n2];

	for (i = 0; i < n1; i++)
	{
		A[i] = a[left + i];
	}
	for (j = 0; j < n2; j++)
	{
		B[j] = a[mid + 1 + j];
	}

	i = 0; //Inizializzo i contatori
	j = 0;

	while (i < n1 && j < n2)
	{
		if (A[i] <= B[j])
		{
			a[k] = A[i];
			i++;
		}
		else
		{
			a[k] = B[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		a[k] = A[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		a[k] = B[j];
		j++;
		k++;
	}
}

/*soluzione con int max*/
void mergeIntMax(int *A, int p, int q, int r)
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
		L[i] = A[p + i];
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	i = 0;
	j = 0;
	for (k = p; k <= r; k++)
	{

		{
			if (L[i] <= R[j])
			{
				A[k] = L[i];
				i++;
			}
			else
			{
				A[k] = R[j];
				j++;
			}
		}
	}
}

/*merge sort basata su mergeIndex*/
void mergeSortIndex(int *a, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSortIndex(a, p, q);
		mergeSortIndex(a, q + 1, r);
		mergeIndex(a, p, q, r);
	}
}

/*merge sort basata su mergeIntMax*/
void mergeSortIntMax(int *A, int p, int r)
{

	int q = 0;

	if (p < r)
	{
		q = (p + r) / 2;

		mergeSortIntMax(A, p, q);
		mergeSortIntMax(A, q + 1, r);
		mergeIntMax(A, p, q, r);
	}
}

/*soluzione ibrida: merge sort (usa mergeIntMax e insertionSort)*/
void hybridSortIntMax(int *a, int p, int r)
{
	if (r - p <= 10)
	{
		insertionSort(a, r - p);
	}
	else
		mergeSortIntMax(a, p, r);
}

/*soluzione ibrida: merge sort (usa mergeSortIndex ed insertionSort)*/
void hybridSortIndex(int *a, int p, int r)
{
	if (r - p <= 10)
	{
		insertionSort(a, r - p);
	}
	else
		mergeSortIndex(a, p, r);
}

/*merge in place*/
/* http://penguin.ewu.edu/cscd300/Topic/AdvSorting/MergeSorts/InPlace.html */
void mergeInPlace(int *a, int first, int mid, int last)
{
}

/*merge sort usando mergeInPlace */
void inPlaceMergeSort(int *a, int p, int r)
{
}

void Scambia(int *a, int *b)
{
	int l;
	l = *a;
	*a = *b;
	*b = l;
}

/*suddivisione array*/
int standardPartition(int *a, int p, int r)
{

	int x = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (a[j] <= x)
		{
			i = i + 1;
			Scambia(&a[i], &a[j]);
		}
	}
	Scambia(&a[i + 1], &a[r]);
	StampaArray(a, 10);
	return i + 1;
}

/*quick sort base che usa standardPartition*/
void standardQuicksort(int *a, int p, int r)
{
	if (p < r)
	{
		int q = standardPartition(a, p, r);
		standardQuicksort(a, p, q - 1);
		standardQuicksort(a, q + 1, r);
	}
}

/*suddivisione array casuale*/
int randomizedPartition(int *a, int p, int r)
{
	int s;
	do
	{
		s = rand() % 1000;
		printf("%d\n", s);
	} while (s < r && s > p);
	Scambia(&a[s], &a[r]);
	int x = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (a[j] <= x)
		{
			i = i + 1;
			Scambia(&a[i], &a[j]);
		}
	}
	Scambia(&a[i + 1], &a[r]);
	StampaArray(a, 10);
	return i + 1;

	return 0;
}

/*quick sort che usa randomizedPartition*/
void randomizedQuicksort(int *a, int p, int r)
{
	// if(p<r)
	// {
	// 	int q=randomizedPartition(a,p,r);
	// 	randomizedQuicksort(a,p,q-1);
	// 	randomizedQuicksort(a,q+1,r);
	// }
}

void printProgressBar(double percentage)
{
	printf("[");
	int PBWIDTH = 70;
	int pos = PBWIDTH * percentage;
	int value = PBWIDTH - (int)(percentage * PBWIDTH);
	for (int i = 0; i < PBWIDTH; ++i)
	{
		if (i < pos)
			printf("=");
		else if (i == pos)
			printf(">");
		else
			printf(" ");
	}
	printf("] %d %%\r", (100 - value));
	fflush(stdout);
}

int main()
{

	int seed; //salvare il seme per poter ripetere l'esperimento
	int indice_esperimento;
	int indice_ripetizione;
	int lunghezza_corrente = 0; //non ordino fino a max lunghezza ma fino a lunghezza corrente

	double progress;

	clock_t inizio, fine, misurato;
	clock_t totale_insertion_sort = 0;
	clock_t totale_merge_sort_index = 0;
	clock_t totale_merge_sort_int_max = 0;
	clock_t totale_hybrid_sort_int_max = 0;
	clock_t totale_hybrid_sort_index = 0;
	clock_t totale_merge_sort_in_place = 0;
	clock_t totale_standard_quicksort = 0;
	clock_t totale_randomized_quicksort = 0;

	FILE *fp;

	int a[MAX_LUNGHEZZA];
	int temp[MAX_LUNGHEZZA];

	// per rendere l'esperimento ripetibile
	printf("Inserisci seme: ");
	scanf("%d", &seed);
	srand(seed);

	// gestione file dei tempi
	fp = fopen("tempi_ordinamento.txt", "w");
	if (fp == NULL)
	{
		perror("Errore apertura file");
		exit(EXIT_FAILURE);
	}

	printf("Inizio Esperimenti\n");

	for (indice_esperimento = 0; indice_esperimento < NUM_ESPERIMENTI; indice_esperimento++)
	{									  //numero di esperimenti decisi prima in costante
		lunghezza_corrente += SALTO;	  //viene sempre incrementata con salto
		CreaArray(a, lunghezza_corrente); //crea array casuale con "lunghezza_corrente" elementi
		CopiaArray(a, temp, lunghezza_corrente);

		//insertion sort 																				//eseguo Insertion Sort
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			insertionSort(a, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock(); //finisce misurare tempo durata clock inserion sort
		misurato = fine - inizio;
		totale_insertion_sort = misurato;

		//merge sort int max
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{

			mergeSortIntMax(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_merge_sort_int_max += misurato; //tempo totale

		//merge sort index
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			mergeSortIndex(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_merge_sort_index += misurato;

		//hybrid sort int max
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			hybridSortIntMax(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_hybrid_sort_int_max += misurato;

		//hybrid sort index
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			hybridSortIndex(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_hybrid_sort_index += misurato;

		//merge in place
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			inPlaceMergeSort(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_merge_sort_in_place += misurato;

		//standard quicksort
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			StampaArray(a, 10);
			standardQuicksort(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_standard_quicksort += misurato;

		//randomized quicksort
		inizio = clock();
		for (indice_ripetizione = 0; indice_ripetizione < REP_PER_ESPERIMENTO; indice_ripetizione++)
		{
			randomizedQuicksort(a, 0, lunghezza_corrente);
			CopiaArray(temp, a, lunghezza_corrente);
		}
		fine = clock();
		misurato = fine - inizio;
		totale_randomized_quicksort += misurato;

		fprintf(fp, "%d\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu\t%lu \n", lunghezza_corrente, totale_insertion_sort,
				totale_merge_sort_int_max, totale_merge_sort_index, totale_hybrid_sort_int_max,
				totale_hybrid_sort_index, totale_merge_sort_in_place, totale_standard_quicksort, totale_randomized_quicksort);

		progress = (double)indice_esperimento / (NUM_ESPERIMENTI);
		printProgressBar(progress);
	}

	fclose(fp);
	printf("Fine Esperimenti\n");
	return 0;
}
