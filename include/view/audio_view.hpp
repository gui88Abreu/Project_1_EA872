#ifndef _AUDIO_HPP_
#define _AUDIO_HPP_

#include "../model/audio_model.hpp"
#include "portaudio.h"

namespace Audio{

class Player {
  private:
    Sample *audio_sample;
    bool playing;

    PaStreamParameters  outputParameters;
    PaStream*           stream;
    PaError             err;
    PaTime              streamOpened;


  public:
    Player();
    ~Player();
    float volume;
    void init(double sample_rate, unsigned int frames, float volume);
    void pause();
    void stop();
    void play(Sample *audiosample);
    Sample *get_data();
};

}

#endif
