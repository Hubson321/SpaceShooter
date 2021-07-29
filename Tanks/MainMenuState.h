#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "State.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;

public:
	MainMenuState(sf::RenderWindow* window);
	virtual ~MainMenuState();

	//Functions
	void endState();

	void initKeybinds();
	void updateKeybinds(const float &dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};


#endif