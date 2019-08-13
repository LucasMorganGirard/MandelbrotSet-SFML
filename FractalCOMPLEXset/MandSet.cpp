//
//  MandSet.cpp
//  FractalCOMPLEXset
//
//  Created by GIRARD Lucas on 14/02/2019.
//

#include "MandSet.hpp"
#include <iostream>
#include <math.h>
#include <fstream>
#include "ResourcePath.hpp"
#include <thread>

mandelbrot::mandelbrot(sf::RenderWindow& win)
: mLongueur(win.getSize().x), mHauteur(win.getSize().y), mWin(win), mIntervGaucheX(-1.8), mIntervDroiteX(0.5),mIntervHautY(-1.2), mIntervBasY(1.2), mColorOption(0), mPrecision(100), mAffichierInfo(true)
{
    mWin.setFramerateLimit(30);
    mPixels = new sf::Uint8[mLongueur*mHauteur*4];  //Creation de l'array de pixels
    mTexture.create(mLongueur, mHauteur);           //On cree l'objet qui vas stoquer les pixels
    
    if(!mFont.loadFromFile(resourcePath() + "sansation.ttf")){
        return EXIT_FAILURE;
    }
    mInfo.setFont(mFont);
    mInfo.setFillColor(sf::Color::White);
    mInfo.setCharacterSize(30);
    mInfo.setPosition(20, 20);
    calculateNextStep();
};

const double mandelbrot::map(const double& x, const double& Interval1, const double& Interval1Stop, const double& Interval2, const double& Interval2Stop) const{
    return ((x / (Interval1Stop-Interval1))*(Interval2Stop-Interval2)) + Interval2;
};


void mandelbrot::drawSet() {
    mTexture.update(mPixels);           //On charge les pixels dans la texture
    mSprite.setTexture(mTexture, true); //On charge le sprite (on ne peut pas draw de texture directement)
    mWin.draw(mSprite);                 //On draw le tout
    if(mAffichierInfo){
        mWin.draw(mInfo);
    }
};

void mandelbrot::calculateNextStep(){
    std::vector<std::thread> threads;
    threads.reserve(mLongueur-1);
    for (unsigned x = 0; x < mLongueur; x++) {
        threads.emplace_back(std::thread(&mandelbrot::subClaculateNextStep, this, x));
    }
    
    for (unsigned i = 0; i < threads.size(); i++) {
        threads[i].join();
    }
    
    //infos
    
    std::string infoPrecision = "";
    if(mPrecision < 100){
        infoPrecision = "  very low resolution";
    }else if (mPrecision < 200){
        infoPrecision = " low resolution";
    }else if(mPrecision == 400){
        infoPrecision = " slower to load";
    }else if(mPrecision > 400){
        infoPrecision = " really slow";
    }
    mInfo.setString("precision : " + std::to_string(mPrecision) + infoPrecision + "\nbors gauche : " + std::to_string(mIntervGaucheX) + "\nbors droit : " + std::to_string(mIntervDroiteX)+ "\nbors haut : " + std::to_string(mIntervHautY)+ "\nbors bas : " + std::to_string(mIntervBasY));
};

