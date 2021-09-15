/* 
Youssef Helal
Sokoban*/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <stdlib.h>
#include<fstream>
#include <string>
#define rows 10
#define cols 10
int const h = 50; // to set height of tile. Also for upward movement
int const w = 50; // to set width of tile. Also for sideways movement
float const e = 5; //to set position of tiles
int const r = 30; ////to set position of tiles
using namespace std;
void loadMap(sf::RectangleShape map[][cols], char m[][cols], sf::Texture wall, sf::Texture floor);
void setmap(char m[][cols], char z[][cols], char x[][cols], string s, int &p1, int &p2, string &solution, int&, int&);
string checkLevel(bool, bool, bool, bool, bool);

void main()
{
	int p1, p2, n, marks;
	sf::Vector2f c;
	char x[rows][cols];
	char m[rows][cols];
	char z[rows][cols];
	sf::RenderWindow win;                                         //window
	win.create(sf::VideoMode(1920, 1080), "Sokoban");
	sf::RectangleShape map[rows][cols];
	sf::Texture player1;
	sf::Sprite Psprite;
	for (int i = 0; i < rows; i++)
	for (int j = 0; j < cols; j++)
		m[i][j] = ' ';

	
	if (!player1.loadFromFile("player.png"))
	{
		cout << "Error player image not loaded";
	}
	Psprite.setTexture(player1);
	Psprite.setScale(sf::Vector2f(0.8, 0.8));



	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j].setSize(sf::Vector2f(h, w));
			//map[i][j].setFillColor(sf::Color::Black);
			map[i][j].setPosition((i*h + e) + r, (j*w + e) + r);
			//map[i][j].setOutlineColor(sf::Color::White);                //To see outlines and make sure everything is right
			//	map[i][j].setOutlineThickness(1);
		}
	}

	sf::Texture floor;
	if (!floor.loadFromFile("Ground.png"))
	{
		cout << "Error floor image not loaded";
	}
	sf::Texture wall;
	if (!wall.loadFromFile("stone.png"))
	{
		cout << "Error wall image not loaded";
	}
	sf::Texture crates;
	if (!crates.loadFromFile("crates.png"))
	{
		cout << "Error crate image not loaded";
	}
	sf::Sprite crate[6];


	// sokoban.loadCrates();

	bool isRunning = false;
	bool level1 = true;
	bool level2 = false;
	bool level3 = false;
	bool level4 = false;
	bool level5 = false;




	string s, y, solution;
	while (win.isOpen())
	{
		s = checkLevel(level1, level2, level3, level4, level5);

		setmap(m, z, x, s, p1, p2, solution, n, marks);
		c = map[p2][p1].getPosition();

		/*	int v = 0;
		for (int i = 0; i < n; i++)
		{
		crate[i].setTexture(crates);
		crate[i].setScale(sf::Vector2f(1.31f, 1.31f));
		}



		for (int i = 0; i < rows;i++)
		for (int j = 0; j < cols; j++)
		{
		if (z[i][j] == 'B')
		{
		crate[v].setPosition(map[j][i].getPosition());
		v++;
		}
		}*/

		for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (m[i][j] == '#')
			{
				map[j][i].setTexture(&wall);
			}
			if (m[i][j] == '.')
			{
				map[j][i].setTexture(&floor);
			}
			if (m[i][j] == ' ')
				map[j][i].setFillColor(sf::Color::Black);

		}



		sf::Event myevent;
		while (win.pollEvent(myevent))
		{


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  //to restart
			{
				if (!isRunning)
				{
					isRunning = true;

					for (int i = 0; i < rows; i++)
					{
						for (int j = 0; j < cols; j++)
						{
							map[i][j].setSize(sf::Vector2f(h, w));
							//map[i][j].setFillColor(sf::Color::Black);
							map[i][j].setPosition((i*h + e) + r, (j*w + e) + r);
							//map[i][j].setOutlineColor(sf::Color::White);                //To see outlines and make sure everything is right
							//	map[i][j].setOutlineThickness(1);
						}
					}
					Psprite.setPosition(c);
					if (!crates.loadFromFile("crates.png"))
					{
						cout << "Error crate image not loaded";
					}
					int v = 0;
					for (int i = 0; i < n; i++)
					{
						crate[i].setTexture(crates);
						crate[i].setScale(sf::Vector2f(1.31f, 1.31f));
					}



					for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
					{
						if (z[i][j] == 'B')
						{
							crate[v].setPosition(map[j][i].getPosition());
							v++;
						}
					}

				}


			}
			if (myevent.type == sf::Event::Closed)         //close game if x is clicked
				win.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))           //close game if ESC keys is pressed
				win.close();
			if (isRunning)
			{
				if (sf::Keyboard::isKeyPressed)
				{
					int a, b;
					sf::Vector2f y;
					y = Psprite.getPosition();
					a = ((y.x - (e + r)) / w);
					b = ((y.y - (e + r)) / w);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m[b][a + 1] != '#')
						Psprite.move(w, 0);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m[b][a - 1] != '#')
						Psprite.move(-w, 0);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m[b + 1][a] != '#')
						Psprite.move(0, h);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m[b - 1][a] != '#')
						Psprite.move(0, -h);

				}
				int a, b;
				sf::Vector2f y;
				y = Psprite.getPosition();
				a = ((y.x - (e + r)) / w);
				b = ((y.y - (e + r)) / w);




				for (int i = 0; i < n; i++)
				{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && Psprite.getGlobalBounds().intersects(crate[i].getGlobalBounds()))
				crate[i].move(w, 0);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && Psprite.getGlobalBounds().intersects(crate[i].getGlobalBounds()))
				crate[i].move(-w, 0);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Psprite.getGlobalBounds().intersects(crate[i].getGlobalBounds()))
				crate[i].move(0, h);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Psprite.getGlobalBounds().intersects(crate[i].getGlobalBounds()))
				crate[i].move(0, -h);

				}
			}

			win.clear(sf::Color::Black);
			if (isRunning)
			{

				for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
				{

					win.draw(map[i][j]);
				}

				win.draw(Psprite);
				for (int i = 0; i < n; i++)
				{

					win.draw(crate[i]);
				}
			}

			win.display();
		}
	}
}


