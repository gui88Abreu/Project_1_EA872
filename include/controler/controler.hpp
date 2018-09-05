/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#ifndef _CONTROLER_HPP
#define _CONTROLER_HPP

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <thread>

#include "../model/model.hpp"

class Fisica {
  private:
    ListaDeCorpos *lista;
    float k;
    float b;
    float ext_force;
  public:
    Fisica(ListaDeCorpos *ldc);
    void choque(int direction);
    void add_corpo(Corpo *c);
    void update(float deltaT);
};

#endif