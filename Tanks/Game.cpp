#include"Player.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<chrono>
#include <sstream>
#include<map>
#include<string>
#include<fstream>
#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include "Game.h"


//Initializing functions
void Game::initWindow(sf::RenderWindow* window1)
{

	this->window = window1;

}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

void Game::initTextures()
{
	this->textures["SHIELD"] = new sf::Texture();
	this->textures["SHIELD"]->loadFromFile("Textures/shld.png");
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	if (!this->textures["BULLET"]->loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR::BULLET::INITTEXTURES::Could not load texture file." << "\n";
	}

	this->textures["ENEMY"] = new sf::Texture();
	this->textures["BOOST"] = new sf::Texture();
	this->backgroundMusic.play();
	this->backgroundMusic.setLoop(true);

}

void Game::initGUI()
{ 
	//Load font
	if (!this->font.loadFromFile("Fonts/joystix.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(this->window->getPosition().x*3-80.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);

	
	this->HpText.setPosition(0.f, 10.f);
	this->HpText.setFont(this->font);
	this->HpText.setCharacterSize(30);
	this->HpText.setFillColor(sf::Color::White);
	

	this->gameOVerText.setFont(this->font);
	this->gameOVerText.setCharacterSize(60);
	this->gameOVerText.setFillColor(sf::Color::Red);
	this->gameOVerText.setPosition(this->window->getSize().x / 2.f - this->gameOVerText.getGlobalBounds().width/2.f-200.f, 
		this->window->getSize().y / 2.f - this->gameOVerText.getGlobalBounds().height / 2.f-50.f);	
	this->gameOVerText.setString("Game Over!");
	

	this->waveText.setFont(this->font);
	this->waveText.setCharacterSize(60);
	this->waveText.setFillColor(sf::Color::Red);
	this->waveText.setPosition(this->window->getSize().x/2.f  - this->gameOVerText.getGlobalBounds().width / 3.f,
		10.f);
		
	this->GunOverText.setPosition(sf::Vector2f(1000.f, 730.f));
	this->GunOverText.setFont(this->font);
	this->GunOverText.setCharacterSize(20);
	this->GunOverText.setFillColor(sf::Color::White);
	this->GunOverText.setString("GUN OVERHEAT");


	//Init Player GUI
	this->playerHpBar.setSize(sf::Vector2f(100.f, 10.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(2.f, 20.f));
	

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));


	this->gunOverHeat.setSize(sf::Vector2f(this->gunOverHeatingMax, 15.f));
	this->gunOverHeat.setFillColor(sf::Color::Red);
	this->gunOverHeat.setPosition(sf::Vector2f(1000.f, 760.f));

	this->gunOverHeatBack = this->gunOverHeat;
	this->gunOverHeatBack.setFillColor(sf::Color(25, 25, 25, 200));


	this->shieldTime.setSize(sf::Vector2f(this->shieldSpawnMax, 15.f));
	this->shieldTime.setFillColor(sf::Color::Blue);


	this->shield.setPosition(sf::Vector2f(20.f, 20.f));


	this->speedTime.setSize(sf::Vector2f(this->speedSpawnMax, 15.f));
	this->speedTime.setFillColor(sf::Color::Yellow);


	this->player_Speed.setFont(this->font);
	this->player_Speed.setCharacterSize(15);
	this->player_Speed.setFillColor(sf::Color::White);
	this->player_Speed.setPosition(10, 70);

	this->enemy_Count.setFont(this->font);
	this->enemy_Count.setCharacterSize(15);
	this->enemy_Count.setFillColor(sf::Color::White);
	this->enemy_Count.setPosition(10, 100);

	this->enemy_Speed.setFont(this->font);
	this->enemy_Speed.setCharacterSize(15);
	this->enemy_Speed.setFillColor(sf::Color::White);
	this->enemy_Speed.setPosition(10, 130);

}

void Game::initWorld()
{
	if (!this->worldBacktroundTex.loadFromFile("Textures/farback.png"))
		std::cout<<"ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE";
	this->worldBackground.setTexture(this->worldBacktroundTex);

	if (!this->shieldTexture.loadFromFile("Textures/shld.PNG"))
		std::cout << "ERROR::GAME::COULD NOT LOAD SHIELD TEXTURE";
	this->shield.setTexture(this->shieldTexture);
}

void Game::initSystems()
{
	this->points = 0;
	this->wavePoints = 0;
}

void Game::initSounds()
{
	if (!this->bulletBuffer.loadFromFile("Sounds/Laser2.wav"))
	{
		std::cout << "GAME::ERROR::LASER.WAV - COULDN'T LOAD FILE" << "\n";
	}
	this->bulletSounds.setBuffer(bulletBuffer);
	this->bulletSounds.setVolume(10.f);

	if (!this->enemyBuffer.loadFromFile("Sounds/enemy.wav"))
	{
		std::cout << "GAME::ERROR::ENEMY.WAV - COULDN'T LOAD FILE" << "\n";
	}
	this->enemySound.setBuffer(enemyBuffer);
	this->enemySound.setVolume(2.f);

	if (!this->backgroundMusic.openFromFile("Sounds/Background.wav"))
	{
		std::cout << "GAME::ERROR::Background.WAV - COULDN'T LOAD FILE" << "\n";
	}
	this->backgroundMusic.setVolume(20.f);

	if (!this->gameOverMusic.openFromFile("Sounds/Gameover.wav"))
	{
		std::cout << "GAME::ERROR::GAMEOVER.WAV - COULDN'T LOAD FILE" << "\n";
	}
	this->gameOverMusic.setVolume(10.f);

	if (!this->playerHitBuffer.loadFromFile("Sounds/enemy.wav"))
	{
		std::cout << "GAME::ERROR::ENEMY.WAV - COULDN'T LOAD FILE" << "\n";
	}
	this->playerHitSound.setBuffer(enemyBuffer);
	this->playerHitSound.setVolume(20.f);
}

void Game::initVariables()
{
	this->waveCounter = 1;
	this->enemyCounter = 0;
	this->enemyCounterWave = 0;
	this->enemyCounterMax = 10;
	this-> game_over = false;
	this->EnemySpeed = 2;
	this->gunOverHeating = 0;
	this->gunOverHeatingMax = 160;
}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 100.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initBoosts()
{
	this->boostSpawnMax = 500.f;
	this->boostSpawn= this->boostSpawnMax;
	this->shieldSpawnMax = 70.f;
	this->shieldSpawn = 0;
	this->shielded = false;
	this->speedSpawnMax = 50.f;
	this->speedSpawn = 0;
	this->boosted = false;
}




//Constructors/Destructors
Game::Game(sf::RenderWindow* window1,std::string nick)
{
	this->initWindow(window1);
	this->initVariables();
	this->initStates();
	this->initGUI();
	this->initSounds();
	this->initTextures();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
	this->initBoosts();
	this->Nick = nick;
}


Game::~Game()
{
	for (auto *i : this->enemies)
	{
		delete i;
	}

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}


	delete this->player;

	//Remove textures
	for (auto &i : this->textures)
	{
		delete i.second; 
	}

	//Delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//Delete boosts
	for (auto* i : this->boosts)
	{
		delete i;
	}

}

