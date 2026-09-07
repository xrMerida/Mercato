#include "simulacion.h"
#include "club.h"
#include "common.h"
#include "oferta.h"
#include "transferencia.h"
#include <cstddef>
#include <iostream>
#include <vector>

Simulacion::Simulacion(std::vector<Club *> clubes, int dia_final,
                       int club_usuario)
    : clubes_(std::move(clubes)), dia_final_(dia_final), dia_actual_(1),
      ofertas_aceptadas_(0), ofertas_rechazadas_(0), total_gastado_(0),
      total_recibido_(0) {
    if (dia_final < 5 || dia_final > 15)
        throw "dia final fuera de rango [5 - 15]";
    if (club_usuario < 0 || club_usuario >= clubes_.size())
        throw "club del usuario no existe";

    club_usuario_ = clubes_[club_usuario];
    presupuesto_inicial_ = club_usuario_->presupuesto;
    plantilla_inicial_ = club_usuario_->jugadores;

    for (size_t c = 0; c < clubes_.size(); c++) {
        for (size_t j = 0; j < clubes_[c]->jugadores.size(); j++) {
            clubes_[c]->jugadores[j]->set_club(clubes_[c]);
            jugadores_.push_back(clubes_[c]->jugadores[j]);
        }
    }
}

Simulacion::~Simulacion() {
    for (size_t j = 0; j < jugadores_.size(); j++) {
        delete jugadores_[j];
    }
    for (size_t c = 0; c < clubes_.size(); c++) {
        delete clubes_[c];
    }
}

void Simulacion::mostrar_club_usuario() const {
    std::cout << kCYELLOW << "\n------- " << club_usuario_->nombre
              << " -------\n"
              << kCRES;
    std::cout << kSBOLD << "Presupuesto: € " << club_usuario_->presupuesto
              << "M\n"
              << kCRES;
    std::cout << "Jugadores: " << club_usuario_->jugadores.size() << "\n";
}

void Simulacion::mostrar_plantilla() const {
    std::cout << kCYELLOW << "\n------- Plantilla -------\n" << kCRES;
    for (size_t j = 0; j < club_usuario_->jugadores.size(); j++) {
        club_usuario_->jugadores[j]->mostrar_info();
        std::cout << "\n";
    }
}

void Simulacion::listar_jugadores() const {
    for (size_t c = 0; c < clubes_.size(); c++) {
        std::cout << kCYELLOW << "\n------ " << clubes_[c]->nombre << " (€ "
                  << clubes_[c]->presupuesto << "M)" << " ------\n"
                  << kCRES;
        for (size_t j = 0; j < clubes_[c]->jugadores.size(); j++) {
            clubes_[c]->jugadores[j]->mostrar_info();
            std::cout << "\n";
        }
    }
}

void Simulacion::listar_jugadores(std::string posicion) const {
    bool encontrado = false;
    for (size_t j = 0; j < jugadores_.size(); j++) {
        if (jugadores_[j]->posicion() != posicion)
            continue;

        jugadores_[j]->mostrar_info();
        std::cout << "\n";
        encontrado = true;
    }

    if (!encontrado)
        std::cerr << kCRED << "\nNo se encontraron jugadores de esa posicion.\n"
                  << kCRES;
}

void Simulacion::mostrar_jugador(int id) const {
    for (size_t j = 0; j < jugadores_.size(); j++) {
        if (jugadores_[j]->id() != id)
            continue;

        jugadores_[j]->mostrar_info();
        return;
    }

    std::cerr << kCRED << "\nNo se encontraron jugadores de esa posicion.\n"
              << kCRES;
}

