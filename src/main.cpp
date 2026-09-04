#include "common.h"
#include "init.h"
#include "simulacion.h"
#include <array>

using namespace std;

Simulacion *sim_;

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
        "▄█▄ █ ▄██▄  ▀█▄▄▄▀ ▄██▄     ▀█▄▄▄▀ ▀█▄▄▀█▀  ▀█▄▀  ▀█▄▄█▀\n";
    constexpr const array _menu_p{
        Opcion{"Salir", []() { return; }},
        Opcion{"Ver Club", []() { sim_->ver_mi_club(); }},
        Opcion{"Explorar Jugadores", []() {}},
        Opcion{"Realizar Oferta", []() {}},
        Opcion{"Reviasr Ofertas", []() {}},
        Opcion{"Ver Historial", []() {}},
        Opcion{"Avanzar de día", []() {}},
    };

    int seleccion;
    do {
        seleccion = menu(_msg_p, _menu_p);
        _menu_p[seleccion].accion();
    } while (seleccion != 0);

    delete sim_;
}
