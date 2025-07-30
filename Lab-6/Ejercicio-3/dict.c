#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    if (d == NULL) {
        return true;
    } else {
        //Aseguro que se cumpla el órden alfabetico en el diccionario comparando las claves(key's)
        //Utilizo recurrsion para recorrer los nodos que están a la izq y los que están a la der
        if (d->left != NULL) {
            assert(key_less(d->left->key, d->key));
            assert(invrep(d->left));
        }
        if (d->right != NULL) {
            assert(!key_less(d->right->key, d->key));
            assert(invrep(d->right));
        }
    }
    return true;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    return dict;
}


dict_t create_node(key_t word, value_t def) {
    dict_t node = malloc(sizeof(struct _node_t));
    node->key = word;
    node->value = def;
    node->left = NULL;
    node->right = NULL;
    return node;
}


dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict==NULL) {
        //Si el diccionario es vacio, creo un nuevo nodo con la palabra y su definición
        create_node(word, def);
    } else {
        dict_t pNode = dict;
        bool bl = key_less(dict->key, word);
        // 
        if (!bl && dict->left == NULL) {
            //La palabra es menor a la raiz actual y el subárbol izq es NULL
            pNode->left = create_node(word, def);
        } else if (bl && dict->right == NULL) {
            //la palabra es mayor a la raíz actual y el subárbol der es NULL
            pNode->right = create_node(word, def);
        } else {
            if (bl) {
                //Apunto al siguiente nodo del subárbol der
                pNode = pNode->right;
            } else {
                //Apunto al siguiente nodo del subárbol izq
                pNode = pNode->left;
            }
            //LLamada recursiva
            pNode = dict_add(pNode, word, def);
        }
    }
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def = NULL;
    if (dict_exists(dict, word)) {
        dict_t pSearch=dict;
        while (!key_eq(pSearch->key, word)) {
            if (key_less(word, pSearch->key)) {
                pSearch = pSearch->left;
            } else {
                pSearch = pSearch->right;
            }
            def = pSearch->value;
        }
    }
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exists = false;
    assert(invrep);
    if (dict != NULL) {
        exists = (dict->key == word || dict_exists(dict->left, word) || dict_exists(dict->right, word));
    }
    return exists;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    assert(invrep(dict));
    if(dict!=NULL) {
        length = 1u + dict_length(dict->left) + dict_length(dict->right);
    }
    assert(invrep(dict) && (length>0u || dict==NULL));
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    //Caso 1: el diccionario es nulo (dict==NULL) ó la palabra no existe en el diccionario
    if (dict == NULL || !dict_exists(dict, word)) {
        return dict;
    } else if (key_eq(dict->key, word)) {
        //Caso 2: la palabra es la raíz 
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
        return NULL;
    }
    dict_t pNode = dict;
    dict_t pPRev = dict; 
    while (key_eq(pNode->key, word)) {
        if (key_less(pNode->key, word) ) {
            pPRev = pNode;
            pNode = pNode->left;    
        } else {
            pPRev = pNode;
            pNode = pNode->right;
        }
    }
    // Casos 3 y 4
    if (pNode->right!=NULL) {
        /* 
             En caso de que el subárbol derecho del dict no esté vacío, 
             remplazo la palabra eliminada por la menor palabra del subárbol derecho. 
        */
        dict_t repl_node = dict_min(pNode->right);
        pNode->key = repl_node->key;
        pNode->value = repl_node->value;
        pPRev = pNode;
        pNode = pNode->right;
        while (pNode->left!=NULL) {
            pPRev = pNode;
            pNode = pNode->left;
        }
        if (pPrev->right == pNode) {
            pPrev->right = pNode->right;
        } else {
            pPrev->left = pNode->right;
        }
        // Libero el espacio ocupado por el nodo
        free(pNode);
    } else if (pNode->left != NULL) {
        /* 
             En caso de que el subárbol derecho del dict no esté vacío,
             y el subárbol izquierdo tampoco lo esté, 
             remplazo la palabra eliminada por la mayor palabra del subárbol derecho. 
        */
        dict_t repl_node = dict_max(pNode->left);
        pNode->key = repl_node->key;
        pNode->value = repl_node->value;
        pPrev = pNode;
        pNode = pNode->left;
        while (pNode->right != NULL) {
            pPrev = pNode;
            pNode = pNode->right;
         }
         if (pPrev->left == pNode) {
            pPrev->left = pNode->left;
         } else {
            pPrev->right = pNode->left;
         }
         key_destroy(pNode->key);
         value_destroy(pNode->value);
         free(pNode);
    } else  {
        if (key_less(word, pNode->key)) {
            pPrev->left = NULL;
        } else {
            pPrev->right = NULL;
        }
        pNode->key = key_destroy(pNode->key);
        pNode->value = value_destroy(pNode->value);
        free(pNode);
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if (dict != NULL) {
        if (dict->left != NULL) {
            dict->left = dict_remove_all(dict->left);
        }
        if (dict->right != NULL) {
            dict->left = dict_remove_all(dict->right);
        }
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(stdout, ": ");
        value_dump(dict->value, file);
        fprintf(stdout, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict_destroy(dict->left);
        dict_destroy(dict->right);
        key_destroy(dict->key);
        value_destroy(dict->value);
        free(dict);      
    }
    dict = NULL;
    assert(dict == NULL);
    return dict;
}

/*
    Declaro las siguiente funciones auxiliares que serviran para la implementación de la función
    dict_remove();

    La primera función dict_min(), devuelve el nodo que contiene la primera palabra ordenada alfabéticamente en el dict y su definición
    La segunda función dict_max(), devuelve el nodo que contiene la última palabra ordenada alfabéticamente en el dict y definición

*/

dict_t dict_min(dict_t dict) {
    assert(dict!=NULL);
    dict_t pNode = dict;
    while (pNode->left != NULL) {
        pNode = pNode->left;
    }
    dict_t new_node = create_node(pNode->key, pNode->value);
    return new_node;
}

dict_t dict_max(dict_t dict) {
    assert(dict!=NULL);
    dict_t pNode =dict;
    while (pNode->right != NULL) {
        pNode = pNode->right;
    }
    dict_t new_node = create_node(pNode->key, pNode->value);
    return new_node;
}
