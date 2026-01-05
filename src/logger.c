// Zapis danych danych pośrednich (informacji o położeniu cząstek) do pliku.

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "pso.h"

void init_logger(const char *filename) {

    FILE *zapis = fopen(filename, "w"); // Tworzenie/zerowanie pliku
    if (!zapis) {
        fprintf(stderr, "Blad: Nie mozna utworzyc pliku logow: %s\n", filename);
        return;
    }

    fprintf(zapis, "iteracja, id, x, y, wartosc\n");
    fclose(zapis);
}

void log_swarm(const char *filename, int iteration, const Swarm *swarm){

    if(swarm == NULL) {
        fprintf(stderr, "Blad: Roj jest pusty, nie mozna zalogowac stanu\n");
        return;
    }

    FILE *zapis = fopen(filename, "a"); // Dopisywanie do pliku
    if (!zapis) {
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku logow: %s\n", filename);
        return;
    }

    for (int i = 0; i < swarm->particle_count; i++) { // Używamy particle_count z pso.h
        double x = swarm->particles[i].x;
        double y = swarm->particles[i].y;
        
        // Obliczamy wartość "w locie"
        double val = get_map_value(map, x, y);

        fprintf(zapis, "%d,%d,%.4f,%.4f,%.4f\n", iteration, i, x, y, val);
    }

    fclose(zapis);
}