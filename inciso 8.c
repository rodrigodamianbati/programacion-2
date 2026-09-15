#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoA {
    int dato;
    struct nodoA* hizq;
    struct nodoA* hder;
}*Arbol;

int estaVacio(Arbol a) {
    int vacio = 0;
    if (a == NULL) {
        vacio = 1;
    }
    return vacio;
}

/*8. Diseñe e implemente en C un módulo llamado igualesAB, que determine si dos
árboles binarios que almacenan números enteros son iguales, es decir, si tienen la
misma forma y contenido. Realice una versión recursiva e iterativa. Defina los tipos
necesarios para resolver el problema.*/

int igualesABRecursiva(Arbol a, Arbol b)
{
    int iguales;

    if (estaVacio(a) && estaVacio(b)) {
        iguales = 1;
    } else if (estaVacio(a) || estaVacio(b)) {
        iguales = 0;
    } else if (a->dato != b->dato) {
        iguales = 0;
    } else {
        iguales = igualesABRecursiva(a->hizq, b->hizq);

        if (iguales == 1) {
            iguales = igualesABRecursiva(a->hder, b->hder);
        }
    }

    return iguales;
}

/* Cada elemento de la pila guarda dos nodos de la misma posicion. */
typedef struct nodoPar {
    Arbol a;
    Arbol b;
    struct nodoPar* sig;
}*PilaPares;

static void liberarPilaPares(PilaPares* pila) {
    PilaPares aux;
    while (*pila != NULL) {
        aux = *pila;
        *pila = aux->sig;
        free(aux);
    }
}

static void apilarPar(PilaPares* pila, Arbol a, Arbol b) {
    PilaPares nuevo = malloc(sizeof *nuevo);
    nuevo->a = a;
    nuevo->b = b;
    nuevo->sig = *pila;
    *pila = nuevo;
}

/* Se utiliza solamente cuando la pila tiene elementos. */
static void desapilarPar(PilaPares* pila, Arbol* a, Arbol* b) {
    PilaPares aux = *pila;
    *a = aux->a;
    *b = aux->b;
    *pila = aux->sig;
    free(aux);
}

int igualesABIterativa(Arbol a, Arbol b) {
    int iguales = 1;
    PilaPares pila = NULL;

    apilarPar(&pila, a, b);

    while (pila != NULL && iguales == 1) {
        desapilarPar(&pila, &a, &b);

        if (estaVacio(a) && estaVacio(b)) {
            iguales = 1;
        } else if (estaVacio(a) || estaVacio(b)) {
            iguales = 0;
        } else if (a->dato != b->dato) {
            iguales = 0;
        } else {
            /* Se apila derecha primero para comparar izquierda primero. */
            apilarPar(&pila, a->hder, b->hder);
            apilarPar(&pila, a->hizq, b->hizq);
        }
    }

    liberarPilaPares(&pila);
    return iguales;
}