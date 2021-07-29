#include "Game.h"
#include<time.h>
#include"Menu.h"
#include<iostream>
#include<fstream>

int main()
{
	srand(time(static_cast<unsigned>(0)));
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Space Shooter");
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(false);


	Menu menu(window.getSize().x, window.getSize().y);

	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					menu.button.play();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					menu.button.play();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
					{
						//std::cout << "Play button has been pressed" << std::endl;
						

						sf::String userInput;
						sf::Text temp;
						sf::Font font;
						font.loadFromFile("Fonts/joystix.ttf");
						temp.setFont(font);
						temp.setFillColor(sf::Color(25, 25, 25, 200));
						temp.setCharacterSize(40.0f);
						temp.setPosition(200, 400);

						bool keyPressed = false;
						

						while (window.isOpen() and !keyPressed) 
						{
							sf::Event event;

							for (int i = 0; i < 1; i++)
							{
								temp.setString("Zapisz sie: " + userInput);
								window.draw(temp);
								window.display();
							}
							

							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::TextEntered)
								{
									if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
										userInput.insert(userInput.getSize(), event.text.unicode);
								}
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) // delete the last character
								{
									userInput.erase(userInput.getSize() - 1);

								}

								
								window.draw(temp);
								window.display();
								if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
								{
									keyPressed = true;

								}
							}
						}

						std::string test;
						test = userInput;


						Game game(&window,test);
						
						game.run(window);
						window.close();
						
					}
						
					case 1:
						window.close();
						
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		menu.draw(window);

		window.display();
	}
	
	

	return 0;
}