#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


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

