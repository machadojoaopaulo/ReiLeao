//
// Created by João Paulo Machado on 2018-11-30.
//
#include "AdamsBashford.h"

class AdamsBashfordSinusoidal: public AdamsBashford {

protected:
    void alphaVariation(int time) {
         this->alpha = (1.5 + sin(time)) * this->alphaInitial;
    }

};
