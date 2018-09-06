/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#include "../include/model/model.hpp"
#include "../include/controler/controler.hpp"

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  deltaT = deltaT/1000.0;
  
  for (int i = 0; i < (*c).size(); i++) {
    vel_2d vel = (*c)[i]->get_velocidade();
    pos_2d last_pos = (*c)[i]->get_posicao();
    pos_2d new_pos;
    
    new_pos.x = last_pos.x + deltaT *vel.x;
    new_pos.y = last_pos.y + deltaT *vel.y;

    if (new_pos.x < 0) {
      new_pos.x  = COLS;
    }
    if (new_pos.y < 0){
      new_pos.y  = LINES;
    }
    if (new_pos.x >= COLS) {
      new_pos.x  = 0;
    }
    if (new_pos.y >= LINES){
      new_pos.y  = 0;
    }

    (*c)[i]->update(vel, new_pos);
  }
}

void Fisica::change_dir(int direction, int i) {
  // Atualiza parametros dos corpos!
  vel_2d new_vel;

  switch (direction){
    case 0:
      new_vel.x = 0;
      new_vel.y = VEL;
      break;
    case 1:
      new_vel.x = -VEL;
      new_vel.y = 0;
      break;
    case 2:
      new_vel.x = 0;
      new_vel.y = -VEL;  
      break;
    case 3:
      new_vel.x = VEL;
      new_vel.y = 0;
      break;
    default:
      return;
  }

  std::vector<Corpo *> *c = this->lista->get_corpos();
  (*c)[i]->update(new_vel, (*c)[i]->get_posicao());
}