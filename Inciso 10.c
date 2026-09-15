/*10. Un árbol binario AB se dice completo si todos sus nodos tienen dos descendientes,
excepto las hojas. Diseñe e implemente en C una función que dado un árbol binario
retorne verdadero si el árbol es completo y falso en otro caso*/

#include <stddef.h>

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

int esHoja(Arbol a) {
    int hoja = 0;
    if (!estaVacio(a) && estaVacio(a->hizq) && estaVacio(a->hder)) {
        hoja = 1;
    }
    return hoja;
}

/* El arbol vacio se considera completo. */
int esCompleto(Arbol a) {
    int completo;

    if (estaVacio(a) || esHoja(a)) {
        completo = 1;
    } else if (estaVacio(a->hizq) || estaVacio(a->hder)) {
        completo = 0;
    } else {
        completo = esCompleto(a->hizq);

        if (completo == 1) {
            completo = esCompleto(a->hder);
        }
    }

    return completo;
}
