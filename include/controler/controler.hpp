/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#ifndef _CONTROLER_HPP
#define _CONTROLER_HPP

#include <iostream>
#include <vector>
#include <cstdlib>

#include "../model/model.hpp"

const float VEL = 8.0;

class Fisica {
  private:
    ListaDeSnakes *lista;
    bool verify_selfkill(std::vector<Corpo*> *corpos);
    void feed_snake();

  public:
    Fisica(ListaDeSnakes *lds);
    void change_dir(int direction, int i);
    void add_corpo(Corpo *c);
    bool update(float deltaT);
    int grid[1000][1000];
};

#endif