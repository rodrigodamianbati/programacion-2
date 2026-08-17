#include <stdio.h>

typedef struct regNodo{
    int data;
    struct regNodo * sgte;
} Lista;

Lista * inicio;

/*a. mostrar. Recibe cómo parámetro L de tipo Lista y muestra por pantalla todos
los números impares qué contiene L.*/

void mostrar(Lista *l){
    Lista *aux = l;
    int impares = 0;

    while(aux != NULL){
        if(aux->data % 2 != 0){
            impares++;
        }
        aux = aux->sgte;
    }
    printf("Cantidad de elementos impares: %d\n", impares);
}

/*b. calcPromedio. Recibe como parámetros L de tipo Lista, calcula y retorna el
promedio de los valores contenidos.*/

float calcPromedio(Lista *L){
    float acumulador = 0;
    float promedio = 0;
    int contador = 0;

    while(L != NULL){
        acumulador += L->data;
        contador++;
        L = L->sgte;
    }

    promedio = acumulador / contador;
    return promedio;
}

/*c. existeX. Recibe como parámetro L de tipo Lista y un entero X, y determina si
X está en la lista, retornando 1 o en otro caso 0.*/

int existeX(Lista *L, int X){
    int existe = 0;
    while(L != NULL && existe == 0){
        if(L->data ==X){
            existe = 1;
        }else {
            L = L->sgte;
        }
    }
    return existe;
}

/*d. buscaX. Recibe como parámetro L de tipo Lista y un entero X, y recupera el
puntero a la posición en la qué se encuentra X*/

Lista* buscaX(Lista *L, int X){
    Lista *punteroAx = NULL;

    while(L != NULL && punteroAx == NULL){
        if(L->data == X){
            punteroAx = L;
        }else{
            L = L->sgte;
        }
    }
    return punteroAx;
}

/*e. getMinimo. Recibe como parámetros L de tipo Lista y recupera el valor del
menor elemento almacenado en L.*/

int getMinimo(Lista *L){
    int minimo = 0;

    while(L != NULL){
        if(L->data < minimo){
            minimo = L->data;
        }
        L = L->sgte;
    }
    return minimo;
}

int main(void) {
    Lista nodo1 = {10, NULL};
    Lista nodo2 = {5, NULL};
    Lista nodo3 = {30, NULL};
    Lista *nodoBuscado1 = NULL;
    Lista *nodoBuscado2 = NULL;

    inicio = &nodo1;
    nodo1.sgte = &nodo2;
    nodo2.sgte = &nodo3;

    mostrar(inicio);
    printf("El promedio de la lista es: %.2f\n", calcPromedio(inicio));

    printf("El valor 5 %s en la lista.\n", existeX(inicio, 5) ? "existe" : "no existe");
    printf("El valor 100 %s en la lista.\n", existeX(inicio, 100) ? "existe" : "no existe");

    nodoBuscado1 = buscaX(inicio, 5);
    printf("El nodo con valor 5 %s encontrado.\n", nodoBuscado1 != NULL ? "fue" : "no fue");
    nodoBuscado2 = buscaX(inicio, 100);
    printf("El nodo con valor 100 %s encontrado.\n", nodoBuscado2 != NULL ? "fue" : "no fue");

    printf("El mínimo de la lista es: %d\n", getMinimo(inicio));
    return 0;
}
