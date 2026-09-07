#include "common.h"
#include <climits>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <random>
#include <span>
#ifdef __WIN32
#include <Windows.h>
#endif // !__WIN32

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

int menu(const char *const msg, const std::span<const Opcion> opts) {
    int seleccion;
    do {
        std::cout << "\n" << kCCYAN << msg << "\n";
        for (size_t i = 0; i < opts.size(); ++i) {
            std::cout << kCGREEN << i + 1 << ". " << kCRES << opts[i].texto
                      << "\n";
        }
        std::cout << kCBLUE << "> " << kCRES;

        std::cin >> seleccion;
    } while (fallo_cin() || seleccion < 1 || seleccion > opts.size());
    return --seleccion;
}

int leer_int(const char *const msg, int min, int max) {
    int entrada;
    do {
        std::cout << kCCYAN << msg << kCRES;
        if (max != INT_MAX && min != INT_MIN)
            std::cout << kSFAINT << " [" << min << " - " << max << "]" << kCRES;
        std::cout << ": ";
        std::cin >> entrada;
    } while (fallo_cin() || entrada < min || entrada > max);

    return entrada;
}

bool confirmo_usuario(const char *msg) {
    char respuesta;
    do {
        std::cout << kCCYAN << msg << kCRES << kSFAINT << " [S/N]" << kCRES
                  << ": ";
        std::cin >> respuesta;
    } while (fallo_cin() || (respuesta != 'S' && respuesta != 's' &&
                             respuesta != 'N' && respuesta != 'n'));

    return (respuesta == 'S' || respuesta == 's');
}

void detener_usuario() {
    std::cout << kSFAINT << kSITALIC << "Presione enter para continuar"
              << kCRES;
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
