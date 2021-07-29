#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>

class Enemy
{
private:
	unsigned pointCount;
	sf::Sprite shape;
	sf::Texture texture;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables(float spee);
	void initShape();

public:
	Enemy(float pos_x, float pos_y,float speed);
	virtual ~Enemy();


	//Accesros
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage()const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
	void setSpeed(float);
	float getSpeed();
};


#endif //!ENEMY_H