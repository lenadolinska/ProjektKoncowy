#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h" 

// Inicjalizuje plik logów
void init_logger(const char *filename);

// Dopiosuje stan roju w danej iteracji do pliku
void log_swarm(const char *filename, int iteration, const Swarm *swarm, const Map *map);

#endif
