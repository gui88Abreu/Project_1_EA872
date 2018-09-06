/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#include "../include/model/model.hpp"
#include "../include/controler/controler.hpp"

Fisica::Fisica(ListaDeSnakes *lds) {
  this->lista = lds;
}

void Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Snake*> *s = this->lista->get_snakes();
  deltaT = deltaT/1000.0;
  
  for (int j = 0; j < s->size(); j++){
    std::vector<Corpo*> *c = (*s)[j]->get_corpos();
    vel_2d vel = (*c)[0]->get_velocidade();
    pos_2d last_pos = (*c)[0]->get_posicao();
    pos_2d new_pos;
    
    new_pos.x = last_pos.x + deltaT *vel.x;
    new_pos.y = last_pos.y + deltaT *vel.y;

    if (new_pos.x < 0) {
      new_pos.x  = COLS-1;
    }
    if (new_pos.y < 0){
      new_pos.y  = LINES-1;
    }
    if (new_pos.x >= COLS) {
      new_pos.x  = 0;
    }
    if (new_pos.y >= LINES){
      new_pos.y  = 0;
    }

    (*c)[0]->update(vel, new_pos);
    
    pos_2d front_pos;
    for (int i = 1; i < (*c).size(); i++) {
      front_pos = (*c)[i]->get_posicao();
      (*c)[i]->update(vel, last_pos);
      last_pos = front_pos;
    }
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
      new_vel.x = -1.5*VEL;
      new_vel.y = 0;
      break;
    case 2:
      new_vel.x = 0;
      new_vel.y = -VEL;  
      break;
    case 3:
      new_vel.x = 1.5*VEL;
      new_vel.y = 0;
      break;
    default:
      return;
  }

  std::vector<Snake *> *s = this->lista->get_snakes();
  std::vector<Corpo *> *c = (*s)[i]->get_corpos();
  (*c)[0]->update(new_vel, (*c)[i]->get_posicao());
}