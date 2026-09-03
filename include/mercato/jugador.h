#pragma once

#include <string>

struct Club;

class Jugador {
  public:
    Jugador(int id, std::string nombre, int valor, Club *club);
    virtual ~Jugador() = default;

    virtual void mostrar_info() const;
    std::string nombre() const;
    int valor() const;

  protected:
    int id_;
    std::string nombre_;
    int valor_;
    Club *club_;
};
