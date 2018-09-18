/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#ifndef OO_VIEW_HPP
#define OO_VIEW_HPP

#include <ncurses.h>
#include <thread>

#include "../model/snake_model.hpp"

#define SNAKE_SHAPE '0'
#define FOOD_SHAPE '0'

#define SNAKE_PAIR 1
#define FOOD_PAIR 2

class Tela {
  private:
    ListaDeSnakes *lista;
    pos_2d *food_pos;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(ListaDeSnakes *lds, pos_2d *food_pos, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop(); // stop screen
    void init(); // init screen
    void update(); // update screen
};

#endif
