#pragma once

#include <string>

struct Club;

class Jugador {
  public:
    Jugador(int id, std::string nombre, int valor);
    virtual ~Jugador() = default;

    virtual void mostrar_info() const;
    std::string nombre() const;
    int valor() const;
    void set_club(Club *club);
    void set_valor(int nuevo_valor);
    int id() const;
    Club *club() const;

  protected:
    int id_;
    std::string nombre_;
    int valor_;
    Club *club_;
};
