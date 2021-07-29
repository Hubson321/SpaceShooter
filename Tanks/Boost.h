#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class Boost
{
private:
	sf::Sprite shape;
	sf::Texture texture;
	int type;

	void initVariables();
	void initShape();

public:
	Boost(float pos_x, float pos_y);
	virtual ~Boost();


	//Accesors
	const sf::FloatRect getBounds() const;


	//Functions
	void update();
	void render(sf::RenderTarget* target);

	int getType();
	
};

