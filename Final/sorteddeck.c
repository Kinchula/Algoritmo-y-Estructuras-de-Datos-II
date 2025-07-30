#include "sorteddeck.h"
#include "card.h"
#include "card_helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <assert.h>

struct s_sdeck {
    unsigned int size;
    unsigned int cred;
    unsigned int cblack;
    struct s_node *first;
};

struct s_node {
    card c;
    cardcolor_t color;
    struct s_node *next;
};

typedef struct s_node * node_t;

static node_t create_node(card c) {
    node_t new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->c = c;
    new_node->color = card_color(c);
    new_node->next = NULL;
    return new_node;
}

static node_t destroy_node(node_t node) {
    assert(node!=NULL);
    node->c = card_destroy(node->c);
    free(node);
    node = NULL;
    assert(node==NULL);
    return node;
}


static bool invrep(sdeck deck) {
    bool valid = true;
    //bool match_color = true;
    unsigned int c_red = 0u;
    unsigned int c_black = 0u;
    unsigned int c_size = 0u;
    node_t aux;
    aux = deck->first;
    while (aux!=NULL) {
        //Contadores
        if (aux->color == red) {
            c_red += 1;
        } else {
            c_black += 1;
        }
        c_size += 1;
        aux = aux->next;
    }
    valid = valid && c_red == deck->cred && c_black == deck->cblack && deck->size == c_size;
    return valid;
}


sdeck sorteddeck_create(void) {
    sdeck new_deck = NULL;
    new_deck = malloc(sizeof(struct s_sdeck));
    assert(new_deck!=NULL);
    new_deck->size = 0u;
    new_deck->cred = 0u;
    new_deck->cblack = 0u;
    new_deck->first = NULL;
    assert(invrep(new_deck));
    return new_deck;
 }

sdeck sorteddeck_destroy(sdeck deck) {
    assert(deck!=NULL);
    node_t kill_node = NULL;
    while (deck->first!=NULL) {
        kill_node = deck->first;
        deck->first = deck->first->next;
        kill_node = destroy_node(kill_node);
    };
    free(deck);
    deck = NULL;
    assert(deck==NULL);
    return deck;
}

sdeck sorteddeck_add(sdeck deck, card c) {
    assert(invrep(deck));
    node_t new_node = create_node(c);
    //El mazo es vacío, la agrego al principio
    if (deck->first == NULL) {
        deck->first = new_node;
    } else {
        //El mazo no es vacío.
        //Primero debo verificar de que color es la primera carta
        if (new_node->color == deck->first->color) {
            //El nuevo nodo tiene el mismo colo que la primera carta del mazo
            new_node->next = deck->first;
            deck->first = new_node;
        } else {
            //Sus colores no son iguales
            //Recorro el mazo hasta encontrar una carta con el mismo color
            // O en su defecto, hasta que finalize el mismo
            node_t aux = deck->first;
            while (aux->next!=NULL && (aux->next->color != new_node->color)) {
                aux = aux->next;
            };
            if (aux->next==NULL) {
                //Si se llego al final y no se encontro ninguna carta con el mismo color
                aux->next = new_node;
            } else {
                //Se llego a una carta que tiene el mismo color
                new_node->next = aux->next;
                aux->next = new_node;
            };
        };
    };
    //Incremento los contadores
    if (new_node->color==red) {
        deck->cred += 1;
    } else {
        deck->cblack += 1;
    };
    deck->size += 1;
    assert(invrep(deck) && !sorteddeck_is_empty(deck));
    return deck;
}

sdeck sorteddeck_remove(sdeck deck, card c) {
    assert(invrep(deck));
    node_t aux;
    aux = deck->first;
    if (card_color(c) == aux->color && card_number(c) == card_number(aux->c)) {
        //Si la primera carta coincide, la elimino
        deck->first = deck->first->next;
        aux = destroy_node(aux);
    } else {
        //Si no es la primera, busco en el mazo
        bool b = true;
        node_t prev = deck->first;
        while (b && aux!=NULL) {
            aux = aux->next; 
            if (card_color(c) == aux->color && card_number(c) == card_number(aux->c)) {
                prev->next = aux->next;
                aux = destroy_node(aux);
                b = false;
            }
            prev->next = aux;
            aux = aux->next;
        };
    };
    if (card_color(c) == red) {
        deck->cred -=1;
    } else {
        deck->cblack -= 1;
    };
    deck->size -= 1;
    assert(invrep(deck));
    return deck;
}

sdeck sorteddeck_popfirst(sdeck deck) {
    assert(deck!=NULL && invrep(deck));
    node_t aux = NULL;
    aux = deck->first;
    deck->first = deck->first->next;
    //Disminuyo el contador
    if (aux->color == red) {
        deck->cred -= 1;
    } else {
        deck->cblack -= 1;
    }
    deck->size -= 1;
    aux = destroy_node(aux); //Destruyo el nodo, liberando memoria dinámica
    assert(invrep(deck));
    return deck;
}

card sorteddeck_first(sdeck deck) {
    assert(deck!=NULL && invrep(deck));
    return deck->first->c;
}

unsigned int sorteddeck_size(sdeck deck) {
    assert(invrep(deck));
    return deck->size;
}

unsigned int sorteddeck_redcount(sdeck deck) {
    assert(invrep(deck));
    return deck->cred;
}

unsigned int sorteddeck_blackcount(sdeck deck) {
    assert(invrep(deck));
    return deck->cblack;
}

bool sorteddeck_is_empty(sdeck deck) {
    assert(invrep(deck));
    return (deck->first==NULL) ? true : false;
}


card* sorteddeck_to_array(sdeck deck) {
    assert(invrep(deck));
    card *array = NULL;
    unsigned int length = deck->size;
    array = calloc(sizeof(card), length);
    node_t aux = deck->first;
    for (unsigned i = 0; i < deck->size; i++)
    {
        array[i] = aux->c;
        aux = aux->next;
    };
    return array;
}

void sorteddeck_dump(sdeck deck) {
    assert(invrep(deck));
    node_t node = deck->first;
    if (node != NULL) {
        card_dump(node->c);
        while (node->next != NULL) {
            printf(" -> ");
            node = node->next;
            card_dump(node->c);
        }
        printf("\n");
    } else {
        printf("<>\n");
    }
}

