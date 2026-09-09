#pragma once

#include <string>

struct Club;

class Jugador {
  public:
    // Crea un jugador con id, nombre y valor (debe estar entre 20 y 140).
    Jugador(int id, std::string nombre, int valor);
    virtual ~Jugador() = default;

    // Muestra los datos del jugador en consola.
    virtual void mostrar_info() const;

    // Devuelve la posicion del jugador.
    virtual std::string posicion() const;

    // Devuelve el nombre del jugador.
    std::string nombre() const;

    // Devuelve el valor del jugador.
    int valor() const;

    // Asigna el club al que pertenece el jugador.
    void set_club(Club *club);

    // Actualiza el valor del jugador.
    void set_valor(int nuevo_valor);

    // Devuelve el id del jugador.
    int id() const;

    // Devuelve el club actual del jugador (nullptr si no tiene).
    Club *club() const;

  protected:
    int id_;
    std::string nombre_;
    int valor_;
    Club *club_;
};
