#include "common.h"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <random>
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

int menu(const char *msg, std::span<const Opcion> opts) {
    int seleccion;
    do {
        std::cout << kCCYAN << msg << kCRES;
        for (size_t i = 0; i < opts.size(); ++i) {
            std::cout << kCGREEN << (i + 1) << ". " << kCRES << opts[i].texto
                      << "\n";
        }
        std::cout << kCBLUE << "> " << kCRES;

        std::cin >> seleccion;
    } while (fallo_cin() || seleccion < 1 || seleccion > opts.size());
    return --seleccion;
}
