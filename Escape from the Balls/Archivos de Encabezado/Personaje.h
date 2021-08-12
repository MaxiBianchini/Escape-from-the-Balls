#include "Bola.h"

class Personaje : public Entity {
public:
	Personaje();
	void Actualizar(float dt) override;
	void Dibujar(RenderWindow &Ventana) override;
	Sprite &getSprite();

	bool ColisionBola(Bola *bola);

private:

	Animacion* animacion;

	Sprite spPersonaje;
	Texture texPersonaje;

	int cambioDeLado;

	bool seFreno;

	bool derecha = Keyboard::isKeyPressed(Keyboard::D);
	bool izquierda = Keyboard::isKeyPressed(Keyboard::A);

	Vector2f posicion;
	Vector2f velocidad;
	Vector2f aceleracion;
};