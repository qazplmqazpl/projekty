 #include <iostream>
 #include <unistd.h>
 #include <SFML/System/Clock.hpp>
 #include <SFML/System/Time.hpp>
 #include <SFML/Graphics.hpp>
 #include <SFML/Audio.hpp>
 #include <string>
 #include <cmath> // do wartości bezwzględnej
 
 #include "KlasaBlok.h"
 #include "KlasaDrzewo.h"
 
 #define KAPTUREK_SPADANIE 0.005
 #define KAPTUREK_CHODZENIE 0.1
 #define KAPTUREK_PRZYSPIESZENIE 0.0005
 #define SKOK_MOC 0.8
 #define KAPTUREK_SPAWN (0,524)
 #define SZYBKOSC 1200
 #define PREDKOSC_W_ZABUDOWANYM 1
 

/* Klasa abstrakcyjna */
class Monety // klasa abstrakcyjna do monet
{ 
  protected: // (PRZYJACIEL) do wartości protected ma dostęp klasa Monety oraz jej przyjaciele
  int wartosc;
  friend int funkcjazaprzyjazniona(Monety*); // (PRZYJACIEL) deklaracja przyjaciela
  public:
  sf::Texture tekstura;
  sf::Sprite moneta; 
  int x,y;
  virtual void licznik() = 0; // metoda czysto wirtualna - nie ma ciała
};

/* Klasa dziedzicząca */
class Punkty : public Monety // klasa pochodna 1 (dziedziczenie)
{
  public:
  Punkty (int xparametr,int yparametr); // deklaracja konstruktora
  void licznik ();
};
Punkty::Punkty(int xparametr,int yparametr) // definicja konstruktora
{
tekstura.loadFromFile("tekstury/moneta1.png");
moneta.setTexture(tekstura);
x=xparametr;
y=yparametr;
//moneta.setColor(sf::Color(195,100,50)); miedziana moneta
moneta.setPosition(x,y);
wartosc=20;
}
void Punkty:: licznik () // definicja metody (funkcji w klasie), dzięki której monety znikają (od teraz funkcja zaprzyjaźniona liczy monety)
{
moneta.setPosition(-200,-200);
}
	/* Druga klasa dziedzicząca */
	class Punkty2 : public Monety // klasa pochodna 2
	{
  	public:
  	Punkty2 (int xparametr,int yparametr); // deklaracja konstruktora
  	void licznik ();
	};
	Punkty2::Punkty2(int xparametr,int yparametr) // definicja konstruktora
	{
	tekstura.loadFromFile("tekstury/moneta2.png");
	moneta.setTexture(tekstura);
	x=xparametr;
	y=yparametr;
	moneta.setPosition(x,y);
	wartosc=10;
	}
	void Punkty2:: licznik () // definicja metody (funkcji w klasie), dzięki której monety znikają (od teraz funkcja zaprzyjaźniona liczy monety) 
	{
	moneta.setPosition(-300,-300);
	}
		/* Trzecia klasa dziedzicząca */
		class Grzyb : public Monety // klasa pochodna 3
		{
  		public:
  		Grzyb (int xparametr,int yparametr); // deklaracja konstruktora
 		void licznik ();
		};
		Grzyb::Grzyb(int xparametr,int yparametr) // definicja konstruktora
		{
		tekstura.loadFromFile("tekstury/grzyb.png");
		moneta.setTexture(tekstura);
		x=xparametr;
		y=yparametr;
		moneta.setPosition(x,y);
		wartosc=-10;
		}
		void Grzyb:: licznik () // definicja metody (funkcji w klasie), dzięki której przedmioty znikają (od teraz funkcja zaprzyjaźniona liczy przedmioty) 
		{
		moneta.setPosition(-460,-460);
		}
		
int funkcjazaprzyjazniona(Monety* wskaznik) // (PRZYJACIEL) funkcja zaprzyjaźniona, zwraca wartość
{
return (*wskaznik).wartosc;
}

bool operator==(sf::Sprite wskaznik,sf::Sprite wskaznik2) // (OPERATOR) przeciążamy operator ==
{
return (wskaznik2).getGlobalBounds().intersects((wskaznik).getGlobalBounds());
}


