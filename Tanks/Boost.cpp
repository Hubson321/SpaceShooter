#include "Boost.h"

void Boost::initVariables()
{
	this->type = rand() % 4 + 1;
}

void Boost::initShape()
{
	switch (this->type)
	{
	case 1://hp
	{
		this->texture.loadFromFile(
			"Textures/hp.png");
		if (!this->texture.loadFromFile("Textures/hp.png"))
		{
			std::cout << "ERROR::BOOST::INITTEXTURES::Could not load texture file = HP" << "\n";
		}
		break;
	}
	case 2://speed
	{
		this->texture.loadFromFile(
			"Textures/boost.png");
		if (!this->texture.loadFromFile("Textures/speed.png"))
		{
			std::cout << "ERROR::BOOST::INITTEXTURES::Could not load texture file = BOOST" << "\n";
		}
		break;
	}
	case 3://Shield
	{
		this->texture.loadFromFile(
			"Textures/shield.png");
		if (!this->texture.loadFromFile("Textures/shield.png"))
		{
			std::cout << "ERROR::BOOST::INITTEXTURES::Could not load texture file = SHIELD" << "\n";
		}
		break;

	}
	}
	this->shape.setTexture(this->texture);
}

Boost::Boost(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Boost::~Boost(){}

const sf::FloatRect Boost::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Boost::update()
{
	this->shape.move(0.f, 1);
}

void Boost::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

int Boost::getType()
{
	return this->type;
}