void Simulacion::realizar_oferta(int id_jugador, int monto) {
    Jugador *jugador = nullptr;
    for (size_t j = 0; j < jugadores_.size(); j++) {
        if (id_jugador != jugadores_[j]->id())
            continue;

        jugador = jugadores_[j];
    }

    // --- Validaciones ------------------
    if (!jugador) {
        std::cerr << kCRED << "\nNo se encontró un jugador con ese ID.\n"
                  << kCRES;
        return;
    }
    if (jugador->club() == club_usuario_) {
        std::cerr << kCRED
                  << "\nNo puedes ofertar por un jugador de tu propio club\n"
                  << kCRES;
        return;
    }
    if (monto <= 0) {
        std::cerr << kCRED << "\nEl monto de la oferta debe ser mayor a € 0M\n"
                  << kCRES;
        return;
    }
    // Revisar que no se oferte dos veces al mismo jugador
    for (size_t o = 0; o < ofertas_pendientes_.size(); o++) {
        if (ofertas_pendientes_[o].jugador != jugador)
            continue;
        if (ofertas_pendientes_[o].estado != EstadoOferta::Pendiente)
            continue;

        std::cerr << kCRED
                  << "\nYa existe una oferta pendiente por este jugador.\n"
                  << kCRES;
        return;
    }

    Oferta nueva_oferta{static_cast<int>(ofertas_pendientes_.size() + 1),
                        jugador,
                        club_usuario_,
                        jugador->club(),
                        monto,
                        EstadoOferta::Pendiente};
    ofertas_pendientes_.push_back(nueva_oferta);

    std::cout << kCGREEN << "\n------- Oferta Realizada -------\n" << kCRES;
    std::cout << kSBOLD << "Jugador: " << jugador->nombre() << "\n" << kCRES;
    std::cout << "Del club: " << jugador->club()->nombre << "\n";
    std::cout << "Por: € " << monto << "M\n";
}

