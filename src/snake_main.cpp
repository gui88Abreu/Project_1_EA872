#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <ncurses.h>

#include "../include/model/snake_model.hpp"
#include "../include/view/snake_view.hpp"
#include "../include/controler/snake_controler.hpp"

#include "../include/model/audio_model.hpp"
#include "../include/view/audio_view.hpp"
#include "../include/controler/keyboard_controler.hpp"


using namespace std::chrono;

uint64_t get_now_ms();
void init_asamples(std::vector<Audio::Sample*> *asamples);
Snake *create_snake();

int main ()
{
  std::vector<Audio::Sample* > asamples(16);
  init_asamples(&asamples);

  Audio::Player *button_player, *soundboard_player, *background_player;
  button_player = new Audio::Player(), soundboard_player = new Audio::Player(), background_player = new Audio::Player();
  button_player->init(44100, 64, 0.6), soundboard_player->init(44100, 256, 2.5), background_player->init(44100, 2048, 0.2);

  asamples[3]->set_position(1000000);
  button_player->play(asamples[3]);

  background_player->play(asamples[0]);

  Snake *snake = create_snake();
  
  ListaDeSnakes *l = new ListaDeSnakes();
  l->add_snake(snake);
  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, &f->food_pos, 20, 20, 20, 20);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();

  int deltaT =1;
  int food_counter = 0, background_song = 0;
  while (1) {
    if (f->food_pos.x == -1){
      food_counter++;
      f->feed_snake();
      
      if (food_counter == 10){
      soundboard_player->play(asamples[14]);
      }
      else if (food_counter == 20){
        soundboard_player->play(asamples[12]);
      }
      else if (food_counter > 1){
        soundboard_player->play(asamples[4]);
        asamples[4]->set_position(0);
      }
    }

    if (asamples[background_song]->finished()){
      background_song++;
      if (background_song > 2)
        background_song = 0;
      asamples[background_song]->set_position(0);
      background_player->play(asamples[background_song]);
    }

    // Atualiza modelo
    if(f->update(deltaT) && deltaT!=0) {
      background_player->stop();
      soundboard_player->play(asamples[5]);
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
    int c = teclado->getchar();
    switch (c){
      case KEY_DOWN:
        f->change_dir(0,0);
        asamples[3]->set_position(0);
        break;
      case KEY_LEFT:
        f->change_dir(1,0);
        asamples[3]->set_position(0);
        break;
      case KEY_UP:
        f->change_dir(2,0);
        asamples[3]->set_position(0);
        break;
      case KEY_RIGHT:
        f->change_dir(3,0);
        asamples[3]->set_position(0);
        break;
      case 'n':
      case 'N':
        background_song+=2;
      case 'p':
      case 'P':
        background_song-=1;
        if (background_song > 2)
          background_song = 0;
        else if (background_song < 0)
          background_song = 2;
        asamples[background_song]->set_position(0);
        background_player->play(asamples[background_song]);
        break;
    }
    
    if (c==27){
      background_player->stop();
      soundboard_player->play(asamples[6]);
      clear();
      move((int)LINES/2, (int)COLS/2);
      printw("BYE BYE");
      move((int)LINES/2 + 1, (int)COLS/2);
      printw("COME BACK SOON");
      refresh();
      std::this_thread::sleep_for (std::chrono::milliseconds(3000));
      break;
    }

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
  }

  //asmpl_thread.join();
  button_player->stop();
  soundboard_player->stop();
  tela->stop();
  teclado->stop();
  return 0;
}

uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

Snake *create_snake(){
  pos_2d p = {40,40};
  vel_2d v = {(float)VEL,0};

  Snake *snake = new Snake();
  for (int i =0; i < 8; i++){
    Corpo *c = new Corpo(v, p);
    snake->add_corpo(c);
    p.x-=1;
  }

  return snake;
}

void init_asamples(std::vector<Audio::Sample*> *asamples){
  for (int i = 0; i < asamples->size(); i++){
    (*asamples)[i] = new Audio::Sample();
  }

  (*asamples)[0]->load("audio/assets/background0.dat");
  (*asamples)[1]->load("audio/assets/background1.dat");
  (*asamples)[2]->load("audio/assets/background2.dat");
  (*asamples)[3]->load("audio/assets/blip.dat");
  (*asamples)[4]->load("audio/assets/bite.dat");
  (*asamples)[5]->load("audio/assets/naovaidar.dat");
  (*asamples)[6]->load("audio/assets/get_over_here.dat");
  (*asamples)[7]->load("audio/assets/come_here.dat");
  (*asamples)[8]->load("audio/assets/mortal_kombat_theme.dat");
  (*asamples)[9]->load("audio/assets/finish_him.dat");
  (*asamples)[10]->load("audio/assets/finish_her.dat");
  (*asamples)[11]->load("audio/assets/fatality.dat");
  (*asamples)[12]->load("audio/assets/animality.dat");
  (*asamples)[13]->load("audio/assets/soul_suffer.dat");
  (*asamples)[14]->load("audio/assets/brutality.dat");
  (*asamples)[15]->load("audio/assets/zeruela.dat");
  return;
}