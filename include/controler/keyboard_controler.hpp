#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_

#include <ncurses.h>
#include <thread>

void threadfun (int *keybuffer, int *control);

class Teclado {
  private:
    int ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    int getchar();
};

#endif
