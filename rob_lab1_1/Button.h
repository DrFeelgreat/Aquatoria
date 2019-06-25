#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
	Button();
	~Button();
	bool load(const std::string & textureFile, sf::FloatRect textureCoord, sf::Vector2u size, sf::Vector2f position);
	bool clickCheck(sf::Vector2i cursor_click, sf::Vector2i cursor_rel);
	void cursorPos(sf::Vector2i cursor_pos);
private:
	sf::VertexArray m_vertices;
	sf::Texture m_texture;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};