#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture texture_sheet;

	//Animation
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	

	int hp;
	int hpMax;

	//GUI


	//Private functions
	void initVaraibles();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	bool moving;
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;



	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void setMovementSpeed(float value);
	void looseHp(const int value);
	void addHp(const int value);
	//Functions
	void move(const float firX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);

	float getPlayerSpeed() { return this->movementSpeed; }
};

#endif //!PLAYER_H

