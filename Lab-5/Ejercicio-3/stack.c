#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};


stack stack_empty() {
    return NULL;
}

stack stack_push(stack s, stack_elem e) {
    stack p;
    if (stack_is_empty(s)) {
        p = malloc(sizeof(struct _s_stack));
        p->size = 1;
        p->elems = calloc(1, sizeof(stack_elem));
        p->capacity = 1;
        p->elems[0] = e; 
    } else if ((s->size) == (s->capacity)) {
        p = s;
        p->capacity = (p->capacity) * 2; // Duplico la capacidad acutual
        p->elems = realloc((p->elems), (p->capacity)*sizeof(stack_elem));
        p->size += 1;
        p->elems[(p->size)-1] = e;
    } else {
        p = s;
        p->size += 1;
        p->elems[(p->size)-1] = e; 
    }
    return p;
}


stack stack_pop(stack s) {
    if (s->size <= 1) {
        free(s->elems);
        free(s);
        return NULL;
    }
    s->size -= 1;
    return s;
}

unsigned int stack_size(stack s) {
    return stack_is_empty(s) ? 0 : s->size;
}

stack_elem stack_top(stack s) {
    assert(!stack_is_empty(s));
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s) {
    return (s==NULL);
}

stack_elem *stack_to_array(stack s) {
    stack_elem *arr = calloc(stack_size(s), sizeof(stack_elem));
    
    for (unsigned int i=0u; i<stack_size(s) ; ++i) {
    	arr[i] = s->elems[i] ;
    }
    return arr;
}

stack stack_destroy(stack s) {
    if (stack_is_empty(s)) {
        return NULL;
    }
    free(s->elems);
    free(s);
    return NULL;
}
