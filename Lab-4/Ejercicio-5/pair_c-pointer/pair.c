#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "pair.h"

pair_t pair_new(int x, int y) {
	pair_t par = malloc(sizeof(pair_t));
	par->fst = x;
	par->snd = y;

	assert(par!=NULL);

	return par; 
}

int pair_first(pair_t p) {
	assert(p!=NULL);
	return p->fst;
}

int pair_second(pair_t p) {
	assert(p!=NULL);

	return p->snd;
}

pair_t pair_swapped(pair_t p) {
	assert(p!=NULL);
	pair_t q = malloc(sizeof(struct s_pair_t));
	q->fst = p->snd;
	q->snd = p->fst;
	assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p));
	return q;
}

pair_t pair_destroy(pair_t p) {
	free(p);
	return NULL;
}
