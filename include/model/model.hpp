/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#ifndef _MODEL_HPP
#define _MODEL_HPP

#include <iostream>
#include <vector>
#include "portaudio.h"

typedef struct Position{
  float x;
  float y;
}pos_2d;

typedef pos_2d vel_2d;

class Corpo {
  private:
  float massa;
  vel_2d velocidade;
  pos_2d posicao;

  public:
  Corpo(float massa, vel_2d velocidade, pos_2d p);
  void update(vel_2d nova_velocidade, pos_2d);
  float get_massa();
  vel_2d get_velocidade();
  pos_2d get_posicao();
};

class ListaDeCorpos {
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void hard_copy(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    std::vector<Corpo*> *get_corpos();
};

namespace Audio{

class Sample {
  private:
    std::vector<float> data;
    unsigned int position;

  public:
    Sample();
    ~Sample();
    void load(const char *filename);
    std::vector<float> get_data();
    unsigned int get_position();
    void set_position(unsigned int pos);
    bool finished();

};

}
#endif