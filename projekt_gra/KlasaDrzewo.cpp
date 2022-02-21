#include "KlasaDrzewo.h"
KlasaDrzewo::KlasaDrzewo(float x, float y) //definicja konstruktora
		{	
		tekstura.loadFromFile("tekstury/drzewo.png");
		setTexture(tekstura);
		setPosition(sf::Vector2f(x,y));
		};
		
KlasaDrzewo::KlasaDrzewo (const KlasaDrzewo &drzewko) //definicja konstruktora kopiującego
		{
		setTexture(*(drzewko.getTexture()));
		setPosition(drzewko.getPosition());
		}