/////////////////////////////////////////////////////////FUNKCJA//MAIN/////////////////////////////////////////////////////////
int main()
{
/* zmienne */
float poziomo_ruch=0;
float pionowo_ruch=0;
bool kapturek_stoi=false;
int wynik=0;
int kolor=0;
int r,g,b;


/////////////////////////WARSTWY///GRAFIKI/////////////////////////
std::vector<sf::Sprite*> warstwa1; //tlo
std::vector<sf::Sprite*> warstwa2; //detale
std::vector<sf::Sprite*> warstwa3; //bloczki kapturek
std::vector<sf::Sprite*> skakable; //warstwa do skakania
std::vector<Monety*> zbierable; //warstwa monet
std::vector<sf::Sprite*>::iterator iter; //deklaracja iteratora
 
//////////////////////////////OBRAZY//////////////////////////////
/* nasza postać - Czerwony Kapturek
tworzymy okienko by wyświetlić nasz plik
nasze okienko ma wymiary 1800x900 pixeli */
sf::RenderWindow window(sf::VideoMode(1800, 900), "Witaj, jestem Kapturek!");

sf::Texture texture; //definiujemy teksturę
sf::Texture texturelewo;
texturelewo.loadFromFile("tekstury/kaptureklewa.png");
sf::Texture textureprawo;
textureprawo.loadFromFile("tekstury/kapturekprawa.png");
if (!texture.loadFromFile("tekstury/kapturek.png")) //wczytujemy nasz obraz 
	{
	std::cout << "Load failed" << std::endl;
	system("pause");
	}
sf::Sprite kapturek; 
kapturek.setTexture(texture);
kapturek.setPosition KAPTUREK_SPAWN; 
warstwa3.push_back(&kapturek);

/* bloczki */
KlasaBlok blok(0,620);
warstwa3.push_back(&blok);
skakable.push_back(&blok);
KlasaBlok blok2(300,620);
warstwa3.push_back(&blok2);
skakable.push_back(&blok2);
KlasaBlok blok3(480,620);
warstwa3.push_back(&blok3);
skakable.push_back(&blok3);
KlasaBlok blok4(660,560);
warstwa3.push_back(&blok4);
skakable.push_back(&blok4);
KlasaBlok blok5(660,620);
warstwa3.push_back(&blok5);
skakable.push_back(&blok5);
KlasaBlok blok6(840,620);
warstwa3.push_back(&blok6);
skakable.push_back(&blok6);
KlasaBlok blok7(1020,620);
warstwa3.push_back(&blok7);
skakable.push_back(&blok7);

/* tło mapy */
sf::Texture background; //definiujemy teksturę tła
if (!background.loadFromFile("tekstury/mapa.png")) //wczytujemy nasz bloczek 
	{
	std::cout << "Load failed" << std::endl;
	system("pause");
	}	
sf::Sprite mapa;
mapa.setTexture(background);
mapa.setPosition(sf::Vector2f(0,-132));
warstwa1.push_back(&mapa);

/* krzaczki */
sf::Texture detal; 
if (!detal.loadFromFile("tekstury/krzak2.png")) 
	{
	std::cout << "Load failed" << std::endl;
	system("pause");
	}	
sf::Sprite krzak;
krzak.setTexture(detal);
krzak.setPosition(sf::Vector2f(-10,460));
warstwa2.push_back(&krzak);
sf::Sprite krzak2(krzak);
krzak2.setPosition(sf::Vector2f(480,460));
warstwa2.push_back(&krzak2);
sf::Sprite krzak3(krzak);
krzak3.setPosition(sf::Vector2f(660,400));
warstwa2.push_back(&krzak3);
sf::Sprite krzak4(krzak);
krzak4.setPosition(sf::Vector2f(900,460));
warstwa2.push_back(&krzak4);

/* drzewka */ 
KlasaDrzewo drzewko(260,260);
warstwa2.push_back(&drzewko);
KlasaDrzewo drzewko2(10,260);
warstwa2.push_back(&drzewko2);
KlasaDrzewo drzewko3(900,260);
warstwa2.push_back(&drzewko3);
KlasaDrzewo drzewko4(1000,260);
warstwa2.push_back(&drzewko4);

sf::Texture detal3; 
detal3.loadFromFile("tekstury/drzewo2.png"); //wysokie drzewo	
sf::Sprite drzewo2;
drzewo2.setTexture(detal3);
drzewo2.setPosition(sf::Vector2f(470,260));
warstwa2.push_back(&drzewo2);

/* monety */
Punkty moneta1(160,590);
warstwa2.push_back(&moneta1.moneta);
zbierable.push_back(&moneta1);
Punkty2 moneta2(300,590);
warstwa2.push_back(&moneta2.moneta);
zbierable.push_back(&moneta2);
Punkty moneta3(400,590);
warstwa2.push_back(&moneta3.moneta);
zbierable.push_back(&moneta3);
Punkty2 moneta4(500,590);
warstwa2.push_back(&moneta4.moneta);
zbierable.push_back(&moneta4);
Punkty moneta5(1040,590);
warstwa2.push_back(&moneta5.moneta);
zbierable.push_back(&moneta5);
Punkty2 moneta6(1140,590);
warstwa2.push_back(&moneta6.moneta);
zbierable.push_back(&moneta6);

Grzyb grzyb(520, 600);
warstwa2.push_back(&grzyb.moneta);
zbierable.push_back(&grzyb);
Grzyb grzyb2(920, 600);
warstwa2.push_back(&grzyb2.moneta);
zbierable.push_back(&grzyb2);


///////////////////////////TEKST///////////////////////////////////////
sf::Font czcionka; //deklarujemy czcionkę
czcionka.loadFromFile("tekstury/Minecraft.ttf");
sf::Text tekst;
tekst.setFont(czcionka);
tekst.setString("wynik:"+ std::to_string(wynik));
tekst.setCharacterSize(40);
//tekst.setFillColor(sf::Color(76,74,77));
tekst.setStyle(sf::Text::Regular);
tekst.setPosition(sf::Vector2f(20,20));


///////////////////////////CZAS///I///MUZYKA///////////////////////////
/* czas potrzebny do szybkości poruszania się postaci */
sf::Time czas = sf::microseconds(SZYBKOSC);
sf::Time czas_skok = sf::milliseconds(500);
sf::Clock zegar;
sf::Clock zegar_skok;
 
/* muzyka */
sf::Music muzyka; //definiujemy muzykę
if (!muzyka.openFromFile("muzyka.wav")) //otwieramy plik audio
	{
	std::cout << "Load failed" << std::endl;
	system("pause");
	}	
muzyka.setVolume(25); //obniża głośność 
muzyka.setLoop(true); //muzyka będzie się odtwarzać w zapętleniu
//muzyka.play(); //odtwarzamy muzykę 


/////////////////////////////PĘTLA///WHILE/////////////////////////////////////////////////////////////////////////////
while (window.isOpen()) //pętla działa dopóki nie zamkniemy okna
	{
	zegar.restart();
	sf::Event event;
	pionowo_ruch += KAPTUREK_SPADANIE; 
	kapturek.setTexture(texture);

	while (window.pollEvent(event))
		{
		  switch (event.type)
		  {
		  case sf::Event::Closed:
		  window.close();
		  break;
	          }

 	        }

window.clear( ); //usuwa nieaktualny obraz


/////////////////////////////////KOLIZJE/////////////////////////////////

		kapturek_stoi = false;
for(iter=skakable.begin();iter<skakable.end();iter++) //użycie iteratora
	{
		//if ( (*skakable[i]).getGlobalBounds().intersects(kapturek.getGlobalBounds()) )  
		if (kapturek== **iter ) // (OPERATOR) używamy przeciążonego operatora aby sprawdzić czy spite'y się przecinają
		{
		kapturek_stoi = true;
		if (pionowo_ruch > 0) pionowo_ruch = 0;
		}
	}

/////////////////////PORUSZANIE///SIĘ////POSTACI//////////////////////////
/* skok w górę */
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //do góry
	{
	if (kapturek_stoi == true && zegar_skok.getElapsedTime() > czas_skok )
		{
		zegar_skok.restart();
		pionowo_ruch += -SKOK_MOC; 
		}
	}
	
/* poruszanie się w dół */
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //w dół
	{ 	/* usunęłam możliwość poruszania się Kapturka w dół, zostawiam go w komentarzu */
	//if (kapturek_stoi == false) {pionowo_ruch += KAPTUREK_CHODZENIE;}
	}
	
/* poruszanie się w lewo */	
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //w lewo
	{
	poziomo_ruch += -KAPTUREK_CHODZENIE;
	kapturek.setTexture(texturelewo);
	}
	
/* poruszanie się w prawo */ 
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) //w prawo
	{
	poziomo_ruch += KAPTUREK_CHODZENIE;
	kapturek.setTexture(textureprawo);
	}
	
//poruszanie
if (poziomo_ruch > PREDKOSC_W_ZABUDOWANYM) poziomo_ruch = PREDKOSC_W_ZABUDOWANYM;
if (poziomo_ruch < -PREDKOSC_W_ZABUDOWANYM) poziomo_ruch = -PREDKOSC_W_ZABUDOWANYM;
kapturek.move( sf::Vector2f(poziomo_ruch,pionowo_ruch) );
	
		
//////////////////////PRZYSPIESZENIE///CHODU///POSTACI//////////////////////
/* przyspieszanie w prawo */
if( poziomo_ruch > (KAPTUREK_CHODZENIE - KAPTUREK_PRZYSPIESZENIE))
	{
	poziomo_ruch += -(KAPTUREK_CHODZENIE - KAPTUREK_PRZYSPIESZENIE);
	}
else if (poziomo_ruch > 0 )
	{
	poziomo_ruch = 0 ;
	}

/* przyspieszanie w lewo */
if( poziomo_ruch < -(KAPTUREK_CHODZENIE - KAPTUREK_PRZYSPIESZENIE))
	{
	poziomo_ruch += (KAPTUREK_CHODZENIE - KAPTUREK_PRZYSPIESZENIE);
	}
else if (poziomo_ruch < 0 )
	{
	poziomo_ruch = 0 ;
	}


///////////////////////////////////RESTART///////////////////////////////////
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {kapturek.setPosition KAPTUREK_SPAWN;} //restartujemy wciskając q na klawiaturze


////////////////////////KOLORKI///NAPISU///WYNIK////////////////////////////
tekst.setFillColor(sf::Color(r,g,b));
tekst.setString("wynik:"+ std::to_string(wynik));
r=510-abs (510-(((kolor/(15-wynik/5)-510)%1530)));
if(r<0) r=0;
if(r>250) r=255;
g=510-abs (510-(((kolor/(15-wynik/5))%1530)));
if(g>250) g=255;
if(g<0) g=0;
b=510-abs (510-(((kolor/(15-wynik/5))+510)%1530));
if(b<0) b=0;
if(b>250) b=255;
kolor++;


///////////////////////////////////WYŚWIETLANIE//////////////////////////////
/* wyświetlamy obiekty w oknie */
for(int i=0;i<warstwa1.size();i++)
	{window.draw(*warstwa1[i]);
	}
for(int i=0;i<warstwa2.size();i++)
	{window.draw(*warstwa2[i]);
	}	
//for(int i=0;i<warstwa3.size();i++)
for(sf::Sprite* zmienna : warstwa3) //zakresowa pętla for 
	{window.draw(*zmienna);
	}
for(int i=0; i<zbierable.size(); i++)
//for(Monety* zmienna : zbierable)
{	if ( (*zbierable[i]).moneta.getGlobalBounds().intersects(kapturek.getGlobalBounds()) )  
	{
	(*zbierable[i]).licznik();
	wynik+=funkcjazaprzyjazniona(zbierable[i]); // (PRZYJACIEL) wynik pobieramy za pomocą funkcji zaprzyjaźnionej
	}
}

window.draw(tekst);
window.display();
 
while (zegar.getElapsedTime()<czas) {usleep(10);}
	}

return EXIT_SUCCESS;
}
