#pragma once

#include "club.h"
#include "jugador.h"
#include "oferta.h"
#include "transferencia.h"
#include <cstddef>
#include <string>
#include <vector>

class Simulacion {
  public:
    Simulacion(std::vector<Club *> clubes, int dia_final, int club_usuario);
    ~Simulacion();
    void mostrar_club_usuario() const;
    void listar_jugadores() const;
    void listar_jugadores(std::string posicion) const;
    void mostrar_plantilla() const;
    void mostrar_jugador(int id) const;
    void realizar_oferta(int id_jugador, int monto);
    void revisar_ofertas();
    void ver_historial() const;
    void siguiente_dia();
    void reporte_final() const;
    bool juego_terminado() const;
    size_t jugadores_max() const;

  private:
    std::vector<Club *> clubes_;
    std::vector<Jugador *> jugadores_;
    std::vector<Jugador *> plantilla_inicial_;
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

    void mostrar_transferencia(int t_indice) const;
    bool existe_jugador(int j_indice) const;
};
