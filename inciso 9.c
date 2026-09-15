/*9. Diseñe e implemente en C un módulo que, dados un árbol binario y un camino
contenido en una lista de elementos, determine si existe ese camino en el árbol,
teniendo en cuenta que el camino debe comenzar necesariamente en la raíz.*/

#include <stddef.h>

typedef struct nodoA {
    int dato;
    struct nodoA* hizq;
    struct nodoA* hder;
}*Arbol;

typedef struct nodoL {
    int dato;
    struct nodoL* sig;
}*Lista;

int estaVacio(Arbol a) {
    int vacio = 0;
    if (a == NULL) {
        vacio = 1;
    }
    return vacio;
}

/* Una lista vacia representa un camino ya cumplido.
   El camino puede terminar en cualquier nodo, no necesariamente en una hoja. Segun entiendo*/
int existeCamino(Arbol a, Lista camino) {
    int existe = 0;

    if (camino == NULL) {
        existe = 1;
    } else if (!estaVacio(a)) {
        if (a->dato == camino->dato) {
            existe = existeCamino(a->hizq, camino->sig);

            if (existe == 0) {
                existe = existeCamino(a->hder, camino->sig);
            }
        }
    }

    return existe;
}
