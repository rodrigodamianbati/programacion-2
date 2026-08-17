#include <stdio.h>

typedef struct regNodo{
 int data;
 struct regNodo * next;
} Nodo;

Nodo * HEAD;

int longitud(Nodo *HEAD) {
    Nodo *aux = HEAD;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->next;
    }

    return contador;
}

int main(void) {
    Nodo nodo1 = {10, NULL};
    Nodo nodo2 = {20, NULL};
    Nodo nodo3 = {30, NULL};

    nodo1.next = &nodo2;
    nodo2.next = &nodo3;
    HEAD = &nodo1;

    printf("La longitud de la lista es: %d\n", longitud(HEAD));

    return 0;
}
