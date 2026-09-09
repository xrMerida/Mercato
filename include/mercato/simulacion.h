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
    // Crea la simulacion con los clubes, el dia final y el club del usuario.
    Simulacion(std::vector<Club *> clubes, int dia_final, int club_usuario);

    // Libera la memoria de los jugadores y clubes.
    ~Simulacion();

    // Muestra el presupuesto y la cantidad de jugadores del club del usuario.
    void mostrar_club_usuario() const;

    // Lista todos los jugadores de todos los clubes.
    void listar_jugadores() const;

    // Lista solo los jugadores de la posicion indicada.
    void listar_jugadores(std::string posicion) const;

    // Muestra la plantilla actual del club del usuario.
    void mostrar_plantilla() const;

    // Muestra el jugador con el id indicado.
    void mostrar_jugador(int id) const;

    // Crea una oferta pendiente por un jugador de otro club.
    void realizar_oferta(int id_jugador, int monto);

    // Simula una oferta aleatoria por un jugador del club del usuario.
    void revisar_oferta();

    // Muestra el historial de transferencias.
    void ver_historial() const;

    // Procesa las ofertas pendientes, varia los valores y avanza un dia.
    void siguiente_dia();

    // Muestra el reporte final de la simulacion.
    void reporte_final() const;

    // Indica si la simulacion ya termino (dia actual > dia final).
    bool juego_terminado() const;

    // Devuelve la cantidad total de jugadores.
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

    // Muestra una transferencia del historial por su indice.
    void mostrar_transferencia(int t_indice) const;
};
