//
//  MandSet.hpp
//  FractalCOMPLEXset
//
//  Created by GIRARD Lucas on 14/02/2019.
//

#ifndef MandSet_hpp
#define MandSet_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class mandelbrot{
public:
    mandelbrot(sf::RenderWindow&);
    void drawSet();
    void recentrer(const int&, const int&);
    void reset();
    void colorSwitch();
    void saveImage() const;
    void increasePrecison();
    void goTo(const double&, const double&, const double&, const double&);
    void seeInfo();
    
private:
    void zoom();
    void calculateNextStep();
    void subClaculateNextStep(const unsigned&);
    const double map(const double&, const double&, const double&, const double&, const double&) const;
    
    //members variables
    const unsigned short mLongueur;
    const unsigned short mHauteur;
    sf::RenderWindow& mWin;
    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::Uint8* mPixels;
    double mIntervGaucheX;
    double mIntervDroiteX;
    double mIntervHautY;
    double mIntervBasY;
    unsigned short mColorOption;
    unsigned mPrecision;
    bool mAffichierInfo;
    sf::Font mFont;
    sf::Text mInfo;
    
};

#endif
