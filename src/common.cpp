#include "common.h"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <random>

int aleat_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool fallo_cin() {
    if (std::cin.eof())
        throw "final de archivo de entrada";

    bool cinfail = std::cin.fail();
    if (cinfail) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return cinfail;
}

int mostrar_menu(std::span<const Opcion> opciones) {
    int seleccion;
    do {
        for (size_t i = 0; i < opciones.size(); ++i) {
            std::cout << (i + 1) << ". " << opciones[i].texto << "\n";
        }
        std::cout << "> ";

        std::cin >> seleccion;
    } while (fallo_cin() || seleccion < 0 || seleccion > opciones.size());
    return --seleccion;
}
