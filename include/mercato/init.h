#pragma once

#include "simulacion.h"

namespace init {
// Configura la terminal (UTF-8 y colores) en Windows.
void terminal();

// Crea la simulacion pidiendo los datos iniciales al usuario.
// Devuelve nullptr si el usuario cancela.
Simulacion *simulacion();
} // namespace init
