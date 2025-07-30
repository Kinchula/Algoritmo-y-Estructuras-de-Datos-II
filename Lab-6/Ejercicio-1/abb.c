#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    if (tree == NULL) {
        return true;
    }
    //recorro los subárboles
    if (!abb_is_empty(tree->right)) {
        assert(tree->right->elem >= tree->elem);
    }
    if (!abb_is_empty(tree->left)) {
        assert(tree->left->elem < tree->elem);
    }
    /*
    Para poder verificar que se satisface el invariante en todos los subárboles
    realizo dos llamadas recursivas de la función invrep(), para recorrer los suárboles.
    */
    assert(invrep(tree->left));
    assert(invrep(tree->right));
    return true;
}
/*
    Defino una nueva función que se encargue de crear un nuevo nodo de un árbol
*/
abb create_node(abb_elem e) {
    abb new_node = malloc(sizeof(struct _s_abb));
    new_node->elem = e;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    bool bl = false;
    //Si el árbol es vacio
    if (abb_is_empty(tree)) {
        tree = create_node(e);
    } else {
        //En caso de que el árbol no es vacío
        abb auxTree = tree;
        bl = elem_less(tree->elem, e);
        if (bl && abb_is_empty(tree->right)) {
            //Agrego el elemento nuevo al subárol derecho
            auxTree->right = create_node(e);
        } else if (!bl && abb_is_empty(tree->left)) {
            //Agrego el elemento nuevo al subárol izquierdo
            auxTree->left = create_node(e);
        } else {
            //Sigo recorrido los subárboles hasta encontrar el nodo que sera el "padre" del nuevo nodo
            if (bl) {
                auxTree = auxTree->right;
            } else {
                auxTree = auxTree->left;
            }
        auxTree = abb_add(auxTree, e); //llamada recursiva
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return (tree == NULL);
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if (abb_is_empty(tree)) {
        return exists;
    }
    //Aplicando recursión, exploro los subárboles buscando el elemento
    exists = (e==tree->elem) || abb_exists(tree->left, e) || abb_exists(tree->right, e);
    assert(abb_length(tree)!=0 || !exists);
    return exists;
}

unsigned int abb_length(abb tree) {
    assert(invrep(tree));
    unsigned int length;
    if (abb_is_empty(tree)) {
        length = 0;
    } else {
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    //Caso 1: raíz NULL, el cual no se abarca por el invariante
    //Caso 2y3: si el valor a borrar es mayor/menor al valor actual de la raíz
    if (elem_less(tree->elem, e)) {
        tree->right = abb_remove(tree->right, e);
    } else if (elem_less(e, tree->elem)) {
        tree->left = abb_remove(tree->left, e); 
    } else {
        //Caso 4: si el valor a borrar es igual al valor de la raíz actual
        if (tree->left == NULL && tree->right == NULL && elem_eq(tree->elem, e)) {
            //Si nodo actual no tiene ningun hijo
            free(tree); //Libero el nodo actual
            return NULL;
        } else if (tree->left == NULL || tree->right == NULL) {
            //Si el nodo actual tiene al menos un hijo
            abb tmp;
            if (tree->left == NULL) {
                //Tiene un hijo en el subárbol derecho
                tmp = tree->right;
            } else {
                //Tiene un hijo en el subárbol izquierdo
                tmp = tree->left;
            }
            free(tree); //Libero el nodo actual
            return tmp;
        } else {
            //Si el nodo tiene 2 hijos
            //Busco el subárbol con el valor míninio
            abb auxTree;
            auxTree = tree->right;
            while (auxTree->left != NULL) {
                //Busco en el subárbol derecho el valor mínimo
                auxTree = auxTree->left;
            }
            tree->elem = auxTree->elem;
            tree->right = abb_remove(tree->right, auxTree->elem);
        }
    } 
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb auxTree = tree;
    while (!abb_is_empty(auxTree->right)) {
        auxTree = auxTree->right;
    }
    max_e = auxTree->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb auxTree = tree;
    while (!abb_is_empty(auxTree->left)) {
        auxTree = auxTree->left;
    }
    min_e = auxTree->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));
    if (tree != NULL) {
        // Recorrido: In order
        if (ord == ABB_IN_ORDER) {    
            abb_dump(tree->left, ord);
            printf("%d ", tree->elem);
            abb_dump(tree->right, ord);
        }
        // Recorrido: Pre order
        if (ord == ABB_PRE_ORDER) {
            printf("%d ", tree->elem);
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
        }
        // Recorrido: Post order
        if (ord == ABB_POST_ORDER) {
            abb_dump(tree->left, ord);
            abb_dump(tree->right, ord);
            printf("%d ", tree->elem);
        }
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (!abb_is_empty(tree)) {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
    }
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

