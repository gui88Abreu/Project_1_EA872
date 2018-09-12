/*
Nome: Guilherme de Brito Abreu
RA: 173691
*/

#include "../include/model/model.hpp"
#include "../include/controler/controler.hpp"
#include "../include/view/view.hpp"

Fisica::Fisica(ListaDeSnakes *lds) {
  this->lista = lds;
}

bool Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Snake*> *s = this->lista->get_snakes();
  deltaT = deltaT/1000.0;
  
  for (int j = 0; j < s->size(); j++){
    std::vector<Corpo*> *c = (*s)[j]->get_corpos();
    vel_2d vel = (*c)[0]->get_velocidade();
    std::vector<pos_2d> last_pos(c->size());
    pos_2d new_pos;

    for (int i = 0; i < c->size(); i++) {
      last_pos[i]= (*c)[i]->get_posicao();
      move(i,0);
      printw ("c%i %i %i", i,(int)last_pos[i].x, (int)last_pos[i].y);
    }

    
    new_pos.x = last_pos[0].x + deltaT *vel.x;
    new_pos.y = last_pos[0].y + deltaT *vel.y;

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

    for (int i = 1; i < c->size(); i++) {
      (*c)[i]->update(vel, last_pos[i-1]);
    }
    (*c)[0]->update(vel, new_pos);

    for (int i =1; i < c->size(); i++){
      if ((int)new_pos.x == (int)last_pos[i].x && (int)new_pos.y == (int)last_pos[i].y)
        return true;
    }
  }
  return false;
}

void Fisica::change_dir(int direction, int i) {
  // Atualiza parametros dos corpos!
  vel_2d new_vel;
  vel_2d last_vel;

  switch (direction){
    case 0:
      new_vel.x = 0;
      new_vel.y = VEL;
      break;
    case 1:
      new_vel.x = -2.0*VEL;
      new_vel.y = 0;
      break;
    case 2:
      new_vel.x = 0;
      new_vel.y = -VEL;  
      break;
    case 3:
      new_vel.x = 2.0*VEL;
      new_vel.y = 0;
      break;
    default:
      return;
  }

  std::vector<Snake *> *s = this->lista->get_snakes();
  std::vector<Corpo *> *c = (*s)[i]->get_corpos();
  last_vel = (*c)[0]->get_velocidade();

  if ((new_vel.x < 0 && last_vel.x > 0) || (new_vel.x > 0 && last_vel.x < 0))
    return;
  else if ((new_vel.y < 0 && last_vel.y > 0) || (new_vel.y > 0 && last_vel.y < 0))
    return;
  else
    (*c)[0]->update(new_vel, (*c)[0]->get_posicao());
}