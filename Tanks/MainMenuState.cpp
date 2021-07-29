#include "MainMenuState.h"




MainMenuState::MainMenuState(sf::RenderWindow* window)
	: State(window)
{
	this->background.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{

}


void MainMenuState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void MainMenuState::updateKeybinds(const float &dt)
{
	this->checkForQuit();


}

void MainMenuState::update(const float& dt)
{
	this->updateKeybinds(dt);
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//std::cout << "" << "\n";
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
}
