 #ifndef KLASABLOK_H
 #define KLASABLOK_H
 #include <iostream>
 #include <unistd.h>
 #include <SFML/System/Clock.hpp>
 #include <SFML/System/Time.hpp>
 #include <SFML/Graphics.hpp>

class KlasaBlok: public sf::Sprite
	{
	public:
	sf::Texture tekstura;
	KlasaBlok (float x, float y); //deklaracja konstruktora
	KlasaBlok (const KlasaBlok &bloczek); //deklaracja konstruktora kopiującego
	};
 #endif
