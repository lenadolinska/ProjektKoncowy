#include <stdio.h>
#include <stdlib.h>
#include "map.h"

// Bardzo duża kara za wyjście poza mapę
#define PENALTY -1.0e9 

Map* load_map(const char* filename) {

    FILE *file = fopen(filename, "r");

    if (!file) {
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku mapy: %s\n", filename);
        return NULL;
    }

    // Alokacja struktury mapy
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) {
        fprintf(stderr, "Blad: Nie można zaalokowac pamieci dla struktury mapy\n");
        fclose(file);
        return NULL;
    }

    // Wczytanie wymiarów
    if (fscanf(file, "%d %d", &map->width, &map->height) != 2) {
        fprintf(stderr, "Blad: Nieprawidlowy format naglowka mapy\n");
        free(map);
        fclose(file);
        return NULL;
    }

    // Alokacja wierszy
    map->data = (double**)malloc(map->height * sizeof(double*));
    if (!map->data) {
        fprintf(stderr, "Blad alokacji pamieci dla wskaźników wierszy\n");
        free(map);
        fclose(file);
        return NULL;
    }

    // Alokacja kolumn i wczytywanie danych
    for (int i = 0; i < map->height; i++) {
        map->data[i] = (double*)malloc(map->width * sizeof(double));
        if (!map->data[i]) {
            fprintf(stderr, "Blad alokacji wiersza %d\n", i);
            // Sprzątanie tego co udało się do tej pory zaalokować
            for (int j = 0; j < i; j++) 
                free(map->data[j]);
            
            free(map->data);
            free(map);
            fclose(file);
            return NULL;
        }
        
        // Wczytywanie wartości do wiersza
        for (int j = 0; j < map->width; j++) {
            fscanf(file, "%lf", &map->data[i][j]);
        }
    }

    fclose(file);
    return map;
}

void free_map(Map* map) {
    if (map) {
        if (map->data) {
            for (int i = 0; i < map->height; i++) {
                free(map->data[i]);
            }
            free(map->data);
        }
        free(map);
    }
}

// Funkcja Celu (Fitness Function)
double get_map_value(const Map* map, double x, double y) {
    // Rzutowanie pozycji (x, y) na indeksy tablicy
    int col = (int)x;
    int row = (int)y;

    // Obsługa wyjścia poza zakres (kara) 
    if (!map || col < 0 || col >= map->width || row < 0 || row >= map->height) {
        return PENALTY;
    }

    return map->data[row][col];
}