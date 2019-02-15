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

mandelbrot::mandelbrot(sf::RenderWindow& win)
: mLongueur(win.getSize().x), mHauteur(win.getSize().y), mWin(win), mIntervGaucheX(-1.8), mIntervDroiteX(0.5),mIntervHautY(-1.2), mIntervBasY(1.2), mColorOption(0)
{
    mWin.setFramerateLimit(30);
    mPixels = new sf::Uint8[mLongueur*mHauteur*4];  //Creation de l'array de pixels
    mTexture.create(mLongueur, mHauteur);           //On cree l'objet qui vas stoquer les pixels
    calculateNextStep();
};

double mandelbrot::map(const double& x, const double& Interval1, const double& Interval1Stop, const double& Interval2, const double& Interval2Stop) const{
    return ((x / (Interval1Stop-Interval1))*(Interval2Stop-Interval2)) + Interval2;
};


void mandelbrot::drawSet() {
    mTexture.update(mPixels);           //On charge les pixels dans la texture
    mSprite.setTexture(mTexture, true); //On charge le sprite (on ne peut pas draw de texture directement)
    mWin.draw(mSprite);                 //On draw le tout
};

void mandelbrot::calculateNextStep(){
    unsigned index;
    unsigned short iterations;
    bool continuer;
    unsigned short r;
    unsigned short g;
    unsigned short b;

    double partieReel, partieComplex, partieReelNew, partieComplexNew, tempoA, tempoB;
    for (unsigned x = 0; x < mLongueur; x++) {
        for (unsigned y = 0; y < mHauteur; y++) {
            
            partieReel = map(x, 0, mLongueur, mIntervGaucheX, mIntervDroiteX);
            partieComplex = map(y, 0, mHauteur, mIntervHautY, mIntervBasY);
            
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
                switch (mColorOption) {
                    case 0:
                        r = map(iterations, 15, 10, 0, 255);
                        g = map(iterations, 10, 20, 0, 255);
                        b = map(iterations, 5, 20, 0, 255);
                        break;
                    case 1:
                        r = map(iterations, 15, 10, 0, 255);
                        g = map(iterations, 5, 20, 0, 255);
                        b = map(iterations, 10, 20, 0, 255);
                        break;
                    case 2:
                        r = map(iterations, 10, 10, 0, 255);
                        g = map(iterations, 15, 20, 0, 255);
                        b = map(iterations, 5, 20, 0, 255);
                        break;
                    case 3:
                        r = map(iterations, 5, 10, 0, 255);
                        g = map(iterations, 15, 20, 0, 255);
                        b = map(iterations, 10, 20, 0, 255);
                        break;
                    case 4:
                        r = map(iterations, 5, 10, 0, 255);
                        g = map(iterations, 10, 20, 0, 255);
                        b = map(iterations, 15, 20, 0, 255);
                        break;
                    case 5:
                        r = map(iterations, 10, 10, 0, 255);
                        g = map(iterations, 5, 20, 0, 255);
                        b = map(iterations, 15, 20, 0, 255);
                        break;
                    case 6:
                        r = map(iterations, 10, 10, 0, 255);
                        g = map(iterations, 5, 20, 0, 255);
                        b = map(iterations, 10, 20, 0, 255);
                        break;
                    case 7:
                        r = map(iterations, 5, 10, 0, 255);
                        g = map(iterations, 10, 20, 0, 255);
                        b = map(iterations, 10, 20, 0, 255);
                        break;
                    case 8:
                        r = map(iterations, 10, 10, 0, 255);
                        g = map(iterations, 10, 20, 0, 255);
                        b = map(iterations, 5, 20, 0, 255);
                        break;
                    case 9:
                        r = map(iterations, 5, 10, 0, 255);
                        g = map(iterations, 5, 20, 0, 255);
                        b = map(iterations, 15, 20, 0, 255);
                        break;
                    default:
                        break;
                }
            }else if(iterations == 100){
                r=0;
                g=0;
                b=0;
            }
            index = ( x + ( y * mLongueur )) * 4;
            mPixels[index]=r;       //r
            mPixels[index+1]=g;     //g
            mPixels[index+2]=b;     //b
            mPixels[index+3]=255;   //oppacite
        }
    }
};

void mandelbrot::zoom(){
    double distanceX = abs(mIntervDroiteX - mIntervGaucheX);
    double distanceY = abs(mIntervBasY - mIntervHautY);
    mIntervGaucheX += distanceX/4;
    mIntervDroiteX -= distanceX/4;
    mIntervHautY += distanceY/4;
    mIntervBasY -= distanceY/4;
    calculateNextStep();
}

void mandelbrot::recentrer(const int& x, const int& y){
    
    double distanceX = abs(mIntervDroiteX - mIntervGaucheX);
    double distanceY = abs(mIntervBasY - mIntervHautY);
    double tempo1;
    double tempo2;
    
    tempo1 = map(x, 0, mLongueur, mIntervGaucheX, mIntervDroiteX) - distanceX/2;
    tempo2 = map(x, 0, mLongueur, mIntervGaucheX, mIntervDroiteX) + distanceX/2;
    mIntervGaucheX = tempo1;
    mIntervDroiteX = tempo2;

    tempo1 = map(y, 0, mHauteur, mIntervHautY, mIntervBasY) - distanceY/2;
    tempo2 = map(y, 0, mHauteur, mIntervHautY, mIntervBasY) + distanceY/2;

    mIntervHautY = tempo1;
    mIntervBasY = tempo2;
    zoom();
};

void mandelbrot::reset(){
    mIntervGaucheX = -1.8;
    mIntervDroiteX = 0.5;
    mIntervHautY = -1.2;
    mIntervBasY = 1.2;
    calculateNextStep();
};

void mandelbrot::colorSwitch(){
    if(mColorOption<9){
        mColorOption++;
    }else{
        mColorOption = 0;
    }
    calculateNextStep();
};
