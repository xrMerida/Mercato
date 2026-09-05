#include "simulacion.h"
#include "club.h"
#include "transferencia.h"
#include "oferta.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include "common.h"

Simulacion::Simulacion(std::vector<Club *> clubes, int dia_final,
                       int club_usuario)
    : clubes_(clubes), dia_final_(dia_final), dia_actual_(1),
      ofertas_aceptadas_(0), ofertas_rechazadas_(0), total_gastado_(0),
      total_recibido_(0) {
    if (dia_final < 5 || dia_final > 15)
        throw "dia final fuera de rango [5 - 15]";
    if (club_usuario < 0 || club_usuario >= clubes_.size())
        throw "club del usuario no existe";

    club_usuario_ = clubes_[club_usuario];
    presupuesto_inicial_ = club_usuario_->presupuesto;

    for (size_t c = 0; c < clubes_.size(); c++) {
        for (size_t j = 0; j < clubes_[c]->jugadores.size(); j++) {
            clubes_[c]->jugadores[j]->set_club(clubes_[c]);
            jugadores_.push_back(clubes_[c]->jugadores[j]);
        }
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
void Simulacion::realizar_oferta() {
    for (size_t j = 0; j < jugadores_.size(); j++) {
        std::cout << "\n";
        jugadores_[j]->mostrar_info();
    }
    int id_buscado;
    do {
        std::cout << "\nID del jugador a ofertar: ";
        std::cin >> id_buscado;
    } while (fallo_cin());

    Jugador *jugador_encontrado = nullptr;
    for (size_t j = 0; j < jugadores_.size(); j++) {
        if (jugadores_[j]->id() == id_buscado) {
            jugador_encontrado = jugadores_[j];
            break;
        }
    }
    if (!jugador_encontrado) {
        std::cout << "\nJugador no encontrado\n";
        return;
    }
    if (jugador_encontrado->club() == club_usuario_) {
        std::cout << "\nNo puedes ofertar por un jugador de tu propio club\n";
        return;
    }
    int monto_oferta;
    do {
        std::cout << "Monto a ofrecer (millones): ";
        std::cin >> monto_oferta;
    } while (fallo_cin());
    Oferta nueva_oferta{static_cast<int>(ofertas_pendientes_.size() + 1),
                        jugador_encontrado,
                        club_usuario_,
                        jugador_encontrado->club(),
                        monto_oferta,
                        EstadoOferta::Pendiente};
    ofertas_pendientes_.push_back(nueva_oferta);

    std::cout << "\nOferta realizada por " << jugador_encontrado->nombre()
              << " al club " << jugador_encontrado->club()->nombre << " por Q"
              << monto_oferta << "\n";
}
void Simulacion::siguiente_dia() {
    for (size_t i = 0; i < ofertas_pendientes_.size(); i++) {
        Oferta &oferta_actual= ofertas_pendientes_[i];
        if (oferta_actual.estado != EstadoOferta::Pendiente)
            continue;
        int valor_minimo =
            static_cast<int>(oferta_actual.jugador->valor() * 1.10);
        if (oferta_actual.monto < valor_minimo) {
            oferta_actual.estado = EstadoOferta::Rechazada;
            ofertas_rechazadas_++;
            std::cout << "\nOferta rechazada por "
                      << oferta_actual.jugador->nombre()
                      << " (monto insuficiente).\n";
        } else if (oferta_actual.comprador->presupuesto < oferta_actual.monto) {
            oferta_actual.estado = EstadoOferta::Rechazada;
            ofertas_rechazadas_++;
            std::cout << "\nOferta rechazada por "
                      << oferta_actual.jugador->nombre()
                      << " (presupuesto insuficiente del comprador).\n";
        } else {
            oferta_actual.estado = EstadoOferta::Aceptada;
            ofertas_aceptadas_++;
            std::cout << "\nOferta aceptada por "
                      << oferta_actual.jugador->nombre() << ".\n";
            oferta_actual.comprador->presupuesto -= oferta_actual.monto;
            oferta_actual.vendedor->presupuesto += oferta_actual.monto;
            total_gastado_ += oferta_actual.monto;
            for (size_t j = 0; j < oferta_actual.vendedor->jugadores.size();
                 j++) {
                if (oferta_actual.vendedor->jugadores[j] ==
                    oferta_actual.jugador) {
                    oferta_actual.vendedor->jugadores.erase(
                        oferta_actual.vendedor->jugadores.begin() + j);
                    break;
                }
            }
            oferta_actual.comprador->jugadores.push_back(oferta_actual.jugador);
            oferta_actual.jugador->set_club(oferta_actual.comprador);
            Transferencia nueva_transferencia{
                dia_actual_, oferta_actual.jugador, oferta_actual.vendedor,
                oferta_actual.comprador, oferta_actual.monto};
            historial_.push_back(nueva_transferencia);
        }
    }
    for (size_t j = 0; j < jugadores_.size(); j++) {
        int variacion = aleat_int(-5, 5);
        int valor_actual = jugadores_[j]->valor();
        int nuevo_valor = valor_actual + (valor_actual * variacion / 100);
        if (nuevo_valor < 5) {
            nuevo_valor = 5;
        }
        jugadores_[j]->set_valor(nuevo_valor);
    }

    dia_actual_++;
}