#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) 
	: State(window)
{

}

GameState::~GameState()
{

}


void GameState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::initKeybinds()
{
	
}

void GameState::updateInput(const float &dt)
{
	this->checkForQuit();

	//Move player
	


}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//std::cout << "A" << "\n";
}

void GameState::render(sf::RenderTarget* target)
{

}