//Functions
void Game::endApplication()
{
	std::cout << "Ending" << "\n";
}


//Update Functions
void Game::updateDt()
{
	this->dt = this->dtClock.getElapsedTime().asSeconds();
}


void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();	
		}
			
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::LAlt)
		{
			this->player->setHp(1);
		}

		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::M)
		{
			this->backgroundMusic.pause();
		}
	}
}

void Game::updateInput()
{

	//Move player
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
	{
		this->player->move(-1.f, 0.f);
		this->player->moving = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
	{
		this->player->move(1.f, 0.f);
		this->player->moving = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
	{
		this->player->move(0.f, -1.f);
		this->player->moving = true;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)))
	{
		this->player->move(0.f, 1.f);
		this->player->moving = true;
	}
		

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack() && (this->gunOverHeating<this->gunOverHeatingMax))
	{
		this->gunOverHeating += 10;

		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x + this->player->getBounds().width / 5.f+15.f,
			this->player->getPos().y,
			0.f,
			-1.f,
			5.f
		));
		this->bulletSounds.play();
		
	}
	
}

void Game::updateGUI()
{
	std::stringstream ss, ss2, ss4, ss5, ss6;
	std::string temp;

	ss << "Points "<<this->points;
	this->pointText.setString(ss.str());

	ss4 << "Speed " << this->player->getPlayerSpeed();
	this->player_Speed.setString(ss4.str());

	ss5 << "Enemy Speed " << this->EnemySpeed;
	this->enemy_Speed.setString(ss5.str());

	ss6 << "Enemies " << this->enemyCounterMax;
	this->enemy_Count.setString(ss6.str());


	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(100.f * hpPercent, this->playerHpBar.getSize().y));
	this->playerHpBar.setPosition(sf::Vector2f(this->player->getPos().x-(this->player->getBounds().width/4.f)+3.5, this->player->getPos().y+(this->player->getBounds().height)));
	
	float OverHeatPercent = static_cast<float>(this->gunOverHeating / this->gunOverHeatingMax);
	this->gunOverHeat.setSize(sf::Vector2f(150.f * OverHeatPercent, this->gunOverHeatBack.getSize().y));

	if (shielded)
	{
	float ShieldTimePercent = static_cast<float>((this->shieldSpawnMax - this->shieldSpawn) / this->shieldSpawnMax);
	this->shieldTime.setSize(sf::Vector2f(70.f * ShieldTimePercent, 5.f));
	this->shieldTime.setPosition(sf::Vector2f(this->player->getPos().x - (this->player->getBounds().width / 4.f)+3.5f, this->player->getPos().y + (this->player->getBounds().height)+10.f));

	}

	if (boosted)
	{
		float SpeedTimePercentage = static_cast<float>((this->speedSpawnMax - this->speedSpawn) / this->speedSpawnMax);
		this->speedTime.setSize(sf::Vector2f(70.f * SpeedTimePercentage, 5.f));
		this->speedTime.setPosition(sf::Vector2f(this->player->getPos().x - (this->player->getBounds().width / 4.f) + 3.5, this->player->getPos().y + (this->player->getBounds().height) + 20.f));
	}
	

	this->shield.setPosition(sf::Vector2f(this->player->getPos().x-35, this->player->getPos().y-20 ));

	ss2 << "HP " << this->player->getHp();
	this->HpText.setString(ss2.str());

	std::stringstream ss3;
	if (this->waveCounter==1 and this->dt > 5.0)
	{
		ss3 << "";
	}
	else if (this->dt < 2.0)
	{
		ss3 << "WAVE " << this->waveCounter;
	}
	this->waveText.setString(ss3.str());
	
}

