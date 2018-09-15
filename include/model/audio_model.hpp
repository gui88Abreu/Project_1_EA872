#ifndef _AUDIO_MODEL_HPP_
#define _AUDIO_MODEL_HPP_

#include <iostream>
#include <vector>
#include "portaudio.h"

namespace Audio{

class Sample {
  private:
    std::vector<float> data;
    unsigned int position;

  public:
    Sample();
    ~Sample();
    void load(const char *filename);
    std::vector<float> get_data();
    unsigned int get_position();
    void set_position(unsigned int pos);
    bool finished();

};

}

#endif
