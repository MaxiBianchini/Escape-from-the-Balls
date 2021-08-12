#include "Personaje.h"
#include <string>
#include <vector>

using namespace std;

class Juego {
public:

	Juego();

	char MenuFinal();
	char Menu();
	char Run();

private:

	RenderWindow Ventana;

	//Elementos de los Titulos
	Font fuenteTitulo;
	Text Titulo[6];

	//Elementos de loos Menus
	Texture texFondo;
	Sprite spFondo;

	//Elementos del Juego
	Texture texFondoJuego;
	Sprite spFondoJuego;

	//Elementos de Puntaje
	int puntaje;
	string ssPuntaje;

	// Funciones
	void CrearNuevaBola(float minVel);

	void Add(Entity *e);	//Agrega elementos al Vector de Entidades
	
	void CreadorTextos(int i);

	bool Actualizar(bool salir);
	void Dibujar();

	//Cambia entre las escenas
	char cambioEscena;

	//Vectores de Entidades y Bola
	vector <Entity *> entities;
	vector <Bola *>bolas;

	float minVel = 0;	//Velocidad de las Bolas

	Personaje *personaje;

	// Clocks
	Clock TiempoNuevaBola;		//reloj para medir cuando crear la nueva pelota
	Clock ActualizarPuntaje;	//reloj para medir la actializacion del puntaje
	Clock clock;				//reloj para medir el dt que se le pasa a las entidades

	float dt;

	//Musica del Juego
	Music Musica;

	//Sonido del Juego
	SoundBuffer bufMuerte;
	Sound Muerte;

	Archivo archivo;
};