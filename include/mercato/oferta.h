#pragma once

#include "jugador.h"

enum class EstadoOferta { Pendiente, Aceptada, Rechazada };

struct Oferta {
    int id;
    Jugador *jugador;
    Club *comprador;
    Club *vendedor;
    int monto;
    EstadoOferta estado;
};
