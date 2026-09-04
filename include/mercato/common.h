#pragma once

#include <span>

struct Opcion {
    const char *const texto;
    void (*const accion)();
};

int aleat_int(int min, int max);
bool fallo_cin();
int menu(const char *msg, std::span<const Opcion> opts);

// Colores para la terminal
constexpr const char *kCBLACK = "\033[1;30m";
constexpr const char *kCRED = "\033[1;31m";
constexpr const char *kCGREEN = "\033[1;32m";
constexpr const char *kCYELLOW = "\033[1;33m";
constexpr const char *kCBLUE = "\033[1;34m";
constexpr const char *kCMAGENTA = "\033[1;35m";
constexpr const char *kCCYAN = "\033[1;36m";
constexpr const char *kCWHITE = "\033[1;37m";
constexpr const char *kCDEFAULT = "\033[1;39m";
constexpr const char *kCRES = "\033[0m";

constexpr const char *kSBOLD = "\033[1m";
constexpr const char *kSFAINT = "\033[2m";
constexpr const char *kSITALIC = "\033[3m";
constexpr const char *kSUNDERLINE = "\033[4m";
constexpr const char *kSBLINK = "\033[5m";
constexpr const char *kSREVERSE = "\033[7m";
constexpr const char *kSTRIKETHROUGH = "\033[9m";
