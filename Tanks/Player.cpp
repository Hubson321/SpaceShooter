#include "Player.h"


void Player::initVaraibles()
{
	this->moving = false;
	this->movementSpeed = 4.f;

	this->attackCooldownMax = 15.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 50;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//Load texture from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}

}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//this->currentFrame = sf::IntRect(0, 0, 200, 200);

	//this->sprite.setTextureRect(this->currentFrame);

	//Resize sprite
	this->sprite.scale(0.4f, 0.5f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
}


Player::Player()
{
	this->initVaraibles();
	this->initTexture();
	this->initSprite();
	this->setPosition(600, 400);
}

Player::~Player()
{
}

const sf::Vector2f & Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}


void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::setMovementSpeed(float value)
{
	this->movementSpeed += value;
}

void Player::looseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::addHp(const int value)
{
	this->hp += value;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed *dirX, this->movementSpeed*dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::updateAnimations()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5f)
	{
		if (this->moving == false) //Idle animation
		{
			this->currentFrame.left += 200.f;
			if (this->currentFrame.left >= 160.f)
			{
				this->currentFrame.left = 0;
			}
		}

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}

}

//Funtions
void Player::update()
{
	this->updateAttack();
	//this->updateAnimations();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
