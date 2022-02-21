 #ifndef KLASADRZEWO_H
 #define KLASADRZEWO_H
 #include <iostream>
 #include <unistd.h>
 #include <SFML/System/Clock.hpp>
 #include <SFML/System/Time.hpp>
 #include <SFML/Graphics.hpp>

class KlasaDrzewo: public sf::Sprite
	{
	public:
	sf::Texture tekstura;
	KlasaDrzewo (float x, float y); //deklaracja konstruktora
	KlasaDrzewo (const KlasaDrzewo &drzewko); //deklaracja konstruktora kopiującego
	};
 #endif
