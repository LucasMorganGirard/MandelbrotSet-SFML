//
//  MandSet.cpp
//  FractalCOMPLEXset
//
//  Created by GIRARD Lucas on 14/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#include "MandSet.hpp"

mandelbrot::mandelbrot(sf::RenderWindow& win, const unsigned short& longueur, const unsigned short& hauteur)
: mLongueur(longueur), mHauteur(hauteur), mWin(win)
{
    mWin.setFramerateLimit(10);
    mPixels = new sf::Uint8[mLongueur*mHauteur*4];
    mTexture.create(mLongueur, mHauteur);
};

void mandelbrot::drawSet() {
    calculateNextStep();
    mTexture.update(mPixels);
    mSprite.setTexture(mTexture, true);
    mWin.draw(mSprite);
};

void mandelbrot::calculateNextStep(){
    for (unsigned i = 0; i < mLongueur*mHauteur*4; i+=4) {
        mPixels[i]=255;
        mPixels[i+1]=0;
        mPixels[i+2]=0;
        mPixels[i+3]=255;
    }
};
