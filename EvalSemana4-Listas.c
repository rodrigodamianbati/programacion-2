/*Problema

Una empresa de desarrollo de software va a trabajar en el diseño e implementación de productos para entretenimiento. Estos productos pueden simular una partida de cartas o un juego de mesa donde los jugadores se disponen a jugar respetando su ubicación, de forma análoga a un círculo. Cuando termina el turno de la última persona/jugador, continúa jugando el primer jugador, salvo qué decida retirarse del juego o si el juego funcionara con vidas, estas se hubiesen acabado.
Entre las funcionalidades básicas que se requieren diseñar e implementar se encuentran:
Recorrer la mesa de juego. Se desea mostrar por pantalla información del jugador. En este caso asumimos que está disponible la funcionalidad mostrarJugador qué recibe como paràmetro información de tipo Jugador
Agregar un jugador nuevo (alguien se suma a la mesa de juego).  Para esta primera versión, este nuevo jugador se unirá al último jugador, sin romper el círculo.
Avanzar el turno. Esta funcionalidad permite habilitar al siguiente jugador a jugar.
Eliminar un jugador (alguien pierde la partida o decide salir del juego). Se debe re-organizar la mesa de juego. 

En esta oportunidad te vamos a solicitar qué:
modeles la estructura de datos qué permite modelar la mesa de juego.
diseñes e implementes al menos las funcionalidades A y D del problema.

Forma de trabajo
En equipo máximo 3 integrantes dónde tendrán que poner a prueba los siguientes roles:
Diseñador de Estructuras: responsable de la definición técnica de tipos de datos qué permitan modelar la información del juego. El objetivo para la clase está puesto en la representación de la mesa de juego. 
 Ingeniero de Algoritmos: responsable de la lógica de punteros, el control de flujo y la preservación del sentido de jugabilidad respetando el orden circular.
Analista de Casos de Prueba:  definir los casos que permitan poner a prueba la solución

Entrega parte 1:  24 de Agosto 2026
Mìnimo: 
a) La especificación y una breve descripción de las decisiones qué han tomado para el punto 1 de la consigna
b) La resolución de al menos una de las funcionalidades solicitadas
*/

// Online C Compiler - Build, Compile and Run your C programs online in your favorite browser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tjugador {
    char nombre[10];
    int vidasRestantes;
    struct Tjugador *sgteJugador;
}Jugador;

typedef struct {
    int cantidadJugadores;
    Jugador *primerJugador;    
}Juego;

void mostrarJugador(Jugador *jugador){
    printf("Jugador: %s, Vidas: %d\n", jugador->nombre, jugador->vidasRestantes);
}

void recorrerMesa(Juego juego) {
    Jugador *aux = juego.primerJugador;
    for (int i = 0; i < juego.cantidadJugadores; i++) {
        mostrarJugador(aux);
        aux = aux->sgteJugador;
    }
}

void agregarJugadorNuevo(Juego *juego, const char nombre[], int vidasRestantes) {
    Jugador *nuevo = (Jugador *)malloc(sizeof(Jugador));

    strncpy(nuevo->nombre, nombre, sizeof(nuevo->nombre) - 1);
    nuevo->nombre[sizeof(nuevo->nombre) - 1] = '\0';
    nuevo->vidasRestantes = vidasRestantes;

    if (juego->primerJugador == NULL || juego->cantidadJugadores == 0) {
        nuevo->sgteJugador = nuevo; // Se apunta a sí mismo formando el círculo
        juego->primerJugador = nuevo;
    } else {
        // Buscamos el último jugador (aquel cuyo siguiente es el primer jugador)
        Jugador *aux = juego->primerJugador;
        while (aux->sgteJugador != juego->primerJugador) {
            aux = aux->sgteJugador;
        }
        aux->sgteJugador = nuevo;
        nuevo->sgteJugador = juego->primerJugador;
    }
    
    juego->cantidadJugadores++;
}

void agregarJugadores(Juego *juego) {
    char opcion = 's';
    char nombre[10];
    int vidas;

    while (opcion == 's' || opcion == 'S') {
        printf("\n--- Ingrese datos del jugador ---\n");
        printf("Nombre: ");
        scanf("%9s", nombre);
        printf("Vidas restantes: ");
        scanf("%d", &vidas);

        agregarJugadorNuevo(juego, nombre, vidas);

        printf("¿Desea agregar otro jugador? (s/n): ");
        scanf(" %c", &opcion);
    }
}

void eliminarJugador(Juego *juego, Jugador jugador) {
    if (juego->primerJugador == NULL || juego->cantidadJugadores == 0) {
        printf("No hay jugadores en la mesa para eliminar.\n");
    } else {
        Jugador *actual = juego->primerJugador;
        Jugador *anterior = NULL;

        // Caso 1: Hay un solo jugador en la mesa
        if (actual->sgteJugador == juego->primerJugador) {
            if (strcmp(actual->nombre, jugador.nombre) == 0) {
                free(actual);
                juego->primerJugador = NULL;
                juego->cantidadJugadores = 0;
                printf("Jugador %s eliminado. La mesa quedo vacia.\n", jugador.nombre);
            } else {
                printf("El jugador %s no se encuentra en la mesa.\n", jugador.nombre);
            }
        } 
        // Caso 2: El jugador a eliminar es el primero (y hay más de uno)
        else if (strcmp(actual->nombre, jugador.nombre) == 0) {
            Jugador *ultimo = juego->primerJugador;
            while (ultimo->sgteJugador != juego->primerJugador) {
                ultimo = ultimo->sgteJugador;
            }

            juego->primerJugador = actual->sgteJugador;
            ultimo->sgteJugador = juego->primerJugador;
            free(actual);
            juego->cantidadJugadores--;
            printf("Jugador %s eliminado de la mesa.\n", jugador.nombre);
        } 
        // Caso 3: El jugador a eliminar está en el medio o al final
        else {
            anterior = actual;
            actual = actual->sgteJugador;

            while (actual != juego->primerJugador && strcmp(actual->nombre, jugador.nombre) != 0) {
                anterior = actual;
                actual = actual->sgteJugador;
            }

            if (actual != juego->primerJugador) {
                anterior->sgteJugador = actual->sgteJugador;
                free(actual);
                juego->cantidadJugadores--;
                printf("Jugador %s eliminado de la mesa.\n", jugador.nombre);
            } else {
                printf("El jugador %s no se encuentra en la mesa.\n", jugador.nombre);
            }
        }
    }
}

int main()
{
    printf("Welcome to Online IDE!! Happy Coding :)");
    return 0;
}
