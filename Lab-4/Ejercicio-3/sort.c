/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return x->rank <= y->rank;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

static void swap_players(player_t atp[], unsigned int x, unsigned int y) {
    player_t tmp = atp[x]; /*vatiable temporaria para el swapeo*/
    atp[x] = atp[y];
    atp[y] = tmp;
    
}
static unsigned int partition(player_t atp[], unsigned int izq, unsigned int der) {
    unsigned int pivotValue = izq;
    unsigned int j = der;
    unsigned int i = izq + 1;

    // compruebo que los indices i y j esten bien ubicados
    while(i<=j) {
        if(goes_before(atp[i], atp[pivotValue])) {
            i++;    
        } else if (goes_before(atp[pivotValue], atp[j])) {
            j--;
        } else if (goes_before(atp[pivotValue], atp[i]) && goes_before(atp[j], atp[pivotValue])) {
            swap_players(atp, i, j);
        }
    }
    swap_players(atp, pivotValue, j);
    return j;
}


static void quick_sort_rec(player_t atp[], unsigned int izq, unsigned int der) {
    unsigned int pivotValue;
    pivotValue = partition(atp, izq, der);
    if (izq < pivotValue) {
        quick_sort_rec(atp, izq, pivotValue-1); 
    }
    if (pivotValue < der) {
        quick_sort_rec(atp, pivotValue+1, der);
    }
}


void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length-1);
}

