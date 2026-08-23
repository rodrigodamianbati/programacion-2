#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Problema 2. Se dispone de una lista de canciones de una plataforma de música. De cada
canción se conoce su nombre, banda o artista, duración y cantidad de reproducciones durante
el último mes. Diseñar e implementar un programa en C que permita realizar lo siguiente:
a. obtener la información de la canción más larga;
b. obtener el TOP 3 y TOP 5 de canciones más escuchadas;
c. obtener todas las canciones del artista Duki.
d. mostrar los nombres de las bandas o artistas que solo son de una palabra.
 */

// Estructura que representa una Canción con cadenas dinámicas
typedef struct {
    char *nombre;              // Puntero a la cadena del nombre (memoria en Heap)
    char *artista;             // Puntero a la cadena del artista (memoria en Heap)
    int duracion;              // Duración de la canción en segundos
    int reproduccionesUltMes;  // Cantidad de reproducciones en el último mes
} Cancion;

// Estructura para el nodo de la lista simplemente enlazada
typedef struct cancionNodo {
    Cancion data;              // Información de la canción
    struct cancionNodo *sgte;  // Puntero al siguiente nodo
} ListaCanciones;

/**
 * Procedimiento: cargarCanciones
 * ------------------------------
 * Lee canciones por teclado hasta que el usuario decida no continuar.
 * Reserva memoria dinámica para cada nodo y para cada cadena (nombre y artista),
 * insertando los nuevos nodos al inicio de la lista.
 * 
 * Parámetros:
 * - L: Puntero doble a la cabeza de la lista para modificarla por referencia.
 */
void cargarCanciones(ListaCanciones **L) {
    // Búferes temporales en Stack para capturar la entrada del teclado
    char bufferNombre[100];
    char bufferArtista[100];
    int duracion, reproducciones;
    char opcion;
    ListaCanciones *nuevoNodo;

    printf("¿Desea agregar canciones a la lista? (s/n): ");
    scanf(" %c", &opcion); // El espacio inicial descarta saltos de línea anteriores

    while (opcion == 's' || opcion == 'S') {
        // %99[^\n] lee texto con espacios hasta que se presiona Enter
        printf("\nNombre de la cancion: ");
        scanf(" %99[^\n]", bufferNombre);

        printf("Artista: ");
        scanf(" %99[^\n]", bufferArtista);

        printf("Duracion (segundos): ");
        scanf("%d", &duracion);

        printf("Reproducciones: ");
        scanf("%d", &reproducciones);

        // 1. Reserva de memoria dinámica para el nuevo nodo en Heap
        nuevoNodo = (ListaCanciones *) malloc(sizeof(ListaCanciones));

        // 2. Reserva de memoria exacta para las cadenas (strlen + 1 por el '\0')
        nuevoNodo->data.nombre = (char *) malloc((strlen(bufferNombre) + 1) * sizeof(char));
        strcpy(nuevoNodo->data.nombre, bufferNombre);

        nuevoNodo->data.artista = (char *) malloc((strlen(bufferArtista) + 1) * sizeof(char));
        strcpy(nuevoNodo->data.artista, bufferArtista);

        // 3. Asignación de datos numéricos
        nuevoNodo->data.duracion = duracion;
        nuevoNodo->data.reproduccionesUltMes = reproducciones;

        // 4. Inserción al inicio de la lista
        nuevoNodo->sgte = *L;
        *L = nuevoNodo;

        printf("\n¿Desea agregar otra cancion? (s/n): ");
        scanf(" %c", &opcion);
    }
}

/**
 * Procedimiento: mostrarCanciones
 * ------------------------------
 * Recorre la lista de canciones e imprime en consola los datos
 * de cada nodo para verificar que los datos se almacenaron correctamente.
 * 
 * Parámetros:
 * - L: Puntero al inicio de la lista (paso por valor).
 */
void mostrarCanciones(ListaCanciones *L) {
    ListaCanciones *actual = L;
    int i = 1;

    if (actual == NULL) {
        printf("La lista esta vacia.\n");
    } else {
        printf("\n========== LISTA DE CANCIONES ==========\n");
        while (actual != NULL) {
            printf("[%d] %s - %s | %ds | %d reps\n",
                   i++,
                   actual->data.nombre,
                   actual->data.artista,
                   actual->data.duracion,
                   actual->data.reproduccionesUltMes);
            actual = actual->sgte; // Avanzar al siguiente nodo
        }
        printf("=========================================\n");
    }
}

/*a. obtener la información de la canción más larga;*/
void cancionMasLarga(ListaCanciones *L){
     Cancion
}

/*b. obtener el TOP 3 y TOP 5 de canciones más escuchadas;*/
void top5(ListaCanciones *L){
    
}

void top3(ListaCanciones *L){

}
/*c. obtener todas las canciones del artista Duki.*/
void buscarArtista(ListaCanciones *L){
    
}
/*d. mostrar los nombres de las bandas o artistas que solo son de una palabra.*/
void artistaUnicaPalabra(ListaCanciones *L){
    
}

void mostrarCancion(Cancion c){
    printf("%s - %s | %ds | %d reps\n", c.nombre, c.artista, c.duracion, c.reproduccionesUltMes);
}


/**
 * Función: main
 * -------------
 * Punto de entrada principal. Inicializa la lista localmente,
 * realiza la carga de canciones e imprime el resultado.
 */
int main() {
    ListaCanciones *lista = NULL; // Puntero local a la cabeza de la lista

    printf("--- SISTEMA DE GESTION DE CANCIONES ---\n\n");

    // Carga de canciones por referencia
    cargarCanciones(&lista);

    // Impresión de la lista resultante
    mostrarCanciones(lista);

    return 0;
}
