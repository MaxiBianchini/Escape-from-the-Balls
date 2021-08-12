#include "Personaje.h"

Personaje::Personaje() {
	texPersonaje.loadFromFile("Assets/Imagenes/Personaje.png");
	spPersonaje.setTexture(texPersonaje);

	posicion.x = 400;
	posicion.y = 375;
	spPersonaje.setPosition(posicion);

	velocidad.x = 0.0f;
	velocidad.y = 0.0f;

	aceleracion.x = 300.0f;
	aceleracion.y = 0.0f;

	cambioDeLado = 1;

	animacion = new Animacion(&texPersonaje, &spPersonaje, Vector2u(6, 4), 0.1f);
}

void Personaje::Actualizar(float dt) {
	
	derecha = Keyboard::isKeyPressed(Keyboard::D);
	izquierda = Keyboard::isKeyPressed(Keyboard::A);

	//mover personaje
	if (Keyboard::isKeyPressed(Keyboard::A) && seFreno && izquierda != derecha) {
		animacion->setAnimacion(0);

		velocidad.x += aceleracion.x * dt;
		posicion.x -= velocidad.x * dt;

		cambioDeLado = 1;
		spPersonaje.setPosition(posicion);
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && seFreno && izquierda != derecha) {
		animacion->setAnimacion(1);

		velocidad.x += aceleracion.x * dt;
		posicion.x += velocidad.x * dt;

		cambioDeLado = 2;
		spPersonaje.setPosition(posicion);
	}
	else {
		//cambio de lado o freno
		if (cambioDeLado == 1 && velocidad.x > 0) {

			if(Keyboard::isKeyPressed(Keyboard::D)) animacion->setAnimacion(1);
			else animacion->setAnimacion(2);

			velocidad.x -= aceleracion.x * dt * 2;
			posicion.x -= velocidad.x * dt;

			spPersonaje.setPosition(posicion);
		}
		else if (cambioDeLado == 2 && velocidad.x > 0) {

			if (Keyboard::isKeyPressed(Keyboard::A)) animacion->setAnimacion(0);
			else animacion->setAnimacion(3);

			velocidad.x -= aceleracion.x * dt * 2;
			posicion.x += velocidad.x * dt;

			spPersonaje.setPosition(posicion);
		}
		else {
			if (cambioDeLado == 1) {
				animacion->setAnimacion(2);
			}
			if (cambioDeLado == 2) {
				animacion->setAnimacion(3);
			}
		}

		if (velocidad.x > 0) seFreno = false;
		else seFreno = true;
	}

	//limitar el movimiento del personaje a la ventana
	Vector2f posPersonaje = spPersonaje.getPosition();
	if (posPersonaje.x < 0) posPersonaje.x = 0;
	if (posPersonaje.x > 760) posPersonaje.x = 760;
	spPersonaje.setPosition(posPersonaje);
}

void Personaje::Dibujar(RenderWindow & Ventana) {
	animacion->Update();
	Ventana.draw(spPersonaje);
}

Sprite & Personaje::getSprite() {
	return spPersonaje;
}

bool Personaje::ColisionBola(Bola * bola){
	FloatRect PersonajeRect = getSprite().getGlobalBounds();
	FloatRect BolaRect = bola->getSprite().getGlobalBounds();
	return PersonajeRect.intersects(BolaRect);
}
