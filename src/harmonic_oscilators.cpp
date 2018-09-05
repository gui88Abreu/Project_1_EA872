#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "../include/model/model.hpp"
#include "../include/view/view.hpp"
#include "../include/controler/controler.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  Audio::Sample *asample;
  asample = new Audio::Sample();
  asample->load("audio/assets/blip.dat");

  Audio::Player *player;
  player = new Audio::Player();
  player->init();
  
  Corpo *c1 = new Corpo(10, 0, 20);
  Corpo *c2 = new Corpo(10, 0, 18);
  Corpo *c3 = new Corpo(10, 0, 16);
  Corpo *c4 = new Corpo(10, 0, 14);

  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(c1);
  l->add_corpo(c2);
  l->add_corpo(c3);
  l->add_corpo(c4);

  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, 20, 20, 20, 20);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  int i = 0;

  T = get_now_ms();
  t1 = T;
  asample->set_position(0);
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo
    f->update(deltaT);

    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='s'){
      f->choque(1);
      asample->set_position(0);
      player->play(asample);
    }
    if(c == 'w'){
      f->choque(-1);
      asample->set_position(0);
      player->play(asample);
    }
    if (c=='q')
      break;

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  player->stop();
  tela->stop();
  teclado->stop();
  return 0;
}