/*Problema
Una empresa de desarrollo de software va a trabajar en el diseño e implementación
de productos para entretenimiento. Estos productos pueden simular una partida de
cartas o un juego de mesa donde los jugadores se disponen a jugar respetando su
ubicación, de forma análoga a un círculo. Cuando termina el turno de la última
persona/jugador, continúa jugando el primer jugador, salvo qué decida retirarse del
juego o si el juego funcionara con vidas, estas se hubiesen acabado.
Entre las funcionalidades básicas que se requieren diseñar e implementar se
encuentran:
A. Recorrer la mesa de juego. Se desea mostrar por pantalla información del
jugador. En este caso asumimos que está disponible la funcionalidad
mostrarJugador qué recibe como paràmetro información de tipo Jugador
B. Agregar un jugador nuevo (alguien se suma a la mesa de juego). Para esta
primera versión, este nuevo jugador se unirá al último jugador, sin romper el
círculo.
C. Avanzar el turno. Esta funcionalidad permite habilitar al siguiente jugador a
jugar.
D. Eliminar un jugador (alguien pierde la partida o decide salir del juego). Se
debe re-organizar la mesa de juego.
En esta oportunidad te vamos a solicitar qué:
1) modeles la estructura de datos qué permite modelar la mesa de juego.
2) diseñes e implementes al menos las funcionalidades A y D del problema.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tJugador {
    int nro;
    int puntos;
} jugador;

typedef struct tLisGame {
    jugador dato;
    struct tLisGame *sgte;  
} listaJugadores;

void mostrarJugador(jugador j) {
    printf("Jugador Nro: %d, Puntos: %d\n", j.nro, j.puntos);
}

/*
A. Recorrer la mesa de juego. Se desea mostrar por pantalla información del
jugador. En este caso asumimos que está disponible la funcionalidad
mostrarJugador qué recibe como paràmetro información de tipo Jugador
*/
void recorrerMesa(listaJugadores *primerJugador) {
    if (primerJugador == NULL) {
        printf("La mesa esta vacia.\n");
    } else {
        int turno = 1;
        listaJugadores *aux = primerJugador;

        printf("Turno %d -> ", turno);
        mostrarJugador(aux->dato);

        aux = aux->sgte;
        turno++;

        while (aux != primerJugador) {
            printf("Turno %d -> ", turno);
            mostrarJugador(aux->dato);
            aux = aux->sgte;
            turno++;
        }

        printf("Total de jugadores en la mesa: %d\n", turno - 1);
        printf("Fin de la vuelta. El siguiente turno vuelve a ser: Jugador Nro %d\n", aux->dato.nro);
    }
}

/*
B. Agregar un jugador nuevo (alguien se suma a la mesa de juego). Para esta
primera versión, este nuevo jugador se unirá al último jugador, sin romper el
círculo.
*/
void agregarJugadorNuevo(listaJugadores **primerJugador, int nro, int puntos) {
    listaJugadores *nuevo = (listaJugadores *)malloc(sizeof(listaJugadores));
    nuevo->dato.nro = nro;
    nuevo->dato.puntos = puntos;

    if (*primerJugador == NULL) {
        nuevo->sgte = nuevo; // Se apunta a sí mismo formando el círculo
        *primerJugador = nuevo;
    } else {
        // Buscamos el último jugador (aquel cuyo siguiente es el primero)
        listaJugadores *aux = *primerJugador;
        while (aux->sgte != *primerJugador) {
            aux = aux->sgte;
        }
        aux->sgte = nuevo;
        nuevo->sgte = *primerJugador;
    }
}

void agregarJugadores(listaJugadores **primerJugador) {
    char opcion = 's';
    int nro;
    int puntos;

    while (opcion == 's' || opcion == 'S') {
        printf("\n--- Ingrese datos del jugador ---\n");
        printf("Numero de jugador: ");
        scanf("%d", &nro);
        printf("Puntos: ");
        scanf("%d", &puntos);

        agregarJugadorNuevo(primerJugador, nro, puntos);

        printf("¿Desea agregar otro jugador? (s/n): ");
        scanf(" %c", &opcion);
    }
}

/*
C. Avanzar el turno. Esta funcionalidad permite habilitar al siguiente jugador a
jugar.
*/
void avanzarTurno(listaJugadores **turnoActual) {
    if (*turnoActual != NULL) {
        *turnoActual = (*turnoActual)->sgte;
        printf("Turno avanzado. Ahora juega el jugador Nro: %d\n", (*turnoActual)->dato.nro);
    } else {
        printf("No hay jugadores en la mesa.\n");
    }
}

/*
D. Eliminar un jugador (alguien pierde la partida o decide salir del juego). Se
debe re-organizar la mesa de juego.
*/
void eliminarJugador(listaJugadores **primerJugador, int nro) {
    if (*primerJugador == NULL) {
        printf("No hay jugadores en la mesa para eliminar.\n");
    } else {
        listaJugadores *actual = *primerJugador;
        listaJugadores *anterior = NULL;

        // Caso 1: Hay un solo jugador en la mesa
        if (actual->sgte == *primerJugador) {
            if (actual->dato.nro == nro) {
                free(actual);
                *primerJugador = NULL;
                printf("Jugador %d eliminado. La mesa quedo vacia.\n", nro);
            } else {
                printf("El jugador %d no se encuentra en la mesa.\n", nro);
            }
        } 
        // Caso 2: El jugador a eliminar es el primero (y hay más de uno)
        else if (actual->dato.nro == nro) {
            listaJugadores *ultimo = *primerJugador;
            while (ultimo->sgte != *primerJugador) {
                ultimo = ultimo->sgte;
            }

            *primerJugador = actual->sgte;
            ultimo->sgte = *primerJugador;
            free(actual);
            printf("Jugador %d eliminado de la mesa.\n", nro);
        } 
        // Caso 3: El jugador a eliminar está en el medio o al final
        else {
            anterior = actual;
            actual = actual->sgte;

            while (actual != *primerJugador && actual->dato.nro != nro) {
                anterior = actual;
                actual = actual->sgte;
            }

            if (actual != *primerJugador) {
                anterior->sgte = actual->sgte;
                free(actual);
                printf("Jugador %d eliminado de la mesa.\n", nro);
            } else {
                printf("El jugador %d no se encuentra en la mesa.\n", nro);
            }
        }
    }
}

int main()
{
    listaJugadores *primerJugador = NULL;
    listaJugadores *turno = NULL;

    printf("--- CARGA DE JUGADORES ---\n");
    agregarJugadores(&primerJugador);
    turno = primerJugador;

    printf("\n--- MESA DE JUEGO ---\n");
    recorrerMesa(primerJugador);

    if (turno != NULL) {
        printf("\n--- PRUEBA DE AVANCE DE TURNOS (VUELTA COMPLETA) ---\n");
        printf("Turno actual (inicial): Jugador Nro: %d\n", turno->dato.nro);

        avanzarTurno(&turno); // Pasa al 2do jugador
        avanzarTurno(&turno); // Pasa al 3er jugador
        avanzarTurno(&turno); // Vuelve al 1er jugador (cierra la vuelta)
    }

    return 0;
}
