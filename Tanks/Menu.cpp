#include "Menu.h"

Menu::Menu(float width, float height)
{

	//this->backgroundMusic.setLoop(true);

	if (!font.loadFromFile("Fonts/joystix.ttf"))
	{
		std::cout << "FONT DIDNT LOAD" << std::endl;
	}

	if (!buffer.loadFromFile("Sounds/button-3.wav"))
	{
		std::cout << "SOUND DIDNT LOAD" << std::endl;
	}

	button.setBuffer(buffer);
	button.setVolume(10.f);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color(42,157,244,255));
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2 - 50, height / (MAAX_NUMBERS_OF_ITEMS+1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(width / 2 - 50, height / (MAAX_NUMBERS_OF_ITEMS+1) * 2));


	selectedItemIndex = 0;


}

void Menu::draw(sf::RenderWindow& window)
{
	
	
	sf::Sprite Menu_back;
	sf::Texture Menu_backTex;

	if (!Menu_backTex.loadFromFile("Textures/menubackgrounds.jpg"))
		std::cout << "DIDNT LOAD" << std::endl;
	Menu_back.setTexture(Menu_backTex);
	window.draw(Menu_back);

	for (int i = 0; i < MAAX_NUMBERS_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(42,157,244,255));
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 <MAAX_NUMBERS_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(42, 157, 244, 255));
	}
}

std::string Menu::putNick(sf::RenderWindow *window)
{
	sf::Event ev;
	bool keyPressed = false;

		while (!keyPressed)
		{
			while (window->pollEvent(ev))
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					userInput.insert(userInput.getSize(), ev.text.unicode);

				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					this->userInput.erase(userInput.getSize() - 1);
				}

				this->temp.setString("Zapisz sie: " + userInput);
				window->draw(temp);
				window->display();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					keyPressed = true;
			}
		}

		return userInput;
}

