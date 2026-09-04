#include "simulacion.h"
#include "club.h"
#include <cstddef>
#include <iostream>
#include <vector>

Simulacion::Simulacion(std::vector<Club *> clubes, int dia_final,
                       int club_usuario)
    : clubes_(clubes), dia_final_(dia_final) {
    if (dia_final < 5 || dia_final > 15)
        throw "dia final fuera de rango [5 - 15]";
    if (club_usuario < 0 || club_usuario >= clubes_.size())
        throw "club del usuario no existe";

    club_usuario_ = clubes_[club_usuario];
    for (size_t c = 0; c < clubes_.size(); c++) {
        for (size_t j = 0; j < clubes_[c]->jugadores.size(); j++) {
            clubes_[c]->jugadores[j]->set_club(clubes_[c]);
            jugadores_.push_back(clubes_[c]->jugadores[j]);
        }
    }
}

Simulacion::~Simulacion() {
    for (size_t c = 0; c < clubes_.size(); c++) {
        delete clubes_[c];
    }
    for (size_t j = 0; j < jugadores_.size(); j++) {
        delete jugadores_[j];
    }
}

void Simulacion::ver_mi_club() const {
    std::cout << "---" << club_usuario_->nombre << "------\n"
              << "Dias: " << dia_actual_ << " / " << dia_final_ << "\n"
              << "Presupuesto: Q" << club_usuario_->presupuesto << "\n";
    std::cout << "\n------- Plantilla -------\n";
    for (size_t j = 0; j < club_usuario_->jugadores.size(); j++) {
        club_usuario_->jugadores[j]->mostrar_info();
        std::cout << "\n";
    }
}