void Game::updateWorld(){}

void Game::updateCollision()
{
	//left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(1.f, this->player->getBounds().top);
	}

	//right world collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x )
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//bottom world collision
	else if (this->player->getBounds().top +this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition( this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->update();
		
		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Bullet deletion
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
	if(this->gunOverHeating-0.2 > 0)
		this->gunOverHeating -= 0.2;

}

void Game::updateGame()
{
	if(this->enemyCounter == 0 and this->enemyCounterWave == this->enemyCounterMax)
	{
		//wavePoints = 0;
		this->enemyCounterWave = 0;
		this->dtClock.restart();
		this->waveCounter++;
		//std::cout << "NEW WAVE ";
		this->EnemySpeed += 0.4;
		this->player->setMovementSpeed(0.2);

		this->enemyCounterMax += 1;	
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted==false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();
				
				if (this->waveCounter > 1)
				{
					this->wavePoints = points - (100 * (this->waveCounter-1))+1;
				}
				else
				{
					this->wavePoints = points;
				}
	

				this->enemyCounter--;
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				this->enemySound.play();

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}

	}
}

void Game::updateBoosts()
{
	//Spawning
	if (shielded == true)
	{
		shieldSpawn += 0.1;
		if (shieldSpawn >= shieldSpawnMax)
		{
			shielded = false;
			shieldSpawn = 0;
		}
	}
	if (boosted == true)
	{
		speedSpawn += 0.1;
		if (speedSpawn >= speedSpawnMax)
		{
			boosted = false;
			this->player->setMovementSpeed(-0.5);
			speedSpawn = 0;
		}
	}

	this->boostSpawn += 0.5f;
	if (this->boostSpawn >= this->boostSpawnMax)
	{
		this->boosts.push_back(new Boost(rand() % this->window->getSize().x - 20.f, -100.f));
		this->boostSpawn = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* boost : this->boosts)
	{
		boost->update();
		//Bullet culling (top of screen)
		if (boost->getBounds().top > this->window->getSize().y)
		{
			//Enemy deletion
			delete this->boosts.at(counter);
			this->boosts.erase(this->boosts.begin() + counter);

			//--counter;
		}
		//Enemey-player collison
		else if (boost->getBounds().intersects(this->player->getBounds()))
		{
			if (boost->getType() == 1)
			{
				this->player->addHp(5);
			}
			else if (boost->getType() == 2)
			{
				this->boosted = true;
				this->player->setMovementSpeed(0.7);
			}
			else if (boost->getType() == 3)
			{
				this->shieldSpawn = 0;
				this->shielded = true;
			}
			
			delete this->boosts.at(counter);
			this->boosts.erase(this->boosts.begin() + counter);

		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax and (this->enemyCounterWave<this->enemyCounterMax))
	{
		this->enemies.push_back(new Enemy((rand()%this->window->getSize().x-60)+20.f,-50.f,this->EnemySpeed));
		this->spawnTimer = 0.f;
		this->enemyCounter++;
		this->enemyCounterWave++;
	}
		
	//Update
	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Deleting Player HP
			this->player->looseHp(5);
			this->playerHitSound.play();

			//Enemy deletion
			this->enemyCounter--;
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			
		}
		//Enemey-player collison
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//std::cout << "ENEMY COLIDED" << "\n";
			this->enemyCounter--;
			if (!shielded)
			{
				this->player->looseHp(this->enemies.at(counter)->getDamage());
				this->playerHitSound.play();
			}			
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			
		}

		++counter;
	}

}



