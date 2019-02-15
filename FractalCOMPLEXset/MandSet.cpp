//
//  MandSet.cpp
//  FractalCOMPLEXset
//
//  Created by GIRARD Lucas on 14/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#include "MandSet.hpp"
#include <iostream>
#include <math.h>

mandelbrot::mandelbrot(sf::RenderWindow& win, const unsigned short& longueur, const unsigned short& hauteur)
: mLongueur(longueur), mHauteur(hauteur), mWin(win)
{
    mWin.setFramerateLimit(1);
    mPixels = new sf::Uint8[mLongueur*mHauteur*4];  //Creation de l'array de pixels
    mTexture.create(mLongueur, mHauteur);           //On cree l'objet qui vas stoquer les pixels
};

double mandelbrot::map(const double& x, const double& Interval1, const double& Interval1Stop, const double& Interval2, const double& Interval2Stop) const{
    return ((x / (Interval1Stop-Interval1))*(Interval2Stop-Interval2)) + Interval2;
};


void mandelbrot::drawSet() {
    calculateNextStep();                //Mise a jour de la grille de pixel
    mTexture.update(mPixels);           //On charge les pixels dans la texture
    mSprite.setTexture(mTexture, true); //On charge le sprite (on ne peut pas draw de texture directement)
    mWin.draw(mSprite);                 //On draw le tout
};

void mandelbrot::calculateNextStep(){
    unsigned index;
    unsigned short iterations;
    bool continuer;
    unsigned short bright;
    double partieReel, partieComplex, partieReelNew, partieComplexNew, tempoA, tempoB;
    for (unsigned x = 0; x < mLongueur; x++) {
        for (unsigned y = 0; y < mHauteur; y++) {
            
            partieReel = map(x, 0, mLongueur, -1.5, 0.5);
            partieComplex = map(y, 0, mHauteur, -1, 1);
            
            partieReelNew = partieReel;
            partieComplexNew = partieComplex;
            
            iterations = 0;
            continuer = true;
            
            while (iterations < 100 && continuer) {
                
                
                tempoA = ((partieReelNew * partieReelNew) - (partieComplexNew * partieComplexNew));
                tempoB = 2 * partieComplexNew * partieReelNew;
                partieReelNew = tempoA + partieReel;
                partieComplexNew = tempoB + partieComplex;
                
                
                if((partieReelNew * partieReelNew) - (partieComplexNew * partieComplexNew) > 4){
                    continuer=false;
                }else{
                    iterations++;
                }
                
            }
            if(iterations < 100){
                bright = map(iterations, 0, 100, 0, 255);
            }else{
                bright = 0;
            }
            index = ( x + ( y * mLongueur )) * 4;
            mPixels[index]=bright;     //r
            mPixels[index+1]=bright;     //g
            mPixels[index+2]=bright;     //b
            mPixels[index+3]=255;   //oppacite
        }
    }
};
