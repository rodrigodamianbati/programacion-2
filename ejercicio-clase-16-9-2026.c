#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Cada camino desde la raiz hasta una hoja forma una palabra.
   Contar cuantas de esas palabras terminan en la vocal x. */

typedef struct nodoA {
    char dato;
    struct nodoA *hizq;
    struct nodoA *hder;
} *Arbol;


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


// Crear un nodo
Arbol crearNodo(char valor) {

    Arbol nuevo = malloc(sizeof(struct nodoA));

    if (estaVacio(nuevo)) {
        printf("No se pudo reservar memoria.\n");
        exit(EXIT_FAILURE);
    }

    nuevo->dato = valor;
    nuevo->hizq = NULL;
    nuevo->hder = NULL;

    return nuevo;
}


// Recorrido en preorden
void preorden(Arbol A) {

    if (!estaVacio(A)) {

        printf("%c ", A->dato);

        preorden(A->hizq);
        preorden(A->hder);
    }
}


// Recorrido en inorden
void inorden(Arbol A) {

    if (!estaVacio(A)) {

        inorden(A->hizq);

        printf("%c ", A->dato);

        inorden(A->hder);
    }
}


// Recorrido en postorden
void postorden(Arbol A) {

    if (!estaVacio(A)) {

        postorden(A->hizq);
        postorden(A->hder);

        printf("%c ", A->dato);
    }
}


/* La ultima letra de cada palabra esta en una hoja.
   x es la vocal que se desea buscar. */
int cantPalabras(Arbol a, char x) {
    /* Cada llamada tiene su propia variable cantidad, que guarda
       el numero de palabras que terminan en x dentro de su subarbol. */
    int cantidad = 0;

    /* CASO BASE 1: arbol vacio.
       No entra al if, no hace llamadas recursivas y devuelve 0. */
    if (!estaVacio(a)) {
        /* CASO BASE 2: el nodo es una hoja, es decir, termina una palabra.
           Cuenta 1 si su letra coincide con x; si no, cantidad queda en 0.
           En ambos casos se detiene la recursion de esta rama. */
        if (esHoja(a)) {
            if (a->dato == x) {
                cantidad = 1;
            }
        } else {
            /* CASO GENERAL: el nodo tiene al menos un hijo.
               Se resuelve el mismo problema en los subarboles izquierdo
               y derecho, manteniendo la misma vocal x, y se suman sus resultados.
               El nodo actual no se cuenta porque no es el final de una palabra.
               Cada llamada baja un nivel, hasta llegar a una hoja o arbol vacio. */
            cantidad = cantPalabras(a->hizq, x) + cantPalabras(a->hder, x);
        }
    }

    /* Devuelve el resultado a la llamada que la invoco, donde se combina
       con el de la otra rama. La llamada sobre la raiz devuelve el total. */
    return cantidad;
}


/* Repite la lectura hasta recibir una vocal.
   Si no se puede leer, deja '\0' en x. */
void leerVocal(char *x) {
    int repetir = 1;

    while (repetir == 1) {
        printf("Ingrese la vocal x: ");

        if (scanf(" %c", x) == 1) {
            *x = (char)tolower((unsigned char)*x);

            if (*x == 'a' || *x == 'e' || *x == 'i' || *x == 'o' || *x == 'u') {
                repetir = 0;
            } else {
                printf("Debe ingresar una vocal.\n");
            }
        } else {
            printf("No se pudo leer la vocal.\n");
            *x = '\0';
            repetir = 0;
        }
    }
}


void liberarArbol(Arbol a) {
    if (!estaVacio(a)) {
        liberarArbol(a->hizq);
        liberarArbol(a->hder);
        free(a);
    }
}


int main(void) {

    Arbol raiz;
    char x;
    int resultado = 0;

    /* Arbol del enunciado:

                  R
             /         \
            a           o
          /   \       /   \
         m     n     s     t
        / \   / \   / \   / \
       a   o i   e a   e o   a

       Cada una de las ocho hojas termina una palabra.
       Resultados esperados: a = 3, e = 2, i = 1, o = 2, u = 0.
    */

    raiz = crearNodo('R');

    raiz->hizq = crearNodo('a');
    raiz->hder = crearNodo('o');

    raiz->hizq->hizq = crearNodo('m');
    raiz->hizq->hder = crearNodo('n');

    raiz->hder->hizq = crearNodo('s');
    raiz->hder->hder = crearNodo('t');

    raiz->hizq->hizq->hizq = crearNodo('a');
    raiz->hizq->hizq->hder = crearNodo('o');
    raiz->hizq->hder->hizq = crearNodo('i');
    raiz->hizq->hder->hder = crearNodo('e');

    raiz->hder->hizq->hizq = crearNodo('a');
    raiz->hder->hizq->hder = crearNodo('e');
    raiz->hder->hder->hizq = crearNodo('o');
    raiz->hder->hder->hder = crearNodo('a');


    printf("PREORDEN: ");
    preorden(raiz);

    printf("\nINORDEN: ");
    inorden(raiz);

    printf("\nPOSTORDEN: ");
    postorden(raiz);

    printf("\n\n");
    
    leerVocal(&x);

    if (x != '\0') {
        printf("Cantidad de palabras que finalizan en '%c': %d\n",
               x, cantPalabras(raiz, x));
    } else {
        resultado = 1;
    }

    liberarArbol(raiz);

    return resultado;
}
