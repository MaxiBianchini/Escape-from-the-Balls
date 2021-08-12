#include "Juego.h"

#define SALIR		0
#define MENU		1
#define JUEGO		2
#define MENUFINAL	3
#define SALIRFINAL	4

Juego::Juego() {

	//Ventana de Juego
	Ventana.create(VideoMode(800, 450), "TP Final Binachini Maxi", Style::Close);

	//Actualizaciones por segundo
	Ventana.setFramerateLimit(60);

	//Fondo de los Menús
	texFondo.loadFromFile("Assets/Imagenes/Fondo Menu.png");
	spFondo.setTexture(texFondo);
	
	//Fuente de los Textos
	fuenteTitulo.loadFromFile("Assets/Fuentes/Coolvetica.ttf");

	Titulo[0].setFont(fuenteTitulo);
	Titulo[1].setFont(fuenteTitulo);
	Titulo[2].setFont(fuenteTitulo);
	Titulo[3].setFont(fuenteTitulo);
	Titulo[4].setFont(fuenteTitulo);
	Titulo[5].setFont(fuenteTitulo);

	//Fondo de Juego
	texFondoJuego.loadFromFile("Assets/Imagenes/Fondo Juego.png");
	spFondoJuego.setTexture(texFondoJuego);

	//Puntaje
	puntaje = 0;

	//Pesonaje Nuevo
	personaje = new Personaje();
	Add(personaje);

	//Bola Nueva
	CrearNuevaBola(minVel);

	//Musica
	Musica.openFromFile("Assets/Audio/Musica.ogg");
	Musica.play();

	//Sonido
	bufMuerte.loadFromFile("Assets/Audio/Muerte.wav");
	Muerte.setBuffer(bufMuerte);
}

void Juego::Add(Entity *e) {
	entities.push_back(e);
}

char Juego::MenuFinal() {

	archivo.NuevoPuntaje(puntaje);

	CreadorTextos(1);		

	Ventana.clear();
	
	Ventana.draw(spFondo);

	Ventana.draw(Titulo[4]);
	Ventana.draw(Titulo[5]);

	Ventana.display();

	bool salir = false;

	while (!salir) {

		Event evento;

		while (Ventana.pollEvent(evento)) {
			if (evento.type == Event::Closed) {
				salir = true; cambioEscena = SALIRFINAL;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			salir = true; cambioEscena = SALIR;
			TiempoNuevaBola.restart();
			ActualizarPuntaje.restart();
		}
	}

	return cambioEscena;
}

char Juego::Menu() {

	Ventana.clear();

	CreadorTextos(0);
	CreadorTextos(2);

	for (int i = 0; i < 4; i++) {
		Ventana.draw(Titulo[i]);
	}

	Ventana.display();

	bool salir = false;

	while (!salir) {

		Event evento;

		while (Ventana.pollEvent(evento)) {
			if (evento.type == Event::Closed) {
				salir = true; cambioEscena = SALIRFINAL;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			salir = true; cambioEscena = JUEGO;
			TiempoNuevaBola.restart();
			ActualizarPuntaje.restart();
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			salir = true; cambioEscena = MENU;
			archivo.NuevoArchivo();
		}
	}

	return cambioEscena;
}

char Juego::Run() {

	bool salir = false;
	clock.restart();

	while (Ventana.isOpen() && !salir)
	{	//esto es necesario para quitar todos
		//los eventos de la cola de la ventana
		Event evento;

		while (Ventana.pollEvent(evento))
		{
			if (evento.type == Event::Closed) {
				salir = true; cambioEscena = SALIRFINAL;
			}
		}
		dt = clock.restart().asSeconds();

		salir = Actualizar(salir);

		Dibujar();
	}

	return cambioEscena;
}

bool Juego::Actualizar(bool salir) {

	if (TiempoNuevaBola.getElapsedTime().asSeconds() > 5) {
		minVel += 15;
		CrearNuevaBola(minVel);
		TiempoNuevaBola.restart();
	}

	for (auto e : entities) {
		e->Actualizar(dt);
	}

	for (const auto &bola : bolas) {
		if (personaje->ColisionBola(bola)) {
			
			Musica.pause();
			Muerte.play();
			salir = true; cambioEscena = MENUFINAL;
		}
	}

	if (ActualizarPuntaje.getElapsedTime().asSeconds() > 1) {
		//actualizar el puntaje
		puntaje += 1;
		CreadorTextos(0);

		ActualizarPuntaje.restart();
	}

	return salir;
}

void Juego::Dibujar() {
	//limpiar la pantalla
	Ventana.clear();

	//dibujar los elementos del juego
	Ventana.draw(spFondoJuego);

	for (auto e : entities) {
		e->Dibujar(Ventana);
	}

	Ventana.draw(Titulo[4]);

	Ventana.display();
}

void Juego::CrearNuevaBola(float minVel) {
	Bola *b = new Bola(minVel);
	bolas.push_back(b);
	Add(b);
}

void Juego::CreadorTextos(int i) {

	switch (i) {
	case 0: //PUNTAJE PANTALLA DE JUEGO

		ssPuntaje = " Score: " + to_string(puntaje);
		Titulo[4].setString(ssPuntaje);
		break;

	case 1: //MENU FINAL

		///PUNTAJE FINAL
		ssPuntaje = "Tu Puntaje Final: " + to_string(puntaje); 
		Titulo[4].setString(ssPuntaje);
		Titulo[4].setCharacterSize(60);
		Titulo[4].setPosition(Vector2f((800 - Titulo[4].getLocalBounds().width) / 2.0, 150));
		
		///ENTER
		Titulo[5].setString("Preciona ENTER para ir al Inicio...");
		Titulo[5].setCharacterSize(45);
		Titulo[5].setPosition(Vector2f((800 - Titulo[5].getLocalBounds().width) / 2.0, 250));
		break;

	case 2://MENU

		///TITULO
		Titulo[0].setString("Escape fron the Balls");
		Titulo[0].setCharacterSize(80);
		Titulo[0].setPosition(Vector2f((800 - Titulo[0].getLocalBounds().width) / 2.0, 50));

		///SCORE MAXIMO
		ssPuntaje = "High Score: " + to_string(archivo.MostrarPuntaje());
		Titulo[1].setString(ssPuntaje);
		Titulo[1].setCharacterSize(30);
		Titulo[1].setPosition(Vector2f((800 - Titulo[1].getLocalBounds().width) / 2.0, 170));

		///ENTER
		Titulo[2].setString("Precione ENTER para continuar...");
		Titulo[2].setCharacterSize(45);
		Titulo[2].setPosition(Vector2f((800 - Titulo[2].getLocalBounds().width) / 2.0, 250));

		///SPACE
		Titulo[3].setString("Para limpiar el puntaje guardado precione SPACE.");
		Titulo[3].setCharacterSize(30);
		Titulo[3].setPosition(Vector2f((800 - Titulo[3].getLocalBounds().width) / 2.0, 300));
		break;
	}
}