void mandelbrot::subClaculateNextStep(const unsigned& x){
    
    unsigned index;
    unsigned short iterations;
    bool continuer;
    
    unsigned short r;
    unsigned short g;
    unsigned short b;
    
    unsigned short c1=70;
    unsigned short c2=80;
    unsigned short c3=90;
    
    double partieReel, partieComplex, partieReelNew, partieComplexNew, tempoA;
    
    for (unsigned y = 0; y < mHauteur; y++) {
        
        partieReel = map(x, 0, mLongueur, mIntervGaucheX, mIntervDroiteX);
        partieComplex = map(y, 0, mHauteur, mIntervHautY, mIntervBasY);
        
        partieReelNew = partieReel;
        partieComplexNew = partieComplex;
        
        iterations = 0;
        continuer = true;
        
        while (iterations < mPrecision && continuer) {
            tempoA = ((partieReelNew * partieReelNew) - (partieComplexNew * partieComplexNew));
            partieComplexNew = 2 * partieComplexNew * partieReelNew + partieComplex;
            partieReelNew = tempoA + partieReel;
            
            if((partieReelNew * partieReelNew) - (partieComplexNew * partieComplexNew) > 4){
                continuer=false;
            }else{
                iterations++;
            }
            
        }
        
        if(iterations < mPrecision){
            switch (mColorOption) {
                case 0:
                    r = map(iterations, c3, 100, 0, 255);
                    g = map(iterations, c2, 100, 0, 255);
                    b = map(iterations, c1, 100, 0, 255);
                    break;
                case 1:
                    r = map(iterations, c3, 100, 0, 255);
                    g = map(iterations, c1, 100, 0, 255);
                    b = map(iterations, c2, 100, 0, 255);
                    break;
                case 2:
                    r = map(iterations, c2, 100, 0, 255);
                    g = map(iterations, c3, 100, 0, 255);
                    b = map(iterations, c1, 100, 0, 255);
                    break;
                case 3:
                    r = map(iterations, c1, 100, 0, 255);
                    g = map(iterations, c3, 100, 0, 255);
                    b = map(iterations, c2, 100, 0, 255);
                    break;
                case 4:
                    r = map(iterations, c1, 100, 0, 255);
                    g = map(iterations, c2, 100, 0, 255);
                    b = map(iterations, c3, 100, 0, 255);
                    break;
                case 5:
                    r = map(iterations, c2, 100, 0, 255);
                    g = map(iterations, c1, 100, 0, 255);
                    b = map(iterations, c3, 100, 0, 255);
                    break;
                case 6:
                    r = map(iterations, c2, 100, 0, 255);
                    g = map(iterations, c1, 100, 0, 255);
                    b = map(iterations, c2, 100, 0, 255);
                    break;
                case 7:
                    r = map(iterations, c1, 100, 0, 255);
                    g = map(iterations, c2, 100, 0, 255);
                    b = map(iterations, c2, 100, 0, 255);
                    break;
                case 8:
                    r = map(iterations, c2, 100, 0, 255);
                    g = map(iterations, c2, 100, 0, 255);
                    b = map(iterations, c1, 100, 0, 255);
                    break;
                case 9:
                    r = map(iterations, c1, 100, 0, 255);
                    g = map(iterations, c1, 100, 0, 255);
                    b = map(iterations, c3, 100, 0, 255);
                    break;
                default:
                    break;
            }
        }else if(iterations == mPrecision){
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
    if(mColorOption < 9){
        mColorOption++;
    }else{
        mColorOption = 0;
    }
    calculateNextStep();
};

void mandelbrot::saveImage() const{
    std::ofstream screenShot("screenShot.ppm");
    screenShot << "P3" << std::endl;
    screenShot << mLongueur << " " << mHauteur << std::endl;
    screenShot << "255" << std::endl;
    sf::Uint8 r,g,b;
    for(unsigned i = 0; i < mLongueur * mHauteur * 4; i+=4){
        r = mPixels[i];
        g = mPixels[i+1];
        b = mPixels[i+2];
        screenShot << std::to_string(r) << " " << std::to_string(g) << " " << std::to_string(b) << std::endl;
    }
    system("open screenShot.ppm");
};

void mandelbrot::increasePrecison(){
    switch (mPrecision) {
        case 100:
            mPrecision=200;
            break;
        case 200:
            mPrecision=400;
            break;
        case 400:
            mPrecision=800;
            break;
        case 800:
            mPrecision=1000;
            break;
        case 1000:
            mPrecision=100;
            break;
        default:
            break;
    }
    calculateNextStep();
};

void mandelbrot::goTo(const double& Xgauche, const double& Xdroite, const double& Yhaut, const double& Ybas){
    mIntervGaucheX = Xgauche;
    mIntervDroiteX = Xdroite;
    mIntervHautY = Yhaut;
    mIntervBasY = Ybas;
    calculateNextStep();
};

void mandelbrot::seeInfo(){
    mAffichierInfo = !mAffichierInfo;
};
