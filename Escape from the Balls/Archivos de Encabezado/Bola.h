#include "Archivos.h"

class Bola : public Entity {
public:
	Bola(float minVel);

	void Actualizar(float dt) override;
	void Dibujar(RenderWindow &Ventana) override;

	Sprite &getSprite();

private:
	Sprite spBola;
	Texture texBola;

	SoundBuffer bufRebote;
	Sound Rebote;

	int direccion;

	Vector2f posicion;
	Vector2f velocidad;
	Vector2f aceleracion;
};