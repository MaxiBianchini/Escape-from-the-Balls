#include "Bola.h"

Bola::Bola(float minVel) {
	texBola.loadFromFile("Assets/Imagenes/Bola.png");
	spBola.setTexture(texBola);

	srand(time(0));

	posicion.x = 10 + rand() % 750;
	posicion.y = 0 + rand() % 200;
	spBola.setPosition(posicion);
	
	aceleracion.y = 40.0f + minVel;

	velocidad.x = 70;
	velocidad.y = 0; 

	direccion = 0 + rand() % 2;

	bufRebote.loadFromFile("Assets/Audio/Bota Pelota.wav");
	Rebote.setBuffer(bufRebote);
}

void Bola::Actualizar(float dt) {
	//mover la pelota
	switch (direccion) {
	case 0:
		velocidad.y += aceleracion.y * dt;

		posicion.x += velocidad.x * dt;
		posicion.y += velocidad.y * dt;

		break;
	case 1:
		velocidad.y += aceleracion.y * dt;

		posicion.x -= velocidad.x * dt;
		posicion.y += velocidad.y * dt;
		break;
	}

	spBola.setPosition(posicion);

	//limitar el movimiento de la pelota
	Vector2f posBola = spBola.getPosition();
	if (posBola.x < 0) {
		posBola.x = 0;
		direccion = 0;
		Rebote.play();
	} 
	else if (posBola.x > 760) {
		posBola.x = 760;
		direccion = 1;
		Rebote.play();
	}
	
	if (posBola.y < 0) {
		posBola.y = 0;
		velocidad.y *= -1;
		Rebote.play();
	} 
	else if (posBola.y > 380) {
		posBola.y = 380;
		velocidad.y *= -1;
		Rebote.play();
	}

	spBola.setPosition(posBola);
}

void Bola::Dibujar(RenderWindow & Ventana) {
	Ventana.draw(spBola);
}

Sprite & Bola::getSprite() {
	return spBola;
}
