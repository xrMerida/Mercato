#include "common.h"
#include "init.h"
#include "simulacion.h"
#include <array>
#include <iostream>

using namespace std;

Simulacion *sim_;

int main() {
    init::terminal();

    do {
        std::cout << "------------- Bienvenido a Mercato! -----------\n";
        sim_ = init::simulacion();
    } while (sim_ == nullptr);

    // MENU PRINCIPAL
    constexpr const array menu_principal{
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
        cout << "▀██    ██▀\n"
             << " ███  ███    ▄▄▄▄  ▄▄▄ ▄▄    ▄▄▄▄   ▄▄▄▄   ▄██▄    ▄▄▄  \n"
             << " █▀█▄▄▀██  ▄█▄▄▄██  ██▀ ▀▀ ▄█   ▀▀ ▀▀ ▄██   ██   ▄█  ▀█▄\n"
             << " █ ▀█▀ ██  ██       ██     ██      ▄█▀ ██   ██   ██   ██\n"
             << "▄█▄ █ ▄██▄  ▀█▄▄▄▀ ▄██▄     ▀█▄▄▄▀ ▀█▄▄▀█▀  ▀█▄▀  ▀█▄▄█▀\n";
        seleccion = mostrar_menu(menu_principal);
        menu_principal[seleccion].accion();
    } while (seleccion != 0);
}
