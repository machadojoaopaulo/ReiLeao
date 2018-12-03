//
// Created by João Paulo Machado on 2018-11-30.
//
#include "AdamsBashford.h"

class AdamsBashfordUnlimited: public AdamsBashford {

protected:
    void alphaVariation(int time) {
        //Como o ambiente é ilimitado o alpha não mudará
    }

};
