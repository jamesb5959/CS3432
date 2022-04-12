#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

void swap(int v[], size_t k)
{
    int temp;
    temp = v[k];
    v[k] = v[k+1];
    v[k+1] = temp;
}

void sort(int v[], size_t n)
{
    size_t i, j;
    for (i = 0; i < n; i+=1) {
        for (j = i - 1; j >= 0 & v[j] > v[j+1]; j-=1) {
	    swap(v,j);
	}
    }
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv)
{

    /*int print;
    size_t i, n;
    int values[1000000];

    if (argc != 3) {
        printf("Usage: %s <n> <pr> where <n> is the number of integers to sort and <pr> is 1 to print and 0 otherwise\n", argv[0]);
	exit(1);
    }
    n = atoi(argv[1]);   
    print = atoi(argv[2]);
    srand(time(0));
    for (i = 0; i < n; i++) {
        values[i] = rand();
        if (print)
            printf("%d\n", values[i]);
    }
    sort(values, n);
    if (print) {
        printf("\nsorted:\n");
        for (i = 0; i < n; i++) 
            printf("%d\n", values[i]);
    }
    else 
        printf("values[0]: %d\n", values[0]);
    return(0);*/
    int j = 0;
    while(j < 5){
        int r = rand();
        int bubble[r];
        for(int i=0;i<r;i++)
        bubble[i]=rand()%100;

        clock_t BS, QS;
        double cpu_time_used;
        double BSTime, QSTime, diff;

        printf("Before sorting \n");
        for(int i = 0 ; i < 5; i++ ) {
        printf("%d ", bubble[i]);
        } 
        BS = clock();
        sort(bubble, 5);
        BS = clock();
        BSTime = ((double)BS)/CLOCKS_PER_SEC;
        printf("\nBubble sort finished: %f \n", BSTime);

        int quick[] = {1,2,3,4,5};
        QS = clock();
        qsort(quick,5, sizeof(int), cmpfunc);
        QS = clock();
        QSTime = ((double)QS)/CLOCKS_PER_SEC;
        printf("Quick sort finished: %f \n", QSTime);

        if(BSTime>QSTime){
            diff = BSTime-QSTime;
            printf("Quick sort was %f faster than Bubble sort \n", diff);
            printf("After sorting \n");
            for(int i = 0 ; i < 5; i++ ) {
                printf("%d ", quick[i]);
            } 
        }
        else if(BSTime<QSTime){
            diff = QSTime-BSTime;
            printf("Bubble sort was %f faster than Quick sort \n", diff);
            printf("After sorting \n");
            for(int i = 0 ; i < 5; i++ ) {
                printf("%d \n   ", bubble[i]);
            } 
        }
        j++;
    }
}