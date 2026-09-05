#pragma once

#include "jugador.h"

enum class EstadoOferta { Pendiente, Aceptada, Rechazada };

struct Oferta {
    Jugador *jugador;
    Club *comprador;
    Club *vendedor;
    int monto;
    EstadoOferta estado;
};
