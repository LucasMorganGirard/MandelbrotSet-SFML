//
//  MandSet.hpp
//  FractalCOMPLEXset
//
//  Created by GIRARD Lucas on 14/02/2019.
//  Copyright © 2019 GIRARD Lucas. All rights reserved.
//

#ifndef MandSet_hpp
#define MandSet_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class mandelbrot{
public:
    mandelbrot(sf::RenderWindow&, const unsigned short&, const unsigned short&);
    void drawSet();
    
private:
    void calculateNextStep();
    double map(const double&, const double&, const double&, const double&, const double&) const;
    
    //members variables
    const unsigned short mLongueur;
    const unsigned short mHauteur;
    sf::RenderWindow& mWin;
    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::Uint8* mPixels;
    
    //mandelbrot calculs
    
};

#endif
