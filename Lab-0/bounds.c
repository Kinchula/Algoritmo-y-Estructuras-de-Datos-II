#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    
    struct bound_data res;//declaración de la variables del tipo abstracto bound_data que utilizare para retornar los resultados
    
    bool m = true, n = true, p = true;
    unsigned int i, k = length + 1;
    
    for (i=0; i<length; i++) {
            
            m = value >= arr[i] && m;
            n = value <= arr[i] && n;
            p = value == arr[i] || p;
            
            //Si el elemento existe en el arreglo, y de manera repetida, que guarde su primera posición
            if (p) {
                    if (k>i) {
                            k=i;
                    }
            }
    }
    //asigno los valores obtenidos en num luego de recorrer el arreglo
    res.is_upperbound = m;
    res.is_lowerbound = n;
    res.exists = p;
    res.where = k;
    
    return res;
}



int main(void) {
    int value, a[ARRAY_SIZE];
    unsigned int k; //j
    
    //Pido al usuario que ingrese uno por uno los elementos del arreglo
    k = 0;
    while (k<ARRAY_SIZE) {
            printf("Ingrese un número entero en la posición %d del arreglo \n", k);
            scanf("%d",&a[k]);
            ++k;    
    }
    
    printf("Ingrese un valor para realizar las comprobaciones necesarias \n");
    scanf("%d", &value);
    struct bound_data result = check_bound(value, a, ARRAY_SIZE); //llamado de la función check_bound()
   
   
   if (result.exists) {
          
          //máximo y por lo tanto, cota sup
          if (result.is_upperbound) {
                  printf("El valor ingresado es el máximo del arreglo, por lo que es una cota superior, y se encuentra en la posición %u \n", result.where);
          }
          //mínimo y por lo tanto, cota inf
          if (result.is_lowerbound) {
                  printf("El valor ingresado es el mínimo del arreglo, por lo que es una cota inferior, y se encuentra en la posición %u \n", result.where);
          }
		/*
		  while (!result.is_upperbound && !result.is_lowerbound) {
		  		  
		  }
        */
          //Cotas superiores e inferioes
   } else {
          printf("El elemento ingresado no existe en el arreglo \n");
   }
   /*
    printf("%d \n", result.is_upperbound);  
    printf("%d \n", result.is_lowerbound);
    printf("%u \n", result.exists);
    printf("%u \n", result.where);
    */
   return EXIT_SUCCESS;
}
