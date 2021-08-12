#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Entity {
public:
	virtual void Actualizar(float dt) = 0;
	virtual void Dibujar(RenderWindow &Ventana) = 0;
};
