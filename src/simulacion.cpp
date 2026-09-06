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
    plantilla_inicial_ = club_usuario_->jugadores;

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
              << "Presupuesto: Q" << club_usuario_->presupuesto
              << " millones\n";
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
    } while (fallo_cin() || monto_oferta <= 0);
    Oferta nueva_oferta{static_cast<int>(ofertas_pendientes_.size() + 1),
                        jugador_encontrado,
                        club_usuario_,
                        jugador_encontrado->club(),
                        monto_oferta,
                        EstadoOferta::Pendiente};
    ofertas_pendientes_.push_back(nueva_oferta);

    std::cout << "\nOferta realizada por " << jugador_encontrado->nombre()
              << " al club " << jugador_encontrado->club()->nombre << " por Q"
              << monto_oferta << " millones\n";
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
void Simulacion::explorar_jugadores() const {
    int opcion;
    do {
        std::cout
            << "\n1. Ver todos\n2. Filtrar por posicion\n3. Buscar por ID\n> ";
        std::cin >> opcion;
    } while (fallo_cin() || opcion < 1 || opcion > 3);

    if (opcion == 1) {
        for (size_t j = 0; j < jugadores_.size(); j++) {
            jugadores_[j]->mostrar_info();
            std::cout << "\n";
        }
    } else if (opcion == 2) {
        int pos_opcion;
        do {
            std::cout << "\n1. Portero\n2. Defensa\n3. Mediocampista\n4. "
                         "Delantero\n> ";
            std::cin >> pos_opcion;
        } while (fallo_cin() || pos_opcion < 1 || pos_opcion > 4);

        std::string posiciones[] = {"Portero", "Defensa", "Mediocampista",
                                    "Delantero"};
        std::string posicion_buscada = posiciones[pos_opcion - 1];

        bool encontro_alguno = false;
        for (size_t j = 0; j < jugadores_.size(); j++) {
            if (jugadores_[j]->posicion() == posicion_buscada) {
                jugadores_[j]->mostrar_info();
                std::cout << "\n";
                encontro_alguno = true;
            }
        }
        if (!encontro_alguno) {
            std::cout << "\nNo se encontraron jugadores de esa posicion.\n";
        }
    } else if (opcion == 3) {
        int id_buscado;
        do {
            std::cout << "\nID a buscar: ";
            std::cin >> id_buscado;
        } while (fallo_cin());

        Jugador *jugador_encontrado = nullptr;
        for (size_t j = 0; j < jugadores_.size(); j++) {
            if (jugadores_[j]->id() == id_buscado) {
                jugador_encontrado = jugadores_[j];
                break;
            }
        }

        if (jugador_encontrado) {
            jugador_encontrado->mostrar_info();
        } else {
            std::cout << "\nNo se encontro ningun jugador con ese ID.\n";
        }
    }
}
void Simulacion::revisar_ofertas() {
    if (club_usuario_->jugadores.empty()) {
        std::cout << "\nNo tienes jugadores para recibir ofertas.\n";
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
    std::cout << "\n"
              << club_comprador->nombre << " ofrece Q" << monto_oferta
              << " millones"
              << " por " << jugador_ofertado->nombre() << " (valor: Q"
              << jugador_ofertado->valor() << " millones)\n";

    char respuesta;
    do {
        std::cout << "Aceptar? [S/N]: ";
        std::cin >> respuesta;
    } while (fallo_cin());
    if (respuesta == 'S' || respuesta == 's') {
        club_usuario_->presupuesto += monto_oferta;
        club_comprador->presupuesto -= monto_oferta;
        total_recibido_ += monto_oferta;

        for (size_t j = 0; j < club_usuario_->jugadores.size(); j++) {
            if (club_usuario_->jugadores[j] == jugador_ofertado) {
                club_usuario_->jugadores.erase(
                    club_usuario_->jugadores.begin() + j);
                break;
            }
        }
        club_comprador->jugadores.push_back(jugador_ofertado);
        jugador_ofertado->set_club(club_comprador);

        Transferencia nueva_transferencia{dia_actual_, jugador_ofertado,
                                          club_usuario_, club_comprador,
                                          monto_oferta};
        historial_.push_back(nueva_transferencia);

        ofertas_aceptadas_++;
        std::cout << "\nOferta aceptada. " << jugador_ofertado->nombre()
                  << " se va al " << club_comprador->nombre << ".\n";
    } else if (respuesta == 'N' || respuesta == 'n') {
        ofertas_rechazadas_++;
        std::cout << "\nOferta rechazada.\n";
    }
    else {
        std::cout << "\nRespuesta invalida. Se considera como rechazo.\n";
        ofertas_rechazadas_++;
    }
}
void Simulacion::ver_historial() const {
    if (historial_.empty()) {
        std::cout << "\nNo hay transferencias registradas.\n";
        return;
    }
    std::cout << "\n------- Historial de Transferencias -------\n";
    for (size_t i = 0; i < historial_.size(); i++) {
        const Transferencia &t = historial_[i];
        std::cout << "\nDia: " << t.dia << "\n"
                  << "Jugador: " << t.jugador->nombre() << "\n"
                  << "Origen: " << t.origen->nombre << "\n"
                  << "Destino: " << t.destino->nombre << "\n"
                  << "Monto: Q" << t.monto << " millones\n";
    }
}
void Simulacion::reporte_final() const {
    std::cout << "\n======= REPORTE FINAL =======\n";
    std::cout << "\nClub administrado: " << club_usuario_->nombre << "\n";

    std::cout << "\n--- Plantilla Inicial ---\n";
    for (size_t j = 0; j < plantilla_inicial_.size(); j++) {
        plantilla_inicial_[j]->mostrar_info();
        std::cout << "\n";
    }

    std::cout << "\n--- Plantilla Final ---\n";
    for (size_t j = 0; j < club_usuario_->jugadores.size(); j++) {
        club_usuario_->jugadores[j]->mostrar_info();
        std::cout << "\n";
    }
    std::cout << "\n--- Presupuesto ---\n";
    std::cout << "Inicial: Q" << presupuesto_inicial_ << " millones\n";
    std::cout << "Final: Q" << club_usuario_->presupuesto << " millones\n";

    std::cout << "\n--- Totales ---\n";
    std::cout << "Total gastado en compras: Q" << total_gastado_ << " millones\n";
    std::cout << "Total recibido por ventas: Q" << total_recibido_ << " millones\n";

    std::cout << "\n--- Ofertas ---\n";
    std::cout << "Aceptadas: " << ofertas_aceptadas_ << "\n";
    std::cout << "Rechazadas: " << ofertas_rechazadas_ << "\n";

    std::cout << "\n--- Historial completo ---\n";
    ver_historial();
}
bool Simulacion::juego_terminado() const {
    return dia_actual_ > dia_final_;
}