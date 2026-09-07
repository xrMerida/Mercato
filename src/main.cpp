#include "common.h"
#include "init.h"
#include "simulacion.h"
#include <array>
#include <string>

using namespace std;

Simulacion *sim_;

void explorar_jugadores() {
    // POR POSICION ---------------------
    constexpr void (*por_posicion)() = []() {
        constexpr const array _menu_pos{
            Opcion{"Regresar", []() { return; }},
            Opcion{"Portero", []() { sim_->listar_jugadores("Portero"); }},
            Opcion{"Defensa", []() { sim_->listar_jugadores("Defensa"); }},
            Opcion{"Mediocampista",
                   []() { sim_->listar_jugadores("Mediocampista"); }},
            Opcion{"Delantero", []() { sim_->listar_jugadores("Delantero"); }}};

        _menu_pos[menu("Por posicion", _menu_pos)].accion();
    };

    // POR ID ---------------------
    constexpr void (*por_id)() = []() {
        int id = leer_int("Id a buscar", 1, sim_->jugadores_max());
        sim_->mostrar_jugador(id);
    };

    // === MENU ORIGINAL ====================
    constexpr const array _menu{
        Opcion{"Regresar", []() { return; }},
        Opcion{"Ver todos", []() { sim_->listar_jugadores(); }},
        Opcion{"Filtrar por posicion", por_posicion},
        Opcion{"Buscar por ID", por_id}};

    _menu[menu("Explorar Jugadores", _menu)].accion();
}

void realizar_oferta() {
    int id = leer_int("ID del jugador a ofertar", 1, sim_->jugadores_max());
    sim_->mostrar_jugador(id);

    if (!confirmo_usuario())
        return;

    int monto = leer_int("Monto a ofrecer (millones)", 1);
    if (!confirmo_usuario("Ofertar jugador?"))
        return;

    sim_->realizar_oferta(id, monto);
}

void ver_club() {
    sim_->mostrar_plantilla();
    sim_->mostrar_club_usuario();
}

int main() {
    init::terminal();

    do {
        sim_ = init::simulacion();
    } while (sim_ == nullptr);

    // MENU PRINCIPAL
    constexpr const char *_msg_p =
        "▀██    ██▀\n"
        " ███  ███    ▄▄▄▄  ▄▄▄ ▄▄    ▄▄▄▄   ▄▄▄▄   ▄██▄    ▄▄▄  \n"
        " █▀█▄▄▀██  ▄█▄▄▄██  ██▀ ▀▀ ▄█   ▀▀ ▀▀ ▄██   ██   ▄█  ▀█▄\n"
        " █ ▀█▀ ██  ██       ██     ██      ▄█▀ ██   ██   ██   ██\n"
        "▄█▄ █ ▄██▄  ▀█▄▄▄▀ ▄██▄     ▀█▄▄▄▀ ▀█▄▄▀█▀  ▀█▄▀  ▀█▄▄█▀";
    constexpr const array _menu_p{
        Opcion{"Salir", []() { return; }},
        Opcion{"Ver Club", ver_club},
        Opcion{"Explorar Jugadores", explorar_jugadores},
        Opcion{"Realizar Oferta", realizar_oferta},
        Opcion{"Revisar Ofertas", []() { sim_->revisar_ofertas(); }},
        Opcion{"Ver Historial", []() { sim_->ver_historial(); }},
        Opcion{"Avanzar de día", []() { sim_->siguiente_dia(); }},
    };

    int seleccion;
    do {
        seleccion = menu(_msg_p, _menu_p);
        _menu_p[seleccion].accion();
        detener_usuario();
    } while (seleccion != 0 && !sim_->juego_terminado());

    sim_->reporte_final();
}
