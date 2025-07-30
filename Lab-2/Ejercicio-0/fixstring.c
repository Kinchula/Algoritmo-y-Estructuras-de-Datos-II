#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length=0u;
    
    for (unsigned int i = 0u; s[i] != '\0'; ++i) {
        length++;
    }
    /*En caso que el tamaño de la cadena sea mayor a la constante definido, aborto*/
    assert(length<=FIXSTRING_MAX); 
    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool eq=true;
    unsigned int i=0u;
    unsigned int j=0u;
    /*Si alguna de las cadenas no cumple con ser de menor o igual tamaño que la constante definida, aborto*/
    assert(fstring_length(s1) <= FIXSTRING_MAX && fstring_length(s2) <= FIXSTRING_MAX);
    /*Compruebo que las cadenas sean iguales, caracter a caracter*/
    while (s1[i]!='\0' && s2[j]!='\0') {
            if (s1[i] == s2[j]) {
                eq = eq && true;
            } else {
                eq = eq && false;
            }
            i++;
            j++;        
        }
    return eq;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool lesseq=true;
    int count1=0, count2=0;
    unsigned int i=0u;
    
    for (i=0; i<=FIXSTRING_MAX && (s1[i]!='\0'||s2[i]!=0) && s1[i]!=s2[i];++i) {
        if (s1[i] <= s2[i]) {
            count1++;
        } else {
            count2++;
        }
    }

    if (count1 > count2){
        lesseq = false;
    }
    return lesseq;
}

