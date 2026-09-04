#include "simulacion.h"
#include "club.h"
#include <cstddef>
#include <iostream>
#include <utility>

Simulacion::Simulacion(std::vector<Club *> clubes, int dia_final,
                       int club_usuario)
    : clubes_(std::move(clubes)), dia_final_(dia_final),
      club_usuario_(clubes_[club_usuario]) {
    if (dia_final < 5 || dia_final > 15)
        throw "dia final fuera de rango [5 - 15]";
    if (club_usuario < 0 || club_usuario >= clubes_.size())
        throw "club del usuario no existe";

    for (size_t c = 0; c < clubes_.size(); c++) {
        for (size_t j = 0; j < clubes_[c]->jugadores.size(); j++) {
            jugadores_.push_back(clubes_[c]->jugadores[j]);
        }
    }
}

void Simulacion::ver_mi_club() const {
    std::cout << "---" << club_usuario_->nombre << "------\n"
              << "Dias: " << dia_actual_ << " / " << dia_final_ << "\n"
              << "Presupuesto: Q" << club_usuario_->presupuesto << "\n";
    std::cout << "\n------- Plantilla -------\n";
    for (const auto &jugador : club_usuario_->jugadores) {
        jugador->mostrar_info();
        std::cout << "\n";
    }
}
