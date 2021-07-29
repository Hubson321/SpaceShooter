#ifndef GAME_H
#define GAME_H

#include"Player.h"
#include<map>
#include<string>
#include"Bullet.h"
#include"Boost.h"
#include"Enemy.h"
#include<string>
#include<vector>
#include<sstream>
#include"GameState.h"
#include<algorithm>
#include"MainMenuState.h"


class Game 
{
private:
	//Window
	sf::RenderWindow* window;
	

	//Recources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	

	//Variables
	std::stack<State*> states;
	sf::Clock dtClock;
	float dt;
	int waveCounter;
	int enemyCounter;
	int enemyCounterWave;
	int enemyCounterMax;
	bool game_over;
	std::string Nick;

	bool end = false;

	//Sounds
	sf::SoundBuffer bulletBuffer;
	sf::Sound bulletSounds;

	sf::SoundBuffer enemyBuffer;
	sf::Sound enemySound;

	sf::Music backgroundMusic;

	sf::Music gameOverMusic;

	sf::SoundBuffer playerHitBuffer;
	sf::Sound playerHitSound;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text HpText;
	sf::Text gameOVerText;
	sf::Text waveText;
	sf::Text scoreboard1;
	sf::Text scoreboard2;
	sf::Text enemy_Speed;
	sf::Text enemy_Count;
	sf::Text player_Speed;
	sf::Text GunOverText;

	
	

	//std::vector<std::string> Scores;
	std::vector<std::pair<std::pair<int,int>,std::string>> Scores;

	
	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	sf::RectangleShape gunOverHeat;
	sf::RectangleShape gunOverHeatBack;

	sf::RectangleShape shieldTime;
	sf::RectangleShape shieldTimeBack;

	sf::RectangleShape speedTime;

	//Player
	Player* player;
	float gunOverHeating;
	float gunOverHeatingMax;



	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	float EnemySpeed;

	//Boosts
	float boostSpawn;
	float boostSpawnMax;
	std::vector<Boost*> boosts;
	bool shielded;
	float shieldSpawn;
	float shieldSpawnMax;
	sf::Sprite shield;
	sf::Texture shieldTexture;

	float speedSpawn;
	float speedSpawnMax;
	bool boosted;
	

	//Systems
	int points;
	int wavePoints;


	//Initializers
	void initWindow(sf::RenderWindow* window1);
	void initStates();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initSounds();
	void initVariables();
	void initPlayer();
	void initEnemies();
	void initBoosts();


public:
	//Constructors/Destructors
	sf::View View;
	sf::FloatRect fBounds;
	sf::IntRect iBounds;
	sf::Vector2f viewStart;
	sf::Vector2f spriteStart;

	//World 
	sf::Sprite worldBackground;
	sf::Texture worldBacktroundTex;

	Game(sf::RenderWindow* window1,std::string nick);
	virtual ~Game();
	
	//Functions
	void endApplication();

	//Update functions
	void updateDt();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateGame();
	void updateEnemies();
	void updateCombat();
	void updateBoosts();
	void update();

	//Render Functions
	void renderGUI();
	void renderWorld();
	void render();
	void run(sf::RenderWindow& window2);

};

#endif //!GAME_H