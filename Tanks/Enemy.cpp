#include "Enemy.h"
#include<iostream>


void Enemy::initVariables(float spee)
{
	this->pointCount = rand() % 8 + 3;
	this->type		= rand() % 3 + 1;
	switch (this->type)
	{
	case 1:
	{
		this->speed = spee;
		this->hpMax = 10;;
		this->hp = this->hpMax;
		this->damage = this->pointCount;
		this->points = this->pointCount;
		break;
	}
	case 2:
	{
		this->speed = spee;
		this->hpMax = 10;
		this->hp = this->hpMax;
		this->damage = this->pointCount;
		this->points = this->pointCount;
		break;
	}
	case 3:
	{
		this->speed = spee;
		this->hpMax = 10;
		this->hp = this->hpMax;
		this->damage = this->pointCount;
		this->points = this->pointCount;
		break;
	}
	}
}

void Enemy::initShape()
{
	switch (this->type)
	{
	case 1:
	{
		this->texture.loadFromFile("Textures/alien1.png");
		if (!this->texture.loadFromFile("Textures/alien1.png"))
		{
			std::cout << "ERROR::ENEMY::INITTEXTURES::Could not load texture file = ALIEN1" << "\n";
		}
		break;
	}
	case 2:
	{
		this->texture.loadFromFile("Textures/alien2.png");
		if (!this->texture.loadFromFile("Textures/alien2.png"))
		{
			std::cout << "ERROR::BULLET::INITTEXTURES::Could not load texture file = ALIEN2" << "\n";
		}
		break;
	}
	case 3:
	{
		this->texture.loadFromFile("Textures/alien3.png");
		if (!this->texture.loadFromFile("Textures/alien3.png"))
		{
			
			std::cout << "ERROR::BULLET::INITTEXTURES::Could not load texture file = ALIEN3" << "\n";
		}
		break;
	}
	}
	this->shape.setTexture(this->texture);
}

Enemy::Enemy(float pos_x,float pos_y,float temp)
{
	this->initVariables(temp);
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy(){}


//Accesors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int & Enemy::getPoints() const
{
	return this->points;
}

const int & Enemy::getDamage() const
{
	return this->damage;
}


//Functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

void Enemy::setSpeed(float temp)
{
	this->speed = this->speed + temp;
}
float Enemy::getSpeed()
{
	return this->speed;
}

