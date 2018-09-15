#include "../include/model/snake_model.hpp"
#include "../include/view/snake_view.hpp"

Tela::Tela(ListaDeSnakes *lds, pos_2d *food_pos, int maxI, int maxJ, float maxX, float maxY) {
  this->food_pos = food_pos;
  this->lista = lds;
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

void Tela::init() {
  initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
  curs_set(0);           /* Do not display cursor */
  keypad(stdscr, TRUE);

  start_color();
  init_pair(SNAKE_PAIR, COLOR_GREEN, COLOR_BLACK);
  init_pair(FOOD_PAIR, COLOR_RED, COLOR_BLACK);
}

void Tela::update() {
  //std::vector<Snake*> *s_old = this->lista_anterior->get_snakes();
  std::vector<Snake*> *s = this->lista->get_snakes();

  //apaga corpos na tela
  clear();

  
  for (int k =0; k < s->size(); k++){
    int i, j;
    std::vector<Corpo *> *corpos = (*s)[k]->get_corpos();

    // Desenha corpos na tela
    attron(COLOR_PAIR(SNAKE_PAIR));
    for (int z = 0; z < corpos->size(); z++)
    {
      pos_2d p = (*corpos)[z]->get_posicao();
      i = (int)p.y * (this->maxI / this->maxX);
      j = (int)p.x * (this->maxI / this->maxX);
      mvaddch(i, j, SNAKE_SHAPE);
    }
    attroff(COLOR_PAIR(SNAKE_PAIR));
  }

  if (this->food_pos->x != -1){
    attron(COLOR_PAIR(FOOD_PAIR));
    mvaddch(this->food_pos->y, this->food_pos->x, FOOD_SHAPE);
    attroff(COLOR_PAIR(FOOD_PAIR));
  }
  
  // Atualiza tela
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}