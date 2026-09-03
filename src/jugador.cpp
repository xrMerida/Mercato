#include "jugador.h"
#include "club.h"
#include <iostream>
#include <string>

Jugador::Jugador(int id, std::string nombre, int valor, Club *club)
    : id_(id), nombre_(nombre), valor_(valor), club_(club) {
    if (valor < 20 || valor > 140)
        throw "jugador con valor invalido [20 - 140]";
    if (id < 0)
        throw "jugador con numero negativo";
    if (club == nullptr)
        throw "jugador debe tener un club";
}

void Jugador::mostrar_info() const {
    std::cout << "ID: " << id_ << "\n"
              << "Nombre: " << nombre_ << "\n"
              << "Valor: Q " << valor_ << "\n"
              << "Club: " << club_->nombre << std::endl;
}

std::string Jugador::nombre() const { return nombre_; }
int Jugador::valor() const { return valor_; }
