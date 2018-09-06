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
  
  pos_2d p = {0,20};
  vel_2d v = {(float)1.5*VEL,0};

  Snake *snake = new Snake();
  for (int i =0; i < 4; i++){
    Corpo *c = new Corpo(v, p);
    snake->add_corpo(c);
    p.y++;  
  }

  ListaDeSnakes *l = new ListaDeSnakes();
  l->add_snake(snake);
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
    switch (c){
      case 's':
        f->change_dir(0,0);
        asample->set_position(0);
        player->play(asample);
        break;
      case 'a':
        f->change_dir(1,0);
        asample->set_position(0);
        player->play(asample);
        break;
      case 'w':
        f->change_dir(2,0);
        asample->set_position(0);
        player->play(asample);
        break;
      case 'd':
        f->change_dir(3,0);
        asample->set_position(0);
        player->play(asample);
        break;
    }

    if (c==27)
      break;

    std::this_thread::sleep_for (std::chrono::milliseconds(10));
    i++;
  }
  player->stop();
  tela->stop();
  teclado->stop();
  return 0;
}