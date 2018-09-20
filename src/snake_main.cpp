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
void init_asamples(std::vector<Audio::Sample*> *asamples); // init asamples
void game_over_msg(); // print game over message
void exit_msg(); // print exit message
void soundboard_interaction(int food_counter, std::vector<Audio::Sample*> asamples, Audio::Player *soundboard_player); // define which soundboard to play
bool keyboard_map(int c, std::vector<Audio::Sample* > asamples, Audio::Player *button_player, // choose what happens according with c
                  Audio::Player *soundboard_player, Audio::Player *background_player, Fisica *f, int *impulse);
Snake *create_snake(unsigned int length); // create snake with length bodys
void record_msg(int record);

int main (){

  // init asamples
  std::vector<Audio::Sample* > asamples(16);
  init_asamples(&asamples);

  // init players
  Audio::Player *button_player, *soundboard_player, *background_player;
  button_player = new Audio::Player(), soundboard_player = new Audio::Player(); 
  background_player = new Audio::Player();  
  button_player->init(44100, 64, 0.6), soundboard_player->init(44100, 256, 2.5);
  background_player->init(44100, 2048, 0.2);

  // ensure that button_player won't play at the beginning of the game
  asamples[3]->set_position(INT32_MAX);
  button_player->play(asamples[3]);

  Snake *snake = create_snake(50);
  
  // add snake into snake list and associate a physical model to it
  ListaDeSnakes *l = new ListaDeSnakes();
  l->add_snake(snake);
  Fisica *f = new Fisica(l);

  // begin screen
  Tela *tela = new Tela(l, &f->food_pos, 20, 20, 20, 20);
  tela->init();

  // begin keyboard interface
  Teclado *teclado = new Teclado();
  teclado->init();

  std::string stat_filename = "statistics/stat.est";
  FILE *stat_file = fopen(stat_filename.data(), "r");
  int record = 0;
  if (stat_file){
    fscanf(stat_file, "%d", &record);
    fclose(stat_file);
  }
  
  int impulse = 0; // speed up snake
  int deltaT =1; // lock delta time in 1, in order to guarantee a discrete variation
  int food_counter = -1;
  bool exit = false;

  background_player->play(asamples[1]);
  while (!exit) {

    // food_pos == (-1, don't care) means that there is no food at the arena 
    if (f->food_pos.x == -1){
      food_counter++;
      f->feed_snake();
      soundboard_interaction(food_counter, asamples, soundboard_player);
    }

    if (asamples[1]->finished())
      asamples[1]->set_position(0);

    // update model
    if(f->update(deltaT) && deltaT!=0) {
      soundboard_player->play(asamples[5]);
      std::this_thread::sleep_for (std::chrono::milliseconds(3000));
      game_over_msg();
      break;
    }

    // update screen
    tela->update();

    // read keys from keyboard
    int c = teclado->getchar();
    exit = keyboard_map(c, asamples, button_player, soundboard_player, background_player, f, &impulse);
    
    std::this_thread::sleep_for (std::chrono::milliseconds(100 - impulse));
    impulse = 0;
  }

  if (food_counter > record){
    FILE *stat_file = fopen(stat_filename.data(), "w");
    fprintf(stat_file, "%d", food_counter);
    fclose(stat_file);
    record_msg(food_counter);
  }
  else{
    record_msg(record);
  }

  std::this_thread::sleep_for (std::chrono::milliseconds(5000));

  // terminate objects properly
  background_player->stop();
  button_player->stop();
  soundboard_player->stop();
  tela->stop();
  teclado->stop();
  return 0;
}

void game_over_msg(){
  clear();
  move((int)LINES/2, -10 + (int)COLS/2);
  printw("GAME OVER");
  refresh();
  return;
}


void record_msg(int record){
  move((int)LINES/2 + 3, -10 + (int)COLS/2);
  printw("RECORD: %d", record);
  refresh();
  return;
}

void exit_msg(){
  clear();
  move((int)LINES/2, -10 + (int)COLS/2);
  printw("BYE BYE");
  move((int)LINES/2 + 1, -10 + (int)COLS/2);
  printw("COME BACK SOON");
  refresh();
  return;
}

bool keyboard_map(int c, std::vector<Audio::Sample* > asamples, Audio::Player *button_player, \
                  Audio::Player *soundboard_player, Audio::Player *background_player, Fisica *f, int *impulse){
  switch (c){
    case KEY_DOWN:
      // head goes down
      f->change_dir(0,0);
      asamples[3]->set_position(0);
      break;
    case KEY_LEFT:
      // head goes left
      f->change_dir(1,0);
      asamples[3]->set_position(0);
      break;
    case KEY_UP:
      // head goes up
      f->change_dir(2,0);
      asamples[3]->set_position(0);
      break;
    case KEY_RIGHT:
      // head goes right
      f->change_dir(3,0);
      asamples[3]->set_position(0);
      break;
    case '\n':
      // speed up snake
      *impulse = 50;
      soundboard_player->play(asamples[15]);
      if (asamples[15]->finished()){
        asamples[15]->set_position(0);
      }
      break;
    case 'I':
    case 'i':
      background_player->volume+=0.1;
      if (background_player->volume > 2)
        background_player->volume = 2;
      break;
    case 'D':
    case 'd':
      background_player->volume-=0.1;
      if (background_player->volume <= 0)
        background_player->volume = 0;
      break;
    case 'm':
    case 'M':
      // turn on/off audio
      background_player->volume =  !background_player->volume;
      soundboard_player->volume = !soundboard_player->volume;
      button_player->volume = !button_player->volume;
      break;
    case 27:
      // terminate game
      soundboard_player->play(asamples[6]);
      exit_msg();
      return true;
  }
  return false;
}

void soundboard_interaction(int food_counter, std::vector<Audio::Sample*> asamples, Audio::Player *soundboard_player){
  if (food_counter == 10){
    soundboard_player->play(asamples[14]);
  }
  else if (food_counter == 20){
    soundboard_player->play(asamples[12]);
  }
  else if (food_counter == 40){
    soundboard_player->play(asamples[11]);
  }
  else if(food_counter == 60){
    soundboard_player->play(asamples[2]);
  }
  else if (food_counter > 0){
    soundboard_player->play(asamples[4]);
    asamples[4]->set_position(0);
  }
  /*else if (food_counter == 1){
    soundboard_player->play(asamples[8]);
  }*/
  return;
}

uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

Snake *create_snake(unsigned int length){
  pos_2d p = {40,40};
  vel_2d v = {(float)VEL,0};

  Snake *snake = new Snake();
  for (int i =0; i < length; i++){
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
  /*
  the first position is reserved for background songs that were not chosen yet
  */
  (*asamples)[1]->load("audio/assets/sonic_theme.dat");
  (*asamples)[2]->load("audio/assets/Ce_e_o_bichao.dat");
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
  (*asamples)[15]->load("audio/assets/mario_star.dat");
  return;
}