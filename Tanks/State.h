#ifndef STATE_H
#define STATE_H

#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<stack>
#include<map>

#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include<fstream>
#include<sstream>

class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool &getQuit() const;
	bool quit;

	virtual void checkForQuit();
	virtual void endState()=0;

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt)=0;
	virtual void render(sf::RenderTarget* target = nullptr)=0;
};

#endif
