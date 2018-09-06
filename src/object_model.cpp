/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#include "../include/model/model.hpp"

Corpo::Corpo(float massa, vel_2d velocidade, pos_2d p) {
  this->massa = massa;
  this->velocidade = velocidade;
  this->posicao = p;
}

void Corpo::update(vel_2d nova_velocidade, pos_2d p) {
  this->velocidade = nova_velocidade;
  this->posicao = p;
}

float Corpo::get_massa() {
  return this->massa;
}

vel_2d Corpo::get_velocidade() {
  return this->velocidade;
}

pos_2d Corpo::get_posicao() {
  return this->posicao;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_massa(),(*corpos)[k]->get_velocidade(),(*corpos)[k]->get_posicao());
    this->add_corpo(c);
  }
}

void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}