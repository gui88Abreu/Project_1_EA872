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
  Audio::Sample *asample, *asample2, *asample3, *background_asample;
  asample = new Audio::Sample(), asample2 = new Audio::Sample(),  asample3 = new Audio::Sample();
  background_asample = new Audio::Sample();
  asample->load("audio/assets/blip.dat"), asample2->load("audio/assets/pao.dat");
  asample3->load("audio/assets/naovaidar.dat"), background_asample->load("audio/assets/background.dat");

  Audio::Player *player, *player2, *player3, *background_player;
  player = new Audio::Player(), player2 = new Audio::Player(), player3 = new Audio::Player();
  background_player = new Audio::Player();
  player->init(44100, 64, 0.6), player2->init(38100, 256, 1.5), player3->init(44100, 256, 2.5), background_player->init(44100, 2048, 0.2);
  player->play(asample), player2->play(asample2), background_player->play(background_asample);

  /*
  std::thread asmpl_thread;
  std::thread newthread(player_thread, background_asample);
  asmpl_thread.swap(newthread);*/

  pos_2d p = {40,40};
  vel_2d v = {(float)VEL,0};

  Snake *snake = new Snake();
  for (int i =0; i < 8; i++){
    Corpo *c = new Corpo(v, p);
    snake->add_corpo(c);
    p.x-=1;
  }

  ListaDeSnakes *l = new ListaDeSnakes();
  l->add_snake(snake);
  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, &f->food_pos, 20, 20, 20, 20);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  T = get_now_ms();
  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = 1;//t1-t0;

    if (f->food_pos.x == -1 && f->food_pos.y == -1){
      f->feed_snake();
      asample2->set_position(0);
    }

    if (background_asample->finished())
      background_asample->set_position(0);
      
    // Atualiza modelo
    if(f->update(deltaT) && deltaT!=0) {
      background_player->stop();
      player3->play(asample3);
      std::this_thread::sleep_for (std::chrono::milliseconds(3000));
      clear();
      move((int)LINES/2, (int)COLS/2);
      printw("GAME OVER");
      move((int)LINES/2 + 1, (int)COLS/2);
      printw("PRESS SOMETHING TO EXIT");
      refresh();
      getch();
      break;
    }

    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    switch (c){
      case 's':
        f->change_dir(0,0);
        asample->set_position(0);
        break;
      case 'a':
        f->change_dir(1,0);
        asample->set_position(0);
        break;
      case 'w':
        f->change_dir(2,0);
        asample->set_position(0);
        break;
      case 'd':
        f->change_dir(3,0);
        asample->set_position(0);
        break;
    }
    
    if (c==27){
      background_player->stop();
      clear();
      move((int)LINES/2, (int)COLS/2);
      printw("BYE BYE");
      move((int)LINES/2 + 1, (int)COLS/2);
      printw("COME BACK SOON");
      refresh();
      std::this_thread::sleep_for (std::chrono::milliseconds(2000));
      break;
    }

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
  }

  //asmpl_thread.join();
  player3->stop();
  player2->stop();
  player->stop();
  tela->stop();
  teclado->stop();
  return 0;
}