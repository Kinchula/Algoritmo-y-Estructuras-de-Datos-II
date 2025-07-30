#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node {
	list_elem elem;
	struct node *next;
};

/*Constructors*/
list empty(void) {
	list l = NULL;
	return l;
}

list addl(list_elem e, list l) {
	struct node *k = malloc(sizeof(struct node));
	k->elem = e;
	k->next = l;
	return k;
}

/*Operations*/
bool is_empty(list l) {
	return (l == NULL);
}

list_elem head(list l) {
	assert(!is_empty(l));
	return (l->elem);
}

list tail(list l) {
	assert(!is_empty(l));
	struct node *k;
	k = l->next;
	free(l);
	return k;
}

list addr(list l, list_elem e) {
	struct node *p = malloc(sizeof(struct node));
	p->elem = e;
	p->next = NULL;
	if (l==NULL) {
		return p;
	} else {
		struct node *q;
		q = l;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next	= p;	
	}
	return l;	
}

list copy_list(list l) {
	list k = empty();
	struct node *p = l;
	while (p != NULL) {
		k = addl(p->elem, k);
		p = p->next;
	}
	return k;
}

unsigned int length(list l) {
	struct node *p = copy_list(l);
	unsigned int n = 0u;
	if (p == NULL) {
		n = 0u;
	} else {
		while (p != NULL) {
			p = tail(p);
			++n;
		}
	}
	return n;
}

list concat(list l1, list l2) {
	struct node *p = l1;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = l2;
	return l1;
}

list_elem index(list l, unsigned int n) {
	assert(length(l) >= n);
	struct node *p = l;
	unsigned int m = 1u;
	while (m < n) {
			p = p->next;
			++m;
		}
	return (p->elem);
}

list take(list l, unsigned int n) {
	list k = empty();
	list p = l;
	unsigned int m = 0u;	
	while (m<=n && l!=NULL) {
		k = addr(k, head(p));
		p = tail(p);
		++m;
	}
	destroy(p);
	destroy(l);
	return k;
}

list drop(list l, unsigned int n) {
	list k = l;
	unsigned int m = 0u;
	while (m<n && l!=NULL) {
		k = tail(k);
		++m;
	}
	destroy(l);
	return k;
}

/*Destroy*/
list destroy(list l) {
	for (unsigned int i = 0u; i<length(l); ++i) {
		l = tail(l);
	}	
	return l;
}
