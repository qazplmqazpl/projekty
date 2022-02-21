#include "KlasaBlok.h"
KlasaBlok::KlasaBlok(float x, float y) //definicja konstruktora
		{	
		tekstura.loadFromFile("tekstury/klocek.png");
		setTexture(tekstura);
		setPosition(sf::Vector2f(x,y));
		};
		
KlasaBlok::KlasaBlok (const KlasaBlok &bloczek) //definicja konstruktora kopiującego
		{
		setTexture(*(bloczek.getTexture()));
		setPosition(bloczek.getPosition());
		}
