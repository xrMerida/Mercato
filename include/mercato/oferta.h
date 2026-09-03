#pragma once

#include "jugador.h"

struct Oferta {
    Jugador *jugador;
    Club *comprador;
    Club *vendedor;
    int monto;
    bool fue_vendido;
};
