#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}


static void insert(int a[], unsigned int i) {
    for (int j = i; j > 0 && goes_before(a[j], a[j-1]); j--) {
        swap(a,j-1,j);
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {

    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */

    unsigned int pivotValue = izq;
    unsigned int j = der;
    unsigned i = izq+1;
    //Compruebo que los elementos en las posiciones i y j esten bien ubicados
    while (i<=j) {
        if (goes_before(a[i], a[pivotValue])) {
            i++;
        } else if (goes_before(a[pivotValue], a[j])) {
            j--;
        } else {
            swap(a, i, j);
            i++;
            j--;
        }
    }
    swap(a, pivotValue, j);
    pivotValue = j;

    return pivotValue;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    int ppiv=0; 
    /*
     *   INVARIANTE:  izq = ppiv < i <= j+1 >= der+1 
     *		 && todos los elementos en a[izq,i-1] son <= que a[ppiv]
     *       && todos los elementos en a [j+1,der] son > que a[ppiv]
     */  
     if (izq < der) {
        //izq<=ppiv<=der
        //Llamo a partition() para obtener el pivote
        ppiv = partition(a, izq, der);
            
        if (ppiv==0) {
            //Si el pivot esta en la primera posicion del arreglo
            quick_sort_rec(a, izq, ppiv);     
        } else {
            //Elementos en a[izq, ppiv-1] <= a[ppiv]
            quick_sort_rec(a, izq, ppiv-1);
        }
        //Elementos en a[ppiv+1, der] >= a[ppiv]
        quick_sort_rec(a, ppiv+1, der);
        }
}


void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}
