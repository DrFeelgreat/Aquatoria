#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Screen.h"
#include "Button.h"
#include "time.h"
#define pi 4*atan(1)
#define dt 0.05

using namespace std;

struct point
{
	double x, y;
	point()
	{
		x = 0;
		y = 0;
	}
	point(double x1, double y1)
	{
		x = x1;
		y = y1;
	}
};

struct vec
{
	double x, y, Vx, Vy;
	vec()
	{
		x = 0;
		y = 0;
		Vx = 0;
		Vy = 0;
	}
	vec(double x1, double y1, double Vx1, double Vy1)
	{
		x = x1;
		y = y1;
		Vx = Vx1;
		Vy = Vy1;
	}
};

double sqr(double i)
{
	return i * i;
}

int main()
{

	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	sf::RenderWindow window(modes[0], "", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	Screen screen;
	if (!screen.load("background4.jpg", sf::FloatRect(0, 0, 1300, 964), sf::Vector2u(1920, 1080), sf::Vector2f(0, 0)))
		window.close();
	screen.setMaxFrame(1);

	sf::RectangleShape aqua(sf::Vector2f(1080.f, 1080.f));
	aqua.setFillColor(sf::Color(180, 185, 250));

	Button clear;
	if (!clear.load("clear.jpg", sf::FloatRect(0, 0, 413, 138), sf::Vector2u(413, 138), sf::Vector2f(1300, 50)))
		window.close();

	Button save;
	if (!save.load("save.jpg", sf::FloatRect(0, 0, 413, 138), sf::Vector2u(413, 138), sf::Vector2f(1300, 250)))
		window.close();

	Button load;
	if (!load.load("load.jpg", sf::FloatRect(0, 0, 413, 138), sf::Vector2u(413, 138), sf::Vector2f(1300, 450)))
		window.close();

	Button oil;
	if (!oil.load("oil.jpg", sf::FloatRect(0, 0, 413, 138), sf::Vector2u(413, 138), sf::Vector2f(1300, 650)))
		window.close();

	sf::CircleShape rob(10.f);
	rob.setFillColor(sf::Color::Black);
	rob.setPosition(1000.f, 885.f);

	vector<sf::ConvexShape> arrows;
	arrows.resize(0);


	sf::Vector2i click, rel, cur;

	vector<pair<point, point>> grid;
	grid.resize(0);

	for (int i = 0; i < 1080; i += 54)
	{
		point p1(i, 0), p2(i, 1080);
		grid.push_back(make_pair(p1, p2));
	}

	for (int i = 0; i < 1080; i += 54)
	{
		point p1(0, i), p2(1080, i);
		grid.push_back(make_pair(p1, p2));
	}

	vector<pair<point, point>> streams;
	streams.resize(0);

	vector<sf::CircleShape> oils;
	oils.resize(0);
	sf::CircleShape test(3);
	test.setFillColor(sf::Color::Black);
	test.setOrigin(3, 3);
	test.setPosition(2.25, 1.25);
	oils.push_back(test);

	int i = 1;
	bool put_oil = false;
	bool stream = false;

	sf::Clock osid;
	sf::Clock speed;

	while (window.isOpen())
	{


		cur = sf::Mouse::getPosition();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::Delete)
				{
					streams.pop_back();
					arrows.pop_back();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				click = sf::Mouse::getPosition();
				point p(click.x, click.y);

				if (put_oil == false)
				{
					if (p.x < 1080)
					{
						streams.push_back(make_pair(p, p));
						stream = true;
					}
					else
					{
						point p1(10000, 10000);
						streams.push_back(make_pair(p1, p1));
					}
				}
				/*}*/
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				rel = sf::Mouse::getPosition();
				if (put_oil == true)
				{
					if (rel.x < 1080)
					{
						for (int i = rel.x - 47; i <= rel.x + 47; i += 6)
							for (int j = rel.y - 47; j <= rel.y + 47; j += 6)
								if ((sqr(i - rel.x) + sqr(j - rel.y)) <= 2025)
								{
									sf::CircleShape circle(3);
									circle.setOrigin(3, 3);
									circle.setFillColor(sf::Color::Black);
									circle.setPosition(i, j);
									oils.push_back(circle);
								}
					}
					put_oil = false;
				}
				else
				{
					point p1(rel.x, rel.y);
					if (streams.back().first.y > 1080)
					{
						p1.y = 10000;
					}
					if (p1.x > 1075)
						p1.x = 1075;
					streams.back().second = p1;
					double x1 = streams.back().first.x;
					double y1 = streams.back().first.y;
					double x2 = streams.back().second.x;
					double y2 = streams.back().second.y;
					double dx = abs(x2 - x1);
					double dy = abs(y2 - y1);
					double rot;
					if (dx == 0)
					{
						if (y2 < y1)
							rot = 0;
						else rot = 180;
					}
					if (dy == 0)
					{
						if (x2 > x1)
							rot = 90;
						else rot = 270;
					}
					else if ((x1 < x2) && (y1 > y2))
						rot = 90 - 180 / pi * atan(dy / dx);
					else if ((x1 < x2) && (y1 < y2))
						rot = 90 + 180 / pi * atan(dy / dx);
					else if ((x1 > x2) && (y1 < y2))
						rot = 270 - 180 / pi * atan(dy / dx);
					else if ((x1 > x2) && (y1 > y2))
						rot = 270 + 180 / pi * atan(dy / dx);
					sf::ConvexShape arrow;
					arrow.setPointCount(3);
					arrow.setPoint(0, sf::Vector2f(5.f, 0.f));
					arrow.setPoint(1, sf::Vector2f(0.f, 18.f));
					arrow.setPoint(2, sf::Vector2f(10.f, 18.f));
					arrow.setFillColor(sf::Color::Black);
					arrow.setOrigin(5, 9);
					arrow.setPosition(p1.x, p1.y);
					arrow.setRotation(rot);
					arrows.push_back(arrow);
					stream = false;
					if (streams.back().first.y > 1080)
					{
						streams.pop_back();
						arrows.pop_back();
					}
					if (clear.clickCheck(click, rel))
					{
						streams.clear();
						arrows.clear();
						oils.clear();
					}
					if (save.clickCheck(click, rel))
					{
						ofstream file("streams.txt", ios_base::out | ios_base::trunc);
						for (int i = 0; i < streams.size(); i++)
							file << streams[i].first.x << " " << streams[i].first.y << " " << streams[i].second.x << " " << streams[i].second.y << " " << arrows[i].getRotation() << endl;
						file.close();
					}
					if (load.clickCheck(click, rel))
					{
						ifstream file("streams.txt");
						double x1, y1, x2, y2, rot;
						while (file >> x1 >> y1 >> x2 >> y2 >> rot)
						{
							point p1(x1, y1), p2(x2, y2);
							streams.push_back(make_pair(p1, p2));
							sf::ConvexShape arrow;
							arrow.setPointCount(3);
							arrow.setPoint(0, sf::Vector2f(5.f, 0.f));
							arrow.setPoint(1, sf::Vector2f(0.f, 18.f));
							arrow.setPoint(2, sf::Vector2f(10.f, 18.f));
							arrow.setFillColor(sf::Color::Black);
							arrow.setOrigin(5, 9);
							arrow.setPosition(p2.x, p2.y);
							arrow.setRotation(rot);
							arrows.push_back(arrow);
						}
						file.close();
					}
					if (oil.clickCheck(click, rel))
					{
						put_oil = true;
					}
				}
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{

		}
		point p(cur.x, cur.y);
		if (stream == true)
			streams.back().second = p;
		srand(time(0));
		if (streams.size() > 2)
		{
			if (speed.getElapsedTime().asMilliseconds() >= 35)
			{
				for (int i = 0; i < oils.size(); i++)
				{
					double x = oils[i].getPosition().x;
					double y = oils[i].getPosition().y;
					vector < pair<vec, double>> r;
					r.resize(0);
					vec vec1(streams[0].first.x, streams[0].first.y, streams[0].second.x - streams[0].first.x, streams[0].second.y - streams[0].first.y);
					r.push_back(make_pair(vec1, sqrt(sqr(streams[0].first.x - x) + sqr(streams[0].first.y - y))));
					vec vec2(streams[1].first.x, streams[1].first.y, streams[1].second.x - streams[1].first.x, streams[1].second.y - streams[1].first.y);
					r.push_back(make_pair(vec2, sqrt(sqr(streams[1].first.x - x) + sqr(streams[1].first.y - y))));
					vec vec3(streams[2].first.x, streams[2].first.y, streams[2].second.x - streams[2].first.x, streams[2].second.y - streams[2].first.y);
					r.push_back(make_pair(vec3, sqrt(sqr(streams[2].first.x - x) + sqr(streams[2].first.y - y))));
					for (int k = 0; k < 2; k++)
						for (int l = k + 1; l < 3; l++)
						{
							if (r[l].second > r[k].second)
							{
								iter_swap(r.begin() + k, r.begin() + l);
							}
						}
					for (int j = 3; j < streams.size(); j++)
					{
						double d = sqrt(sqr(streams[j].first.x - x) + sqr(streams[j].first.y - y));
						if (d < r[2].second)
						{
							vec vec4(streams[j].first.x, streams[j].first.y, streams[j].second.x - streams[j].first.x, streams[j].second.y - streams[j].first.y);
							r.push_back(make_pair(vec4, d));
							iter_swap(r.begin(), r.begin() + 1);
							iter_swap(r.begin() + 1, r.begin() + 2);
							iter_swap(r.begin() + 2, r.begin() + 3);
							r.pop_back();
						}
						else if (d < r[1].second)
						{
							vec vec4(streams[j].first.x, streams[j].first.y, streams[j].second.x - streams[j].first.x, streams[j].second.y - streams[j].first.y);
							r.push_back(make_pair(vec4, d));
							iter_swap(r.begin(), r.begin() + 1);
							iter_swap(r.begin() + 1, r.begin() + 3);
							r.pop_back();
						}
						else if (d < r[0].second)
						{
							vec vec4(streams[j].first.x, streams[j].first.y, streams[j].second.x - streams[j].first.x, streams[j].second.y - streams[j].first.y);
							r.push_back(make_pair(vec4, d));
							iter_swap(r.begin(), r.begin() + 3);
							r.pop_back();
						}
					}
					double dn1 = sqrt(sqr(r[1].first.x - r[2].first.x) + sqr(r[1].first.y - r[2].first.y) + sqr(r[1].first.Vx - r[2].first.Vx));
					double dn2 = sqrt(sqr(r[1].first.x - r[0].first.x) + sqr(r[1].first.y - r[0].first.y) + sqr(r[1].first.Vx - r[0].first.Vx));
					double nx = ((r[1].first.y - r[2].first.y)*(r[1].first.Vx - r[0].first.Vx) - (r[1].first.y - r[0].first.y)*(r[1].first.Vx - r[2].first.Vx)) / (dn1*dn2);
					double ny = ((r[1].first.x - r[0].first.x)*(r[1].first.Vx - r[2].first.Vx) - (r[1].first.x - r[2].first.x)*(r[1].first.Vx - r[0].first.Vx)) / (dn1*dn2);
					double nz = ((r[1].first.x - r[2].first.x)*(r[1].first.y - r[0].first.y) - (r[1].first.x - r[0].first.x)*(r[1].first.y - r[2].first.y)) / (dn1*dn2);
					double Vx0 = (1 / nz)*(-(x - r[2].first.x)*nx - (y - r[2].first.y)*ny) + r[2].first.Vx;

					double dm1 = sqrt(sqr(r[1].first.x - r[2].first.x) + sqr(r[1].first.y - r[2].first.y) + sqr(r[1].first.Vy - r[2].first.Vy));
					double dm2 = sqrt(sqr(r[1].first.x - r[0].first.x) + sqr(r[1].first.y - r[0].first.y) + sqr(r[1].first.Vy - r[0].first.Vy));
					double mx = ((r[1].first.y - r[2].first.y)*(r[1].first.Vy - r[0].first.Vy) - (r[1].first.y - r[0].first.y)*(r[1].first.Vy - r[2].first.Vy)) / (dm1*dm2);
					double my = ((r[1].first.x - r[0].first.x)*(r[1].first.Vy - r[2].first.Vy) - (r[1].first.x - r[2].first.x)*(r[1].first.Vy - r[0].first.Vy)) / (dm1*dm2);
					double mz = ((r[1].first.x - r[2].first.x)*(r[1].first.y - r[0].first.y) - (r[1].first.x - r[0].first.x)*(r[1].first.y - r[2].first.y)) / (dm1*dm2);
					double Vy0 = (1 / mz)*(-(x - r[2].first.x)*mx - (y - r[2].first.y)*my) + r[2].first.Vy;
					oils[i].setPosition(x + Vx0 * dt, y + Vy0 * dt);
					if (oils[i].getPosition().x > 1080)
					{
						vector<sf::CircleShape>::iterator j = oils.begin();
						for (int z = 0; z < i; z++)
							j++;
						oils.erase(j);
					}
				}
				speed.restart();
			}
		}
		if (osid.getElapsedTime().asMilliseconds() >= 300)
		{

			for (int i = 0; i < oils.size(); i++)
			{
				double os = (rand() % 100 + 1);
				if (os <= 20)
				{
					vector<sf::CircleShape>::iterator j = oils.begin();
					for (int z = 0; z < i; z++)
						j++;
					oils.erase(j);
				}
			}
			osid.restart();
		}
		clear.cursorPos(cur);
		save.cursorPos(cur);
		load.cursorPos(cur);
		oil.cursorPos(cur);
		window.draw(screen);
		window.draw(aqua);
		window.draw(clear);
		window.draw(save);
		window.draw(load);
		window.draw(oil);
		/*for (int i = 0; i < grid.size(); i++)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(grid[i].first.x, grid[i].first.y)),
				sf::Vertex(sf::Vector2f(grid[i].second.x, grid[i].second.y))
			};
			line[0].color = sf::Color::Black;
			line[1].color = sf::Color::Black;
			window.draw(line, 2, sf::Lines);
		}*/
		point p1(cur.x, cur.y);
		for (int i = 0; i < streams.size(); i++)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(streams[i].first.x, streams[i].first.y)),
				sf::Vertex(sf::Vector2f(streams[i].second.x, streams[i].second.y))
			};
			line[0].color = sf::Color::Black;
			line[1].color = sf::Color::Black;
			window.draw(line, 2, sf::Lines);
		}
		for (int i = 0; i < arrows.size(); i++)
			window.draw(arrows[i]);
		for (int i = 0; i < oils.size(); i++)
			window.draw(oils[i]);
		window.display();
	}
	system("pause");
	return 0;
}