void setmap(char m[][cols], char z[][cols], char q[][cols], string s, int &p1, int &p2, string &solution, int &crate, int &marks)
{
	crate = 0;
	char a = 'a', b;
	int c, d;
	int i, j = 0;
	string y;
	ifstream x;
	x.open(s);
	if (x.fail())
		cout << "Error" << EXIT_FAILURE;
	else
	{
		while (!x.eof() && y != "Boxes:")
		{

			getline(x, y);

			for (i = 0; i < y.length(); i++)
			{
				switch (y[i])
				{
				case '#':m[j][i] = '#'; break;
				case '.':m[j][i] = '.'; break;
				case ' ':m[j][i] = ' '; break;
				}
			}
			j++;

		}

		while (!x.eof() && a != 'M')
		{


			x >> a;
			x >> b;
			if (a != 'M')
			{
				c = a - '0';
				d = b - '0';
				z[c][d] = 'B';
				crate++;
			}

		}
		x.ignore(4);
		while (!x.eof() && a != 'P')
		{

			x >> a;
			x >> b;
			if (a != 'P')
			{
				c = a - '0';
				d = b - '0';
				z[c][d] = 'M';
				marks++;
			}
		}
		x.ignore(6);
		while (!x.eof() && a != 'S')
		{

			x >> p1;
			x >> p2;
			x >> a;
		}
		while (!x.eof() && ((a != 'S') || (b != 'S')))
		{
			x.ignore(8);
			getline(x, solution);
		}


	}

}
string checkLevel(bool level1, bool level2, bool level3, bool level4, bool level5)
{
	string s;


	if (level1 == true)
		s = "Level1.txt";
	else if (level2 == true)
		s = "Level2.txt";
	else if (level3 == true)
		s = "Level3.txt";
	else if (level4 == true)
		s = "Level4.txt";
	else if (level5 == true)
		s = "Level5.txt";
	return s;
}
