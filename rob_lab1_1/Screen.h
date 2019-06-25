#pragma once
#include <SFML/Graphics.hpp>

class Screen :public sf::Drawable, sf::Transformable
{
public:

	Screen();
	~Screen();
	bool load(const std::string & textureFile, sf::FloatRect textureCoord, sf::Vector2u size, sf::Vector2f position);
	void setMaxFrame(int frameNumber);
	void nextFrame();
	void visibility(bool visible);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool vis = true;
	int animation_step = 0;
	int animation_step_max = 0;
	sf::FloatRect m_frameSize;
	sf::VertexArray m_vertices;
	sf::Texture m_texture;
};