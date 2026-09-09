#pragma once

#include "jugador.h"

class Portero : public Jugador {
  public:
    // Crea un portero con sus estadisticas (atajadas, salidas y goles recibidos).
    Portero(int id, std::string nombre, int valor, int atajadas,
            int salidas_exitosas, int goles_recibidos);
    ~Portero() = default;

    // Muestra la info base mas las estadisticas de portero.
    void mostrar_info() const override;

    // Devuelve "Portero".
    std::string posicion() const override;

  private:
    int atajadas_;
    int salidas_exitosas_;
    int goles_recibidos_;
};
