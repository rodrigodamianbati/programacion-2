#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodoA {
    int dato;
    struct nodoA* hizq;
    struct nodoA* hder;
}*Arbol;

/*1. Diseñe e implemente el algoritmo estaVacio(Árbol A) que recibe un árbol binario y
retorna 1 en caso que esté vacío y 0 en otro caso.*/

int estaVacio(Arbol a) {
    int vacio = 0;
    if (a == NULL) {
        vacio = 1;
    }
    return vacio;
}

/*2. Implemente un algoritmo denominado esHoja, que determine si un elemento de un
árbol binario es hoja . Definición: int esHoja(Árbol A).*/
/*EN ESTE CASO NO ESTOY SEGURO SI DECIRLES DE USAR estaVacio(a->hizq) o directamente preguntar por a->hizq == NULL*/
int esHoja(Arbol a) {
    int hoja = 0;
    if (!estaVacio(a) && estaVacio(a->hizq) && estaVacio(a->hder)) {
        hoja = 1;
    }
    return hoja;
}

/*3. Implemente un algoritmo denominado esPadre, que determine si el elemento qué
recibe como parámetro tiene descendientes. Definición: int esPadre(Árbol A).*/

int esPadre(Arbol a){
    int padre = 0;
    if (!estaVacio(a) && (!estaVacio(a->hizq) || !estaVacio(a->hder))) {
        padre = 1;
    }
    return padre;
}

/*4. Utilizando el algoritmo del punto 3, implemente una solución recursiva que permita
contar las hojas de un árbol binario. Definición: int cantHojas(Árbol A);*/

int cantHojas(Arbol a) {
    int cant = 0;
    if (!estaVacio(a)) {
        if (esHoja(a)) {
            cant = 1;
        }  else {
            cant = cantHojas(a->hizq) + cantHojas(a->hder);
        }
    }
    return cant;
}

/*5. Utilizando el algoritmo punto 4, implemente una solución recursiva que permita
contar los nodos que son padres y que tengan los dos hijos presentes. Definición: int
cantPadres(Árbol A)*/
/*creo que puede prestar a un poco de confunsion el enunciado*/
int cantPadres(Arbol a) {
    int cant = 0;
    if (!estaVacio(a)) {
        if (!estaVacio(a->hizq) && !estaVacio(a->hder)) {
            cant = 1;
        }
        cant = cant + cantPadres(a->hizq) + cantPadres(a->hder);
    }
    return cant;
}

/*6. Cambiaría la solución si se desea imprimir las hojas de un árbol binario cuyo valor se
encuentra comprendido en rango dado. void imprimirHojas(Árbol A, int a, int b);*/

void imprimirHojas(Arbol A, int minimo, int maximo) {
    if (!estaVacio(A)) {
        if (esHoja(A) && A->dato >= minimo && A->dato <= maximo) {
            printf("%d ", A->dato);
        }else{
            imprimirHojas(A->hizq, minimo, maximo);
            imprimirHojas(A->hder, minimo, maximo);
        }
    }
}

/*7. Dado un árbol binario y un valor X, determine la cantidad de claves con valor X que
existen en el mismo int cantClaves(Árbol A, int X)*/

int cantClaves(Arbol a, int x) {
    int cant = 0;
    if (!estaVacio(a)) {
        if (a->dato == x) {
            cant = 1;
        }
        cant = cant + cantClaves(a->hizq, x) + cantClaves(a->hder, x);
    }
    return cant;
}



