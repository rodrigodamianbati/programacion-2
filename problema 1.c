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
    Lista *actual;       // Puntero auxiliar para recorrer la lista

    printf("Ingrese números enteros (999 para finalizar):\n");
    scanf("%d", &valor);

    // Bucle de lectura hasta encontrar la condición de fin (999)
    while (valor != 999) {

        // Reserva dinámica de memoria para el nuevo nodo
        nuevoNodo = (Lista *) malloc(sizeof(Lista));
        nuevoNodo->data = valor;
        nuevoNodo->sgte = NULL;

        // Caso 1: Inserción al INICIO.
        // Ocurre si la lista está vacía (*L == NULL) o si el nuevo valor es MAYOR o IGUAL
        // al valor de la cabeza ((*L)->data <= valor). En ambos casos, el nuevo nodo pasa a ser la cabeza.
        if (*L == NULL || (*L)->data <= valor) {
            nuevoNodo->sgte = *L;
            *L = nuevoNodo;
        } else {
            // Caso 2: Inserción en el MEDIO o al FINAL.
            // Ocurre cuando el nuevo valor es MENOR que el primer nodo de la lista.
            //
            // Técnica de inspección "look-ahead" (mirar al de adelante):
            // En lugar de usar dos punteros (actual y anterior), nos paramos en 'actual' e
            // inspeccionamos el nodo SIGUIENTE (actual->sgte) para decidir si avanzar o frenar.
            actual = *L;

            // Avanzamos mientras:
            // 1. Exista un nodo siguiente (actual->sgte != NULL) -> evita desbordamiento de memoria.
            // 2. El dato del nodo siguiente sea MAYOR al nuevo valor -> mantiene el orden descendente.
            // Al salir del bucle, 'actual' queda parado en el nodo EXACTO previo a la inserción.
            while (actual->sgte != NULL && actual->sgte->data > valor) {
                actual = actual->sgte;
            }

            // --- REENGANCHE EN 2 PASOS (¡EL ORDEN ES CRÍTICO!) ---
            //
            // PASO 1 (PRIMERO): Conectar el nuevo nodo con el resto de la lista.
            //     nuevoNodo->sgte = actual->sgte;
            //     ¡MUY IMPORTANTE PARA ESTUDIANTES! Este paso DEBE hacerse primero.
            //     Si hiciéramos 'actual->sgte = nuevoNodo' primero, sobreescribiríamos
            //     la dirección del resto de la lista y PERDERÍAMOS todos los nodos siguientes.
            nuevoNodo->sgte = actual->sgte;

            // PASO 2 (DESPUÉS): Conectar 'actual' con el nuevo nodo.
            //     actual->sgte = nuevoNodo;
            //     Una vez asegurada la referencia al resto de la lista en el paso 1,
            //     recién podemos desviar el puntero de 'actual' hacia nuestro nuevo nodo.
            actual->sgte = nuevoNodo;
        }

        // Lectura del siguiente número
        scanf("%d", &valor);
    }
}

/**
 * Función: contarNegativos
 * ------------------------
 * Recorre la lista enlazada y cuenta la cantidad de elementos cuyos valores son negativos (< 0).
 * 
 * Parámetros:
 * - L: Puntero al inicio de la lista.
 * 
 * Retorna:
 * - Un entero que representa la cantidad de números negativos encontrados en la lista.
 */
int contarNegativos(Lista *L) {
    Lista *actual = L;
    int contador = 0;

    while (actual != NULL) {
        if (actual->data < 0) {
            contador++;
        }
        actual = actual->sgte;
    }

    return contador;
}

/**
 * Función: buscarPosicion
 * -----------------------
 * Busca un número entero X en la lista enlazada y retorna su posición (1-based).
 * Aprovecha que la lista está ordenada descendentemente para cortar la búsqueda
 * en cuanto encuentra un valor menor a X.
 * 
 * Parámetros:
 * - L: Puntero al inicio de la lista.
 * - X: Número entero a buscar.
 * 
 * Retorna:
 * - La posición (1, 2, 3...) donde se encuentra X.
 * - 0 si X no está presente en la lista.
 */
