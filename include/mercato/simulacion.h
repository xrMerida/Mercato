#pragma once

#include "oferta.h"
#include "transferencia.h"
#include "club.h"
#include "jugador.h"
#include <vector>

class Simulacion {
  public:
    Simulacion(std::vector<Club *> clubes, int dia_final, int club_usuario);
    ~Simulacion();
    void ver_mi_club() const;
    void explorar_jugadores() const;
    void realizar_oferta();
    void revisar_ofertas();
    void ver_historial() const;
    void siguiente_dia();

  private:
    std::vector<Club *> clubes_;
    std::vector<Jugador *> jugadores_;
    Club *club_usuario_;
    int dia_actual_;
    const int dia_final_;
    std::vector<Oferta> ofertas_pendientes_;
    std::vector<Transferencia> historial_;
    int presupuesto_inicial_;
    int ofertas_aceptadas_;
    int ofertas_rechazadas_;
    int total_gastado_;
    int total_recibido_;
};
