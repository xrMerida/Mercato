#include <cstddef>
#include <iostream>
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
    std::vector<Jugador *> jugadores{
        new Portero(1, "Thibaut Courtois", aleat_int(20, 70)),
        new Defensa(2, "Éder Militão", aleat_int(25, 90)),
        new Mediocampista(3, "Jude Bellingham", aleat_int(30, 110)),
        new Delantero(4, "Vinícius Júnior", aleat_int(35, 140)),
        new Mediocampista(5, "Federico Valverde", aleat_int(30, 110)),
        new Portero(6, "Marc-André ter Stegen", aleat_int(20, 70)),
        new Defensa(7, "Ronald Araújo", aleat_int(25, 90)),
        new Mediocampista(8, "Pedri González", aleat_int(30, 110)),
        new Delantero(9, "Robert Lewandowski", aleat_int(35, 140)),
        new Delantero(10, "Lamine Yamal", aleat_int(35, 140)),
        new Portero(11, "Ederson", aleat_int(20, 70)),
        new Defensa(12, "Rúben Dias", aleat_int(25, 90)),
        new Mediocampista(13, "Rodri Hernández", aleat_int(30, 110)),
        new Delantero(14, "Erling Haaland", aleat_int(35, 140)),
        new Mediocampista(15, "Kevin De Bruyne", aleat_int(30, 110)),
        new Portero(16, "Yann Sommer", aleat_int(20, 70)),
        new Defensa(17, "Alessandro Bastoni", aleat_int(25, 90)),
        new Mediocampista(18, "Nicolò Barella", aleat_int(30, 110)),
        new Delantero(19, "Lautaro Martínez", aleat_int(35, 140)),
        new Delantero(20, "Marcus Thuram", aleat_int(35, 140)),
        new Portero(21, "Manuel Neuer", aleat_int(20, 70)),
        new Defensa(22, "Dayot Upamecano", aleat_int(25, 90)),
        new Mediocampista(23, "Joshua Kimmich", aleat_int(30, 110)),
        new Delantero(24, "Harry Kane", aleat_int(35, 140)),
        new Mediocampista(25, "Jamal Musiala", aleat_int(30, 110)),
        new Portero(26, "Gianluigi Donnarumma", aleat_int(20, 70)),
        new Defensa(27, "Achraf Hakimi", aleat_int(25, 90)),
        new Mediocampista(28, "Vitinha", aleat_int(30, 110)),
        new Delantero(29, "Ousmane Dembélé", aleat_int(35, 140)),
        new Delantero(30, "Bradley Barcola", aleat_int(35, 140)),
    };

    std::vector<Club> clubes{
        Club{"Real Madrid", aleat_int(100, 200)},
        Club{"FC Barcelona", aleat_int(100, 200)},
        Club{"Manchester City", aleat_int(100, 200)},
        Club{"Inter Milan", aleat_int(100, 200)},
        Club{"Bayer Munich", aleat_int(100, 200)},
        Club{"Paris Saint-Germain", aleat_int(100, 200)},
    };

    for (size_t club = 0; club < clubes.size(); club++) {
        for (size_t jugador = 0; jugador < 5; jugador++) {
            clubes[club].jugadores.push_back(jugadores[(club * 5) + jugador]);
        }
    }

    // Solicitar datos iniciales
    int dia_final;
    int club_usuario;
    do {
        std::cout << "Club a administrar:\n";
        for (size_t i = 0; i < clubes.size(); i++)
            std::cout << i + 1 << ". " << clubes[i].nombre << "\n";
        std::cout << "> ";

        std::cin >> club_usuario;
    } while (fallo_cin() || club_usuario < 1 || club_usuario > clubes.size());
    club_usuario--;

    do {
        std::cout << "Dias a simular [5 - 15]: ";
        std::cin >> dia_final;
    } while (fallo_cin() || dia_final < 5 || dia_final > 15);

    // Resumen
    std::cout << "\n--- Datos Generados ------";
    for (size_t i = 0; i < clubes.size(); i++) {
        std::cout << "\n- " << clubes[i].nombre << " (Q "
                  << clubes[i].presupuesto << ")\n";
        for (size_t j = 0; j < clubes[i].jugadores.size(); j++) {
            std::cout << "\n";
            clubes[i].jugadores[j]->mostrar_info();
        }
    }
    std::cout << "\n--- Usuario ------\n";
    std::cout << "Club: " << clubes[club_usuario].nombre << "\n";
    std::cout << "Dias a simular: " << dia_final << "\n" << std::endl;

    char continuar;
    do {
        std::cout << "Continuar? [S/n]: ";
        std::cin >> continuar;
    } while (fallo_cin());

    if (continuar == 'N' || continuar == 'n')
        return nullptr;

    return new Simulacion(clubes, jugadores, dia_final, club_usuario);
}

void init::terminal() {
#ifdef __WIN32
    // Set UTF8 for windows console
    SetConsoleOutputCP(CP_UTF8);
    // Allow ANSI escape codes for windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Enable virtual terminal processing
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
#endif // !__WIN32
}