void Simulacion::siguiente_dia() {
    for (size_t i = 0; i < ofertas_pendientes_.size(); i++) {
        Oferta &oferta = ofertas_pendientes_[i];
        // --- Validaciones ----------
        if (oferta.estado != EstadoOferta::Pendiente)
            continue;
        int valor_minimo = static_cast<int>(oferta.jugador->valor() * 1.10);
        if (oferta.monto < valor_minimo) {
            oferta.estado = EstadoOferta::Rechazada;
            ofertas_rechazadas_++;
            std::cout << kCRED << "\nOferta rechazada por "
                      << oferta.jugador->nombre() << " (monto insuficiente).\n"
                      << kCRES;
            continue;
        }
        if (oferta.comprador->presupuesto < oferta.monto) {
            oferta.estado = EstadoOferta::Rechazada;
            ofertas_rechazadas_++;
            std::cout << kCRED << "\nOferta rechazada por "
                      << oferta.jugador->nombre()
                      << " (presupuesto insuficiente).\n"
                      << kCRES;
            continue;
        }

        // --- Ejecución -----------
        oferta.estado = EstadoOferta::Aceptada;
        ofertas_aceptadas_++;
        std::cout << kCGREEN << "\nOferta acpetada por "
                  << oferta.jugador->nombre() << ".\n"
                  << kCRES;
        oferta.comprador->presupuesto -= oferta.monto;
        oferta.vendedor->presupuesto += oferta.monto;
        total_gastado_ += oferta.monto;
        for (size_t j = 0; j < oferta.vendedor->jugadores.size(); j++) {
            if (oferta.vendedor->jugadores[j] == oferta.jugador) {
                oferta.vendedor->jugadores.erase(
                    oferta.vendedor->jugadores.begin() + j);
                break;
            }
        }
        oferta.comprador->jugadores.push_back(oferta.jugador);
        oferta.jugador->set_club(oferta.comprador);
        Transferencia nueva_transferencia{dia_actual_, oferta.jugador,
                                          oferta.vendedor, oferta.comprador,
                                          oferta.monto};
        historial_.push_back(nueva_transferencia);
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

size_t Simulacion::jugadores_max() const { return jugadores_.size(); }

void Simulacion::revisar_ofertas() {
    if (club_usuario_->jugadores.empty()) {
        std::cerr << kCRED << "\nNo tienes jugadores en tu club.\n" << kCRES;
        return;
    }

    int indice_jugador =
        aleat_int(0, static_cast<int>(club_usuario_->jugadores.size() - 1));
    Jugador *jugador_ofertado = club_usuario_->jugadores[indice_jugador];

    Club *club_comprador = nullptr;
    do {
        int indice_club = aleat_int(0, static_cast<int>(clubes_.size() - 1));
        club_comprador = clubes_[indice_club];
    } while (club_comprador == club_usuario_);
    int porcentaje = aleat_int(90, 130);
    int monto_oferta = jugador_ofertado->valor() * porcentaje / 100;

    std::cout << kCYELLOW << "\n------- Oferta Recibida -------\n" << kCRES;
    jugador_ofertado->mostrar_info();
    std::cout << kCYELLOW << "\nOferta por: € " << monto_oferta << "M\n";

    if (!confirmo_usuario("Aceptar?")) {
        ofertas_rechazadas_++;
        std::cerr << kCRED << "\n------- Oferta rechazada -------\n" << kCRES;
        return;
    }

    club_usuario_->presupuesto += monto_oferta;
    club_comprador->presupuesto -= monto_oferta;
    total_recibido_ += monto_oferta;

    // --- Iniciar Transferencia ----------
    // Eliminar jugador del club usuario
    for (size_t j = 0; j < club_usuario_->jugadores.size(); j++) {
        if (club_usuario_->jugadores[j] != jugador_ofertado)
            continue;

        club_usuario_->jugadores.erase(club_usuario_->jugadores.begin() + j);
        break;
    }
    club_comprador->jugadores.push_back(jugador_ofertado);
    jugador_ofertado->set_club(club_comprador);

    Transferencia transferencia{dia_actual_, jugador_ofertado, club_usuario_,
                                club_comprador, monto_oferta};
    historial_.push_back(transferencia);

    ofertas_aceptadas_++;
    std::cout << kCGREEN << "\n------- Oferta aceptada -------\n" << kCRES;
    mostrar_transferencia(historial_.size() - 1);
}

void Simulacion::ver_historial() const {
    if (historial_.empty()) {
        std::cerr << kCRED << "\nNo hay transferencias registradas.\n" << kCRES;
        return;
    }

    std::cout << kCYELLOW << "\n------- Historial de Transferencias -------\n"
              << kCRES;
    for (size_t i = 0; i < historial_.size(); i++) {
        mostrar_transferencia(i);
    }
}

void Simulacion::mostrar_transferencia(int t_indice) const {
    if (t_indice < 0 || t_indice >= static_cast<int>(historial_.size())) {
        std::cerr << kCRED << "\nTransferencia invalida\n" << kCRES;
        return;
    }

    const Transferencia *t = &historial_[t_indice];

    std::cout << "--- Dia " << t->dia << " ---\n";
    std::cout << kSBOLD << "Jugador: " << t->jugador->nombre() << "\n" << kCRES;
    std::cout << kSFAINT << "Origen: " << t->origen->nombre << "\n"
              << "Destino: " << t->destino->nombre << "\n"
              << kCRES;
    std::cout << "Monto: € " << t->monto << " M\n" << kCRES;
    std::cout << "\n";
}

void Simulacion::reporte_final() const {
    std::cout << kCCYAN << "\n======= " << kSBOLD << club_usuario_->nombre
              << kCRES << kCCYAN << " =======\n"
              << kCRES;

    std::cout << kCYELLOW << "\n--- Plantilla Inicial ---\n" << kCRES;
    for (size_t j = 0; j < plantilla_inicial_.size(); j++) {
        plantilla_inicial_[j]->mostrar_info();
        std::cout << "\n";
    }

    std::cout << kCYELLOW << "\n--- Plantilla Final ---\n" << kCRES;
    mostrar_plantilla();

    std::cout << kCYELLOW << "\n--- Presupuesto ---\n" << kCRES;
    std::cout << "Inicial: € " << presupuesto_inicial_ << " M\n";
    std::cout << "Final: € " << club_usuario_->presupuesto << " M\n";

    std::cout << kCYELLOW << "\n--- Totales ---\n" << kCRES;
    std::cout << "Total gastado en compras: € " << total_gastado_ << " M\n";
    std::cout << "Total recibido por ventas: € " << total_recibido_ << " M\n";

    std::cout << kCYELLOW << "\n--- Ofertas ---\n" << kCRES;
    std::cout << "Aceptadas: " << ofertas_aceptadas_ << "\n";
    std::cout << "Rechazadas: " << ofertas_rechazadas_ << "\n";

    ver_historial();
}

bool Simulacion::juego_terminado() const { return dia_actual_ > dia_final_; }
