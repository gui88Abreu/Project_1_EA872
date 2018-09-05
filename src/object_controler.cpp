/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#include "../include/model/model.hpp"
#include "../include/controler/controler.hpp"

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
  this->k = 5; //constante da mola
  this->b = 1; //constante de amortecimento
  this->ext_force = 0;
}

void Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  deltaT = deltaT/1000.0;
  
  for (int i = 0; i < (*c).size(); i++) {
    float acel = ((-1)*this->k*((*c)[i]->get_posicao() - LINES/2) + this->ext_force - this->b*(*c)[i]->get_velocidade())/(*c)[i]->get_massa();
    float new_vel = (*c)[i]->get_velocidade() + acel*deltaT;
    float new_pos = (*c)[i]->get_posicao() + deltaT *new_vel;
    if (new_pos < 0) {
      new_pos *= -1.0;
      new_vel *= -1.0;
    }
    (*c)[i]->update(new_vel, new_pos);
  }
  this->ext_force = 0;
}

void Fisica::choque(int direction) {
  // Atualiza parametros dos corpos!
  this->ext_force = 50*direction;
}