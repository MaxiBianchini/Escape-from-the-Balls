#include "Entity.h"

class Animacion {
	
public:
	Animacion(Texture* texture, Sprite* sprite, Vector2u imageCount, float switchTime) {
		this->imageCount = imageCount;
		this->switchTime = switchTime;
		this->sprite = sprite;

		totalTime = 0.0f;
		currentImage.x = 0;
		currentImage.y = -1;

		uvRect.width = texture->getSize().x / float(imageCount.x);
		uvRect.height = texture->getSize().y / float(imageCount.y);
	}

	void setAnimacion(int row) {
		if (currentImage.y == row) return;
		totalTime = 0.0f;
		currentImage.y = row;
		currentImage.x = 0;
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.top = currentImage.y * uvRect.height;
		sprite->setTextureRect(uvRect);
		clock.restart();
	}

	void Update() {

		totalTime += clock.restart().asSeconds();
		if (totalTime < switchTime || currentImage.y == -1) return;

		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.top = currentImage.y * uvRect.height;
		sprite->setTextureRect(uvRect);

	}

	IntRect uvRect;

private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;

	Sprite* sprite;
	Clock clock;
};