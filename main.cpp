#include<iostream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML\Audio.hpp>0.
#include<cstdlib>
#include<time.h>
#include<string>
#include<vector>
#include "menu.h"

using namespace sf;
using namespace std;

int ms = 1;

//------------------------------------game function----------------------------------------------------//

void game();
void options();

//-----------------------------------------------------------------------------------------------------//

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(900, 900), "Beat Corona");//window
	window.setFramerateLimit(60);

	menu Menu(window.getSize().x, window.getSize().y);//menu window
	//Font

	Font font;
	font.loadFromFile("Fonts/Font.ttf");

	//don't

	RectangleShape r;
	r.setFillColor(Color::Red);
	r.setSize(Vector2f(30, 30));
	r.setPosition(50.f, window.getSize().y - r.getSize().y - 50.f);

	Text t;
	t.setFont(font);
	t.setCharacterSize(22);
	t.setString("Don't hit this red bombs !!!!");
	t.setPosition(100.f, window.getSize().y - r.getSize().y - 50.f);

	//backGround
	
	Texture bg;
	bg.loadFromFile("Textures/bg5.jpg");
	Sprite back;
	back.setTexture(bg);
	back.setPosition(Vector2f(150.f, 3.f));
	back.setScale(2,2);


	//high score

	int line;

	ifstream read_hiscore;
	read_hiscore.open("HighScore.txt");
	read_hiscore >> line;
	read_hiscore.close();

	Text hs;
	hs.setFont(font);
	hs.setCharacterSize(22);

	//-----------------------------game loop---------------------------------------------------------------//
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased :
				switch (event.key.code)
				{
				case Keyboard::Up:
					Menu.MoveUp();
					break;

				case Keyboard::Down:
					Menu.MoveDown();
					break;

				case Keyboard::Return:
					switch (Menu.getPressedItem())
					{
					case 0:
						game();
						break;
					case 1:
						options();
						break;
					case 2:
						window.close();
						break;
					}
				}
				break;

			case Event::Closed:
				window.close();
				break;
			}
			//Hiscore update
			hs.setString("High Score : " + to_string(line));
		}

		window.clear();
		//draw
		window.draw(back);
		Menu.draw(window);
		window.draw(hs);
		window.draw(r);
		window.draw(t);

		window.display();
	}
	

	return 0;
}