int buscarPosicion(Lista *L, int X) {
    Lista *actual = L;
    int posicion = 1;

    // Dado que la lista está ordenada de mayor a menor,
    // podemos detenernos si actual->data es menor a X.
    while (actual != NULL && actual->data >= X) {
        if (actual->data == X) {
            return posicion;
        }
        posicion++;
        actual = actual->sgte;
    }

    return 0; // Retorna 0 si no se encontró
}

/**
 * Función: eliminarX
 * ------------------
 * Busca un valor X en la lista enlazada y, en caso de existir, lo elimina
 * desconectando el nodo y liberando su memoria.
 * Aprovecha que la lista está ordenada descendentemente.
 * 
 * Parámetros:
 * - L: Puntero doble al inicio de la lista para permitir modificar la cabeza.
 * - X: Valor entero a eliminar.
 * 
 * Retorna:
 * - 1 si la eliminación fue exitosa.
 * - 0 si el elemento X no se encontraba en la lista (no se pudo realizar).
 */
int eliminarX(Lista **L, int X) {
    if (*L == NULL) {
        return 0; // Lista vacía, no se puede eliminar
    }

    Lista *aBorrar;

    // Caso 1: El elemento a eliminar es la cabeza de la lista (primer nodo)
    if ((*L)->data == X) {
        aBorrar = *L;
        *L = (*L)->sgte;
        free(aBorrar);
        return 1;
    }

    // Caso 2: El elemento está en el medio o al final de la lista.
    // Usamos inspección "look-ahead" (mirar el nodo siguiente actual->sgte).
    Lista *actual = *L;

    while (actual->sgte != NULL && actual->sgte->data > X) {
        actual = actual->sgte;
    }

    // Verificamos si el nodo siguiente contiene X
    if (actual->sgte != NULL && actual->sgte->data == X) {
        aBorrar = actual->sgte;
        actual->sgte = aBorrar->sgte; // Reenganche pasando de largo aBorrar
        free(aBorrar);                // Liberación de memoria dinámica
        return 1;
    }

    return 0; // No se encontró el elemento X
}

/**
 * Función: main
 * -------------
 * Punto de entrada principal del programa. Inicializa la lista,
 * solicita la carga de datos y muestra los valores almacenados en pantalla.
 */
int main() {
    Lista *aux; // Puntero auxiliar para recorrer la lista sin perder la referencia al inicio
    int x;

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

    printf("\n\n");

    // Requerimiento 1: Recuperar la cantidad de números negativos que existen en la lista.
    int cantidadNegativos = contarNegativos(inicio);
    printf("Cantidad de números negativos en la lista: %d\n", cantidadNegativos);

    // Requerimiento 2: Dado un número X buscarlo en la lista y retornar su posición.
    printf("\nIngrese un número X para buscar en la lista: ");
    if (scanf("%d", &x) == 1) {
        int pos = buscarPosicion(inicio, x);
        if (pos > 0) {
            printf("El número %d se encuentra en la posición %d.\n", x, pos);
        } else {
            printf("El número %d no se encuentra en la lista.\n", x);
        }
    }

    // Requerimiento 3: Dado un número X eliminarlo de la lista, en caso qué exista.
    printf("\nIngrese un número X para eliminar de la lista: ");
    if (scanf("%d", &x) == 1) {
        if (eliminarX(&inicio, x)) {
            printf("El número %d fue eliminado exitosamente.\n", x);

            printf("Lista actualizada:\n");
            aux = inicio;
            while (aux != NULL) {
                printf("%d ", aux->data);
                aux = aux->sgte;
            }
            printf("\n");
        } else {
            printf("No se pudo realizar la operación: El número %d no existe en la lista.\n", x);
        }
    }

    return 0;
}