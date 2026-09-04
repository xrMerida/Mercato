#pragma once

#include <span>

struct Opcion {
    const char *texto;
    void (*accion)();
};

int aleat_int(int min, int max);
bool fallo_cin();
int mostrar_menu(std::span<const Opcion> opciones);
