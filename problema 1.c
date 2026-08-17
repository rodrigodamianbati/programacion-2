#include <stdio.h>
#include <stdlib.h>
/*
Problema 1. Diseñar e implementar en C un programa modularizado que lea una secuencia
de números enteros hasta leer el valor 999, el cuál no debe procesarse. Cada número leído
debe almacenarse en una Lista Enlazada de manera tal que los mismos siempre queden
ordenados de forma descendente. Al finalizar el proceso de lectura, el programa deberá
permitir resolver los siguientes requerimientos:
● Recuperar la cantidad de números negativos que existen en la lista.
● Dado un número X buscarlo en la lista y retornar su posición. El primer elemento
ocupa la posición 1.
● Dado un número X eliminarlo de la lista, en caso qué exista. Indicar si la operación se
pudo realizar o no.
*/

// Estructura que define un nodo de la lista simplemente enlazada.
// Contiene un valor entero (data) y un puntero al siguiente nodo (sgte).
typedef struct regNodo {
    int data;               // Almacena el número entero ingresado por el usuario
    struct regNodo * sgte;  // Puntero al siguiente nodo en la lista enlazada
} Lista;

// Puntero global al primer nodo de la lista (cabeza de la lista).
Lista * inicio;

/**
 * Función: leerValores
 * --------------------
 * Lee números enteros por teclado hasta ingresar el valor 999 (bandera de corte).
 * Inserta cada número en la lista enlazada manteniendo un orden descendente (mayor a menor).
 * 
 * Parámetros:
 * - L: Puntero doble al inicio de la lista para permitir modificar la cabeza de la misma.
 */
void leerValores(Lista **L) {
    int valor;           // Variable para almacenar temporalmente el número ingresado
    Lista *nuevoNodo;    // Puntero para crear y alojar en memoria el nuevo nodo
    Lista *actual;       // Puntero auxiliar para recorrer la lista buscando la posición de inserción
    Lista *anterior;     // Puntero auxiliar para recordar el nodo previo a 'actual'

    printf("Ingrese números enteros (999 para finalizar):\n");
    scanf("%d", &valor);

    // Bucle de lectura hasta encontrar la condición de fin (999)
    while (valor != 999) {

        // Reserva dinámica de memoria para el nuevo nodo
        nuevoNodo = (Lista *) malloc(sizeof(Lista));
        nuevoNodo->data = valor; // Asignación del dato
        nuevoNodo->sgte = NULL;  // Inicialización del puntero al siguiente nodo

        // Caso 1: La lista está completamente vacía (*L es NULL).
        // El nuevo nodo pasa a ser directamente la cabeza (inicio) de la lista.
        if (*L == NULL) {
            *L = nuevoNodo;
        } else {
            // Caso 2: La lista YA contiene elementos.
            // Para mantener el orden descendente (de mayor a menor), debemos encontrar la
            // posición correcta usando dos punteros auxiliares:
            //  - 'actual': Explora los nodos de la lista para comparar sus valores.
            //  - 'anterior': Conserva la referencia del nodo previo a 'actual'.
            actual = *L;
            anterior = NULL;

            // Recorremos la lista mientras el elemento actual sea MAYOR que el valor ingresado.
            // El bucle se detiene cuando:
            //  a) 'actual' es NULL -> llegamos al final (el valor ingresado es el menor de todos).
            //  b) 'actual->data <= valor' -> encontramos el lugar exacto antes de un número menor/igual.
            while (actual != NULL && actual->data > valor) {
                anterior = actual;
                actual = actual->sgte;
            }

            // --- ¿DÓNDE Y CÓMO SE REALIZA LA INSERCIÓN? ---

            // Subcaso 2.A: Inserción al PRINCIPIO de la lista.
            // Ocurre cuando 'anterior' sigue siendo NULL (el bucle while no dio ninguna vuelta).
            // Esto significa que 'valor' es MAYOR que el primer elemento existente (*L).
            if (anterior == NULL) {
                nuevoNodo->sgte = *L; // El nuevo nodo se enlaza al que era el primer nodo
                *L = nuevoNodo;        // La cabeza de la lista (*L) pasa a ser el nuevo nodo
            } 
            // Subcaso 2.B: Inserción en el MEDIO o al FINAL de la lista.
            // Ocurre cuando 'anterior' avanzó al menos una posición (no es NULL).
            // El nuevo nodo debe ubicarse justo DESPUÉS de 'anterior' y ANTES de 'actual'.
            else {
                anterior->sgte = nuevoNodo; // 'anterior' ahora se enlaza con el nuevo nodo
                nuevoNodo->sgte = actual;   // 'nuevoNodo' apunta a 'actual' (o a NULL si es al final)
            }
        }

        // Lectura del siguiente número
        scanf("%d", &valor);
    }
}

/**
 * Función: main
 * -------------
 * Punto de entrada principal del programa. Inicializa la lista,
 * solicita la carga de datos y muestra los valores almacenados en pantalla.
 */
int main() {
    Lista *aux; // Puntero auxiliar para recorrer la lista sin perder la referencia al inicio

    inicio = NULL; // Inicialización del puntero global inicio a NULL (lista vacía)

    // Carga ordenada de valores en la lista
    leerValores(&inicio);

    printf("\nLista ordenada de forma descendente:\n");

    // Recorrido e impresión de los elementos de la lista enlazada
    aux = inicio;

    while (aux != NULL) {
        printf("%d ", aux->data);
        aux = aux->sgte; // Avanzar al siguiente nodo
    }

    printf("\n");

    return 0;
}