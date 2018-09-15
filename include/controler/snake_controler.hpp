/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#ifndef _CONTROLER_HPP
#define _CONTROLER_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "../model/snake_model.hpp"

#define VEL 1

class Fisica {
  private:
    ListaDeSnakes *lista;
    bool verify_selfkill(std::vector<Corpo*> *corpos);
    bool verify_snake_ate(std::vector<Corpo*> *c);

  public:
    Fisica(ListaDeSnakes *lds);
    void change_dir(int direction, int i);
    void add_corpo(Corpo *c);
    bool update(float deltaT);
    pos_2d food_pos;
    void feed_snake();
};

#endif
