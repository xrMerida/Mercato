#include "simulacion.h"
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>
#if defined(_WIN32)
#include <Windows.h>
#endif
#include "club.h"
#include "common.h"
#include "defensa.h"
#include "delantero.h"
#include "init.h"
#include "jugador.h"
#include "mediocampista.h"
#include "portero.h"

Simulacion *init::simulacion() {
    // Generar los Clubes y Jugadores
    std::vector clubes{
        new Club(
            "Real Madrid", aleat_int(100, 200),
            {
                new Portero(1, "Thibaut Courtois", aleat_int(20, 70),
                            aleat_int(0, 5), aleat_int(0, 5), aleat_int(0, 6)),
                new Defensa(2, "Éder Militão", aleat_int(25, 90)),
                new Mediocampista(3, "Jude Bellingham", aleat_int(30, 110)),
                new Delantero(4, "Vinícius Júnior", aleat_int(35, 140)),
                new Mediocampista(5, "Federico Valverde", aleat_int(30, 110)),
            }),
        new Club(
            "FC Barcelona", aleat_int(100, 200),
            {
                new Portero(6, "Marc-André ter Stegen", aleat_int(20, 70),
                            aleat_int(0, 5), aleat_int(0, 5), aleat_int(0, 6)),
                new Defensa(7, "Ronald Araújo", aleat_int(25, 90)),
                new Mediocampista(8, "Pedri González", aleat_int(30, 110)),
                new Delantero(9, "Robert Lewandowski", aleat_int(35, 140)),
                new Delantero(10, "Lamine Yamal", aleat_int(35, 140)),
            }),
        new Club(
            "Manchester City", aleat_int(100, 200),
            {
                new Portero(11, "Ederson", aleat_int(20, 70), aleat_int(0, 5),
                            aleat_int(0, 5), aleat_int(0, 6)),
                new Defensa(12, "Rúben Dias", aleat_int(25, 90)),
                new Mediocampista(13, "Rodri Hernández", aleat_int(30, 110)),
                new Delantero(14, "Erling Haaland", aleat_int(35, 140)),
                new Mediocampista(15, "Kevin De Bruyne", aleat_int(30, 110)),
            }),
        new Club(
            "Inter Milan", aleat_int(100, 200),
            {
                new Portero(16, "Yann Sommer", aleat_int(20, 70),
                            aleat_int(0, 5), aleat_int(0, 5), aleat_int(0, 6)),
                new Defensa(17, "Alessandro Bastoni", aleat_int(25, 90)),
                new Mediocampista(18, "Nicolò Barella", aleat_int(30, 110)),
                new Delantero(19, "Lautaro Martínez", aleat_int(35, 140)),
                new Delantero(20, "Marcus Thuram", aleat_int(35, 140)),
            }),
        new Club(
            "Bayer Múnich", aleat_int(100, 200),
            {
                new Portero(21, "Manuel Neuer", aleat_int(20, 70),
                            aleat_int(0, 5), aleat_int(0, 5), aleat_int(0, 6)),
                new Defensa(22, "Dayot Upamecano", aleat_int(25, 90)),
                new Mediocampista(23, "Joshua Kimmich", aleat_int(30, 110)),
                new Delantero(24, "Harry Kane", aleat_int(35, 140)),
                new Mediocampista(25, "Jamal Musiala", aleat_int(30, 110)),
            }),
        new Club(
            "Paris Saint-Germain", aleat_int(100, 200),
            {
                new Portero(26, "Gianluigi Donnarumma", aleat_int(20, 70),
                            aleat_int(0, 5), aleat_int(0, 5), aleat_int(0, 6)),
                new Defensa(27, "Achraf Hakimi", aleat_int(25, 90)),
                new Mediocampista(28, "Vitinha", aleat_int(30, 110)),
                new Delantero(29, "Ousmane Dembélé", aleat_int(35, 140)),
                new Delantero(30, "Bradley Barcola", aleat_int(35, 140)),
            }),
    };

    // Solicitar datos iniciales
    int dia_final;
    int club_usuario;
    do {
        std::cout << kCCYAN << "Club a administrar\n";
        for (size_t i = 0; i < std::size(clubes); i++)
            std::cout << kCGREEN << i + 1 << ". " << kCRES << clubes[i]->nombre
                      << "\n";
        std::cout << kSFAINT << "> " << kCRES;

        std::cin >> club_usuario;
    } while (fallo_cin() || club_usuario < 1 ||
             club_usuario > std::size(clubes));
    club_usuario--;

    std::cout << kCYELLOW << "\n------- Plantilla -------\n" << kCRES;
    for (size_t j = 0; j < clubes[club_usuario]->jugadores.size(); j++) {
        clubes[club_usuario]->jugadores[j]->mostrar_info();
        std::cout << "\n";
    }

    dia_final = leer_int("Dias a simular", 5, 15);

    Simulacion *sim = new Simulacion(clubes, dia_final, club_usuario);
    // Resumen
    sim->listar_jugadores();
    sim->mostrar_club_usuario();

    if (!confirmo_usuario()) {
        delete sim;
        return nullptr;
    }

    return sim;
}

void init::terminal() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
#endif
}
