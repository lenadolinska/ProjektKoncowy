#ifndef MAP_H
#define MAP_H

// Struktura mapy
typedef struct {
    int width;
    int height;
    double** data;
} Map;

// Ładowanie mapy z pliku
Map* load_map(const char* filename);

// Zwalnianie pamięci mapy
void free_map(Map* map);

// Pobieranie wartości z mapy w danym punkcie
double get_map_value(const Map* map, double x, double y);

#endif