//----------------------game function defination------------------------------------------//
void game()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(900, 900), "Beat Corona");
	window.setFramerateLimit(60);

	//background sound

	SoundBuffer s;
	s.loadFromFile("Sound/back_ground.wav");

	Sound bg;
	bg.setBuffer(s);
	
	if (ms == 1)
		bg.play();

	//backGround

	Texture bg2;
	bg2.loadFromFile("Textures/bgk.jfif");
	Sprite game_bg;
	game_bg.setTexture(bg2);
	game_bg.setPosition(Vector2f(70.f, 190.f));
	game_bg.setScale(4, 4);

	//Font

	Font font;
	font.loadFromFile("Fonts/Font.ttf");

	//Text

	int Display_score = 0;

	Text text;
	text.setFont(font);
	text.setCharacterSize(18);

	//high score
	int hs;

	ifstream read_hiscore;
	read_hiscore.open("HighScore.txt");
	read_hiscore >> hs;
	read_hiscore.close();

	//gameover text

	Text gameOver1;
	gameOver1.setFont(font);
	gameOver1.setCharacterSize(22);
	gameOver1.setPosition(190.f, 300.f);
	gameOver1.setString("You are corona positive !!");
	gameOver1.setFillColor(Color::Red);

	Text gameOver2;
	gameOver2.setFont(font);
	gameOver2.setCharacterSize(22);
	gameOver2.setPosition(35.f, 600.f);
	gameOver2.setString("Press (Esc) to go to hospital [menu]!");
	gameOver2.setFillColor(Color::White);

	//Balls(bullets)


	CircleShape projectile;
	projectile.setFillColor(Color::Red);
	projectile.setRadius(5.f);


	//enemy
	Texture corona;
	corona.loadFromFile("Textures/corona.png");

	RectangleShape enemy;
	enemy.setTexture(&corona);
	enemy.setSize(Vector2f(50.f, 50.f));

	float enemy_size[4] = { 80.f,200.f,35.f,300.f };
	int index = 0;

	//player
	Texture player_tex;
	player_tex.loadFromFile("Textures/Spaceship.png");

	Sprite player;
	player.setTexture(player_tex);
	player.setScale(0.12f,0.12f);
	player.setPosition(250.f, 800.f);

	Vector2f playerCenter;

	int shootTimer = 0;
	int enemySpawn = 0;
	int hp = 5;

	//life
	Texture life;
	life.loadFromFile("Textures/life.png");

	Sprite life_symbol;
	life_symbol.setTexture(life);
	life_symbol.setPosition(800.f, 0.f);
	life_symbol.setScale(0.1f,0.1f);

	Text life_numbers;
	life_numbers.setFont(font);
	life_numbers.setCharacterSize(20);
	life_numbers.setPosition(850.f, 5.f);

	//bomb
	RectangleShape bomb;
	bomb.setFillColor(Color::Red);
	bomb.setSize(Vector2f(50.f, 50.f));

	int bombSpawn = 0;

	//vectors
	vector<CircleShape> projectiles;
	projectiles.push_back(CircleShape(projectile));

	vector<RectangleShape> enemies;
	enemies.push_back(RectangleShape(enemy));

	vector<RectangleShape> bombs;
	bombs.push_back(RectangleShape(bomb));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (hp > 0)
		{
			//update


			playerCenter = Vector2f(player.getPosition().x + 40.f, player.getPosition().y);//for bullets

			if (shootTimer < 7)
				shootTimer++;

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				player.move(-8.f, 0);
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				player.move(8.f, 0);
			}

			if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 7)
			{
				projectile.setPosition(playerCenter);
				projectiles.push_back(CircleShape(projectile));
				shootTimer = 0;
			}

			//player position
			if (player.getPosition().x <=0)
			{
				player.setPosition(0.f,player.getPosition().y);
			}

			if (player.getPosition().x > window.getSize().x - player.getGlobalBounds().width)
			{
				player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
			}

			//update projectiles

			for (size_t i = 0; i < projectiles.size(); i++)
			{
				projectiles[i].move(0, -10.f);

			}

			//update enemy
			int time = 90;

			if (enemySpawn < time)
			{
				enemySpawn++;
				index++;
			}
			if (index >= 4)
			{
				index = 0;
			}

			if (enemySpawn >= time)
			{
				enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0);
				enemy.setSize(Vector2f(enemy_size[index], enemy_size[index]));
				enemies.push_back(RectangleShape(enemy));

				enemySpawn = 0;
			}
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].move(0, 5.f);

				if (enemies[i].getPosition().y > 750.f)
				{
					hp--;
					enemies.erase(enemies.begin());
				}
			}

			//update bombs
			if (bombSpawn < 200)
				bombSpawn++;

			if (bombSpawn >= 200)
			{
				bomb.setPosition(rand() % int(window.getSize().x - bomb.getSize().x),0);
				bombs.push_back(RectangleShape(bomb));

				bombSpawn = 0;
			}

			for (size_t i = 0; i < bombs.size(); i++)
			{
				bombs[i].move(0, 5.f);

				if (bombs[i].getPosition().y > 750.f)
				{
					bombs.erase(bombs.begin());
				}
			}
			
			//score update
			text.setString("Score : " + to_string(Display_score));

			//life update
			life_numbers.setString(to_string(hp));

			//enemy collision 
			for (size_t i = 0; i < projectiles.size(); i++)
			{
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
					{
						//kill.play();
						projectiles.erase(projectiles.begin() + i);
						enemies.erase(enemies.begin() + k);
						Display_score += 10;
						break;
					}
				}
			}

			//bombs collision 
			for (size_t i = 0; i < projectiles.size(); i++)
			{
				for (size_t k = 0; k < bombs.size(); k++)
				{
					if (projectiles[i].getGlobalBounds().intersects(bombs[k].getGlobalBounds()))
					{
						projectiles.erase(projectiles.begin() + i);
						bombs.erase(bombs.begin() + k);
						hp--;
						break;
					}
				}
			}

		}

		//returning to menu
		if (hp <= 0)
		{
			bg.stop();
			//update high score
			if (Display_score > hs)
			{
				ofstream o;
				o.open("HighScore.txt");
				o << Display_score;
				o.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}

		window.clear();
		//draw
		
		window.draw(game_bg);

		window.draw(life_symbol);

		window.draw(text);

		window.draw(life_numbers);

		window.draw(player);

		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}

		for (size_t i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i]);
		}

		for (size_t i = 0; i < bombs.size(); i++)
		{
			window.draw(bombs[i]);
		}

		//game over

		if (hp <= 0)
		{
			window.draw(gameOver1);
			window.draw(gameOver2);
		}
		window.display();
	}
}

void options()
{
	RenderWindow window(VideoMode(900, 900), "Options");
	window.setFramerateLimit(60);
	//Font

	Font font;
	font.loadFromFile("Fonts/Font.ttf");

	Text o;
	o.setFont(font);
	o.setCharacterSize(22);
	o.setString("Music : ");
	o.setPosition(100.f, 450.f);

	Text m;
	m.setFont(font);
	m.setCharacterSize(22);
	m.setString("ON ");
	m.setFillColor(Color::Green);
	m.setPosition(750.f, 450.f);

	Text of;
	of.setFont(font);
	of.setCharacterSize(22);
	of.setString("OFF ");
	of.setFillColor(Color::Red);
	of.setPosition(750.f, 450.f);

	bool l = true;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//update
		window.clear();

		window.draw(o);

		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case Keyboard::Up:
				window.draw(m);
				ms = 1;
				break;
			case Keyboard::Down:
				window.draw(of);
				ms = 0;
				break;
			}
		}

		window.display();
	}
}