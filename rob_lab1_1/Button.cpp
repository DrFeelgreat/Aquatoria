#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::load(const std::string & textureFile, sf::FloatRect textureCoord, sf::Vector2u size, sf::Vector2f position)
{
	if (!m_texture.loadFromFile(textureFile))
		return false;

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);
	m_texture.setSmooth(true);
	m_vertices[0].position = position;
	m_vertices[1].position = sf::Vector2f(position.x + size.x, position.y);
	m_vertices[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	m_vertices[3].position = sf::Vector2f(position.x, position.y + size.y);

	m_vertices[0].texCoords = sf::Vector2f(textureCoord.left, textureCoord.top);
	m_vertices[1].texCoords = sf::Vector2f(textureCoord.left + textureCoord.width, textureCoord.top);
	m_vertices[2].texCoords = sf::Vector2f(textureCoord.left + textureCoord.width, textureCoord.top + textureCoord.height);
	m_vertices[3].texCoords = sf::Vector2f(textureCoord.left, textureCoord.top + textureCoord.height);


	return true;
}

bool Button::clickCheck(sf::Vector2i cursor_click, sf::Vector2i cursor_rel)
{
	if (((cursor_click.x > m_vertices[0].position.x&&cursor_click.x < m_vertices[1].position.x) &&
		(cursor_click.y > m_vertices[0].position.y&&cursor_click.y < m_vertices[3].position.y)) &&
		((cursor_rel.x > m_vertices[0].position.x&&cursor_rel.x < m_vertices[1].position.x) &&
		(cursor_rel.y > m_vertices[0].position.y&&cursor_rel.y < m_vertices[3].position.y)))
		return true;
	return false;
}

void Button::cursorPos(sf::Vector2i cursor_pos)
{
	if ((cursor_pos.x > m_vertices[0].position.x&&cursor_pos.x < m_vertices[1].position.x) &&
		(cursor_pos.y > m_vertices[0].position.y&&cursor_pos.y < m_vertices[3].position.y))
	{
		sf::Color col(53, 204, 255, 255);
		m_vertices[0].color = col;
		m_vertices[1].color = col;
		m_vertices[2].color = col;
		m_vertices[3].color = col;
	}
	else
	{
		sf::Color col(255, 255, 255, 255);
		m_vertices[0].color = col;
		m_vertices[1].color = col;
		m_vertices[2].color = col;
		m_vertices[3].color = col;
	}
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.texture = &m_texture;

	target.draw(m_vertices, states);

}