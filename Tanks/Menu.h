#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"

#define MAAX_NUMBERS_OF_ITEMS 2
class Menu
{
public:
	
	Menu(float width,float height);
	~Menu() {};

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; };
	sf::Sound button;
	sf::SoundBuffer buffer;

	sf::String userInput;
	sf::Text temp;


	std::string putNick(sf::RenderWindow* window);
	



private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAAX_NUMBERS_OF_ITEMS];

};

