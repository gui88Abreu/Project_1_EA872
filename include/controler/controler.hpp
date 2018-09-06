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

const float VEL = 10.0;

class Fisica {
  private:
    ListaDeCorpos *lista;

  public:
    Fisica(ListaDeCorpos *ldc);
    void change_dir(int direction, int i);
    void add_corpo(Corpo *c);
    void update(float deltaT);
};

#endif