void Game::update()
{
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else //Applications end
	{
		this->endApplication();
		this->window->close();
	}


	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateGame();
	this->updateBullets();

	this->updateEnemies();

	this->updateBoosts();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();

}


void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->GunOverText);
	this->window->draw(this->HpText);
	this->window->draw(this->playerHpBar);
	this->window->draw(this->gunOverHeatBack);
	this->window->draw(this->gunOverHeat);
	this->window->draw(this->shieldTime);
	this->window->draw(this->shieldTimeBack);
	this->window->draw(this->speedTime);
	this->window->draw(this->waveText);
	this->window->draw(this->player_Speed);
	this->window->draw(this->enemy_Speed);
	this->window->draw(this->enemy_Count);
	
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->clear();

	//Draw background
	this->renderWorld();

	
	//Render items
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* boost : this->boosts)
	{
		boost->render(this->window);
	}

	this->renderGUI();

	if (shielded)
	{
		this->window->draw(this->shield);
	}



	//Game over screen
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->gameOVerText);
		this->backgroundMusic.pause();


		if (!this->game_over)
		{
			//Zapisywanie wyniku do pliku
			this->gameOverMusic.play();
			std::fstream scoreboard_out;
			scoreboard_out.open("scoreboard.txt", std::ios::app);
			scoreboard_out << this->waveCounter << ";" << this->points<<";"<<this->Nick<<";";

			scoreboard_out.close();
			this->game_over = true;
		}
	

		std::stringstream out1;
		out1 << "RANKING" << "\n";
		
		if (game_over and !this->end) //wypisanie wyników do pliku
		{

			std::fstream scoreboard_in;
			scoreboard_in.open("scoreboard.txt", std::ios::in);

			int waves, pkt;
			while (!scoreboard_in.eof())
			{
				std::string text, text2,text3;
				getline(scoreboard_in, text, ';');//points
				getline(scoreboard_in, text2,';');//waves
				getline(scoreboard_in, text3,';');//waves

				if (text != "" and text2 != "")
				{
					pkt = stoi(text);
					waves = stoi(text2);
					this->Scores.push_back(std::pair<std::pair<int, int>,std::string>(std::make_pair(pkt, waves),text3));
				}
			}
			scoreboard_in.close();

		}
			std::sort(this->Scores.begin(), this->Scores.end(), [](auto& left, auto& right) {return left.first.second > right.first.second; });
			std::string txt3, txt4, txt5;
			int txt1, txt2;

			if (!end)
			{
				auto it = Scores.begin();
				for (int i = 0; i < 6; i++)
				{
					txt1 = (*it).first.first;
					txt2 = (*it).first.second;
					txt5 = (*it).second;
					txt3 = std::to_string(txt2);

					//std::cout << "FALA: " << txt1 << " PUNKTY: " << txt2 << " NICK: "<<txt5<<"\n";
					++it;
				}
			}
			

			

			std::vector<std::pair<std::pair<int, int>, std::string>>::iterator it2;
			it2 = this->Scores.begin();
			for (int i=0;i<6;i++)
			{
				this->scoreboard1.setFont(this->font);
				this->scoreboard1.setCharacterSize(25);
				this->scoreboard1.setFillColor(sf::Color::White);
				this->scoreboard1.setPosition(this->window->getSize().x / 2.f - this->scoreboard1.getGlobalBounds().width / 2.f,
					this->window->getSize().y / 2.f - this->scoreboard1.getGlobalBounds().height / 2.f + 180.f);

				txt1 = (*it2).first.first;
				txt2 = (*it2).first.second;
				txt5 = (*it2).second;
				txt3 = std::to_string(txt2);//waves
				txt4 = std::to_string(txt1);//points

				out1 << "FALA: " << txt4<<" PKT: "<<txt3<<" "<<txt5<<"\n";
				
				++it2;
				
			}
			
			this->scoreboard1.setString(out1.str());
			this->window->draw(this->scoreboard1);
			
			end = true;
			

		this->window->display();
	}
	else
	{
	this->window->display();
	}


}

void Game::run(sf::RenderWindow &window2)
{
	while (window2.isOpen())
	{
		this->updateDt();
		this->updatePollEvents();

		if(this->player->getHp()>0)
			this->update();
		
		this->render();
	}
}
