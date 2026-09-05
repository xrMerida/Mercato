#include "jugador.h"
#include "club.h"
#include <iostream>
#include <string>

Jugador::Jugador(int id, std::string nombre, int valor)
    : id_(id), nombre_(nombre), valor_(valor), club_(nullptr) {
    if (valor < 20 || valor > 140)
        throw "jugador con valor invalido [20 - 140]";
    if (id < 0)
        throw "jugador con id negativo";
}

void Jugador::mostrar_info() const {
    std::cout << "ID: " << id_ << "\n"
              << "Nombre: " << nombre_ << "\n"
              << "Valor: Q " << valor_ << "\n";
    if (club_)
        std::cout << "Club: " << club_->nombre << std::endl;
}

std::string Jugador::nombre() const { return nombre_; }
int Jugador::valor() const { return valor_; }
int Jugador::id() const { return id_; }
Club *Jugador::club() const { return club_; }
void Jugador::set_valor(int nuevo_valor) { valor_ = nuevo_valor; }
void Jugador::set_club(Club *club) {
    if (!club)
        throw "direccion de club invalida";

    club_ = club;
}

