#pragma once

#include "jugador.h"

struct Transferencia {
    int dia;
    Jugador *jugador;
    Club *origen;
    Club *destino;
    int monto;
};
